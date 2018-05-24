/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{


	//--------------------------------------------------------------------------------------
	//	class Player : public GameObject;
	//	用途: プレイヤー
	//--------------------------------------------------------------------------------------
	//構築と破棄
	Player::Player(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir) :
		SS5ssae(StagePtr, BaseDir, L"Idea1.ssae", L"Wait"),
		m_MaxSpeed(50.0f),	//最高速度
		m_Decel(0.65f),	//減速値
		m_Mass(0.5f),	//質量
		m_Key(0),		//鍵の取得状況
		m_Death(0)		//死因を0(生存)に
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.05f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(-0.5f, 0.0f, 0.0f)
		);
		m_ToAnimeMatrixRight.affineTransformation(
			Vec3(-0.1f, 0.05f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.5f, 0.0f, 0.0f)
		);
	}

	//0を渡すと左、1を渡すと右のスティックのX値を返す
	float Player::GetMoveVector(int LR) const {
		float MoveX = 0;
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			switch (LR){
			case 0:
				if (CntlVec[0].fThumbLX != 0) {
					//コントローラの向き計算
					MoveX = CntlVec[0].fThumbLX;
				}
				break;
			case 1:
				if (CntlVec[0].fThumbRX != 0) {
					//コントローラの向き計算
					MoveX = CntlVec[0].fThumbRX;
				}
				break;
			default:
				break;
			}
		}
		return MoveX;
	}

	//モーションを実装する関数群
	//移動して向きを移動方向にする
	//移動距離を返す
	float  Player::MoveRotationMotion() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto MoveX = GetMoveVector(0);
		//Transform
		auto PtrTransform = GetComponent<Transform>();
		//Rigidbodyを取り出す
		auto PtrRedit = GetComponent<Rigidbody>();
		//現在の速度を取り出す
		auto Velo = PtrRedit->GetVelocity().x;
		auto VeloY = PtrRedit->GetVelocity().y;
		//目的地を最高速度を掛けて求める
		auto Target = MoveX * m_MaxSpeed;
		//目的地に向かうために力のかける方向を計算する
		//Forceはフォースである
		auto Force = Target - Velo;
		//加速度を求める
		auto Accel = Force / m_Mass;
		//ターン時間を掛けたものを速度に加算する
		Velo += (Accel * ElapsedTime);
		//減速する
		Velo *= m_Decel;
		//速度を設定する
		Vec3 VecVelo(Velo, VeloY, 0);
		PtrRedit->SetVelocity(VecVelo);
		////回転の計算

		//元となるオブジェクトからアニメーションオブジェクトへの行列の設定
		//Transformのスケーリングを-1にすると衝突判定がうまくいかないので
		//SpriteStdioの部分だけ変更する
		if (MoveX > 0.0f) {
			SetToAnimeMatrix(m_ToAnimeMatrixRight);
		}
		else if (MoveX < 0.0f) {
			SetToAnimeMatrix(m_ToAnimeMatrixLeft);
		}
		//MoveXを返す
		return MoveX;
	}

	//衝突時
	void Player::OnCollision(vector<shared_ptr<GameObject>>& OtherVec) {
		auto playerTrans = GetComponent<Transform>();
		for (auto &obj : OtherVec) {
			//シャドウオブジェクトを検出
			auto ShadowPtr = dynamic_pointer_cast<ShadowObject>(obj);
			//当たったのがシャドウオブジェクトで
			if (ShadowPtr) {
				//シャドウの判定
				OBB p;
				p.m_Center = ShadowPtr->GetComponent<Transform>()->GetWorldPosition();
				p.m_Size = ShadowPtr->GetComponent<Transform>()->GetScale() * 0.5f;
				Vec3 HitPoint;
				//イデアの中心点からシャドウまでの最接近点の算出
				HitTest::ClosestPtPointOBB(playerTrans->GetWorldPosition(), p, HitPoint);
				//プレイヤーの判定よりも、ヒットポイントのYが低くて
				//X幅の中に入っていたら
				if ((playerTrans->GetWorldPosition().x - playerTrans->GetScale().x) <= HitPoint.x
					&& (playerTrans->GetWorldPosition().x + playerTrans->GetScale().x) >= HitPoint.x
					&& playerTrans->GetWorldPosition().y >= p.m_Center.y + p.m_Size.y) {
					//ペアレント化してるオブジェクトが無かったらペアレント化
					if (!playerTrans->GetParent()) {
						//ペアレント化する
						playerTrans->SetParent(ShadowPtr);
						m_ParentFlag = true;
					}
					//当たってるオブジェクトが親オブジェクトじゃ無かったら
					else if (!(playerTrans->GetParent() == ShadowPtr)) {
						//今の親を消して新たに親を設定する
						playerTrans->ClearParent();
						playerTrans->SetParent(ShadowPtr);
					}

				}
			}
		}
	}

	//衝突している時
	void Player::OnCollisionExcute(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto &obj : OtherVec) {
			//それが親だったら
			if (GetComponent<Transform>()->GetParent() == obj) {
				//プレイヤーのYを親の上に乗るようにして
				auto ParentTrans = obj->GetComponent<Transform>();
				auto Ppos = GetComponent<Transform>()->GetWorldPosition();
				Ppos.y = ParentTrans->GetPosition().y + ParentTrans->GetScale().y * 0.5f
									+ GetComponent<Transform>()->GetScale().y * 0.5f;
				//適用する
				GetComponent<Transform>()->SetWorldPosition(Ppos);
			}

			OBB p;
			p.m_Center = obj->GetComponent<Transform>()->GetWorldPosition();
			p.m_Size = obj->GetComponent<Transform>()->GetScale() * 0.5f;
			//当たり判定の更新
			m_DieOBB.m_Center = GetComponent<Transform>()->GetWorldPosition();
			//頭中心あたりが当たったら死ぬ
			if (HitTest::OBB_OBB(m_DieOBB, p)) {
				m_Death = 1;
			}
		}
	}

	//衝突しなくなった時
	void Player::OnCollisionExit(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto &obj : OtherVec) {
			//シャドウオブジェクトを検出
			auto ShadowPtr = dynamic_pointer_cast<ShadowObject>(obj);
			//それが親のシャドウで
			if (ShadowPtr == GetComponent<Transform>()->GetParent()) {
				auto shadowPos = ShadowPtr->GetComponent<Transform>()->GetWorldPosition();
				auto shadowSca = ShadowPtr->GetComponent<Transform>()->GetScale();
				//影オブジェの横に落ちてたら
				if((shadowPos.x - shadowSca.x * 0.5f) >= GetComponent<Transform>()->GetWorldPosition().x ||
					(shadowPos.x + shadowSca.x * 0.5f) <= GetComponent<Transform>()->GetWorldPosition().x){
					//ペアレント化を解く
					GetComponent<Transform>()->ClearParent();
					m_ParentFlag = false;
				}
			}
		}
	}

	//初期化
	void Player::OnCreate() {
		m_GameClearFlag = false;
		m_GameOverFlag = false;
		m_ParentFlag = false;
		//初期位置などの設定
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(0.80f, 1.60f, 0.40f);	//X,Z25、Y50の長方形
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(-8.0f, 5.5f, 0.0f);

		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(49.0f);

		//元となるオブジェクトからアニメーションオブジェクトへの行列の設定
		SetToAnimeMatrix(m_ToAnimeMatrixLeft);

		//Rigidbodyをつける
		auto PtrRedid = AddComponent<Rigidbody>();
		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();
		//auto PtrCol = AddComponent<CollisionSphere>();
		PtrCol->SetIsHitAction(IsHitAction::Auto);
		//コリジョンを表示する場合は以下を設定
		//PtrCol->SetDrawActive(true);
		//デバッグ用文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		//死亡判定用OBBの大きさ設定
		m_DieOBB.m_Size.x = Ptr->GetScale().x * 0.3f;
		m_DieOBB.m_Size.y = Ptr->GetScale().y * 0.3f;

		//Actionをつける
		//レイヤー変更用
		auto PtrAction = AddComponent<Action>();
		//アクションは無効にしておく
		PtrAction->SetUpdateActive(false);

		//ステートマシンの構築
		m_StateMachine = make_shared< StateMachine<Player> >(GetThis<Player>());
		//最初のステートをWaitStateに設定
		m_StateMachine->SetCurrentState(WaitState::Instance());
		//WaitStateの初期化実行を行う
		m_StateMachine->GetCurrentState()->Enter(GetThis<Player>());
	}

	//更新
	void Player::OnUpdate() {
			//ステートマシンのUpdateを行う
			//この中でステートの切り替えが行われる
			m_StateMachine->Update();

			//重力を加える
			auto PtrGrav = GetBehavior<Gravity>();
			PtrGrav->SetGravity(Vec3(0.0f, -4.9f, 0.0f));
			PtrGrav->Execute();
	}

	void Player::OnUpdate2() {
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		if (m_ParentFlag && !m_GameOverFlag && !m_GameClearFlag && ScenePtr->GetStartFlag()) {
			//プレイヤーの移動
			MoveRotationMotion();
			//文字列の表示
			//DrawStrings();
		}

		if (!m_ParentFlag) {
			auto PtrRedit = GetComponent<Rigidbody>();
			PtrRedit->SetVelocityZero();

		}
			PlayerHP();
	}
	//
	void Player::PlayerHP() {
		m_PlayerHP = 3;
		auto PlayerPos = this->GetComponent<Transform>()->GetPosition();
		//落下死
		if (PlayerPos.y < -25.0f){
			m_PlayerHP = 0;
		}

		if (m_PlayerHP == 0&& !m_GameOverFlag){
			m_GameOverFlag = true;
			m_FadeFlag = true;
		}
	}
	//GameOverSceneに移行する
	void Player::GoGameOverScene() {
		m_GameOverFlag = true;
	}
	//GameOverSceneに移行する
	void Player::GoGameClearScene() {
		m_GameClearFlag = true;
	}
	void Player::InGoal() {
		GetStateMachine()->ChangeState(GoalState::Instance());
	}

	//文字列の表示
	void Player::DrawStrings() {

		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring FPS(L"FPS: ");
		FPS += Util::UintToWStr(fps);
		FPS += L"\nElapsedTime: ";
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		FPS += Util::FloatToWStr(ElapsedTime);
		FPS += L"\n";

		auto Pos = GetComponent<Transform>()->GetPosition();
		wstring PositionStr(L"Position:\t");
		PositionStr += L"X=" + Util::FloatToWStr(Pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Y=" + Util::FloatToWStr(Pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Z=" + Util::FloatToWStr(Pos.z, 6, Util::FloatModify::Fixed) + L"\n";

		auto WPos = GetComponent<Transform>()->GetWorldPosition();
		wstring WPositionStr(L"WPosition:");
		WPositionStr += L"X=" + Util::FloatToWStr(WPos.x, 6, Util::FloatModify::Fixed) + L",\t";
		WPositionStr += L"Y=" + Util::FloatToWStr(WPos.y, 6, Util::FloatModify::Fixed) + L",\t";
		WPositionStr += L"Z=" + Util::FloatToWStr(WPos.z, 6, Util::FloatModify::Fixed) + L"\n";


		wstring RididStr(L"Velocity:\t");
		auto Velocity = GetComponent<Rigidbody>()->GetVelocity();
		RididStr += L"X=" + Util::FloatToWStr(Velocity.x, 6, Util::FloatModify::Fixed) + L",\t";
		RididStr += L"Y=" + Util::FloatToWStr(Velocity.y, 6, Util::FloatModify::Fixed) + L",\t";
		RididStr += L"Z=" + Util::FloatToWStr(Velocity.z, 6, Util::FloatModify::Fixed) + L"\n";


		wstring HitObjectStr(L"HitObject: ");
		if (GetComponent<Collision>()->GetHitObjectVec().size() > 0) {
			for (auto&v : GetComponent<Collision>()->GetHitObjectVec()) {
				HitObjectStr += Util::UintToWStr((UINT)v.get()) + L",";
			}
			HitObjectStr += L"\n";
		}
		else {
			HitObjectStr += L"NULL\n";
		}
		wstring str = FPS + PositionStr +WPositionStr + RididStr +  HitObjectStr;
		//文字列をつける
		auto PtrString = GetComponent<StringSprite>();
		PtrString->SetText(str);
	}

	void Player::LoopedAnimeUpdateMotion() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//アニメーションを更新する
		UpdateAnimeTime(ElapsedTime);
	}

	void Player::AnimeChangeMotion(const wstring& key, bool looped) {
		ChangeAnimation(key);
		SetLooped(looped);
	}

	//--------------------------------------------------------------------------------------
	//	class WaitState : public ObjState<Player>;
	//	用途: 待機状態
	//--------------------------------------------------------------------------------------
	//ステートのインスタンス取得
	shared_ptr<WaitState> WaitState::Instance() {
		static shared_ptr<WaitState> instance;
		if (!instance) {
			instance = shared_ptr<WaitState>(new WaitState);
		}
		return instance;
	}
	//ステートに入ったときに呼ばれる関数
	void WaitState::Enter(const shared_ptr<Player>& Obj) {
		Obj->AnimeChangeMotion(L"Wait_1", true);
	}
	//ステート実行中に毎ターン呼ばれる関数
	void WaitState::Execute(const shared_ptr<Player>& Obj) {
		//アニメーション更新
		Obj->LoopedAnimeUpdateMotion();
		//潰れて死んだらDiedアニメを流す
		if (Obj->GetDeath() == 1) {
			Obj->GetStateMachine()->ChangeState(DiedState::Instance());
		}
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		//左スティックの値が0以外ならWalkアニメを流す
		if (Obj->GetParentFlag() && Obj->GetMoveVector(0)&& ScenePtr->GetStartFlag()) {
			Obj->GetStateMachine()->ChangeState(WalkState::Instance());
		}
		if (!Obj->GetParentFlag()) {
			Obj->GetStateMachine()->ChangeState(FallState::Instance());
		}
	}
	//ステートにから抜けるときに呼ばれる関数
	void WaitState::Exit(const shared_ptr<Player>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class FallState : public ObjState<Player>;
	//	用途: 落ちてるとき
	//--------------------------------------------------------------------------------------
	//ステートのインスタンス取得
	shared_ptr<FallState> FallState::Instance() {
		static shared_ptr<FallState> instance;
		if (!instance) {
			instance = shared_ptr<FallState>(new FallState);
		}
		return instance;
	}
	//ステートに入ったときに呼ばれる関数
	void FallState::Enter(const shared_ptr<Player>& Obj) {
		Obj->AnimeChangeMotion(L"Jump_1", true);
	}
	//ステート実行中に毎ターン呼ばれる関数
	void FallState::Execute(const shared_ptr<Player>& Obj) {
		//アニメーション更新
		Obj->LoopedAnimeUpdateMotion();
		//左スティックの値が0以外ならWalkアニメを流す
		if (Obj->GetParentFlag()) {
			Obj->GetStateMachine()->ChangeState(WaitState::Instance());
		}
	}
	//ステートから抜けるときに呼ばれる関数
	void FallState::Exit(const shared_ptr<Player>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class WalkState : public ObjState<Player>;
	//	用途: 歩き状態
	//--------------------------------------------------------------------------------------
	//ステートのインスタンス取得
	shared_ptr<WalkState> WalkState::Instance() {
		static shared_ptr<WalkState> instance;
		if (!instance) {
			instance = shared_ptr<WalkState>(new WalkState);
		}
		return instance;
	}
	//ステートに入ったときに呼ばれる関数
	void WalkState::Enter(const shared_ptr<Player>& Obj) {
		Obj->AnimeChangeMotion(L"Walk", true);
		//---------------------------------------------------------------
		wstring DataDir;
		//サンプルのためアセットディレクトリを取得
		//App::GetApp()->GetAssetsDirectory(DataDir);
		//各ゲームは以下のようにデータディレクトリを取得すべき
		App::GetApp()->GetDataDirectory(DataDir);

		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"walk");
		m_AudioObjectPtr->Start(L"walk", XAUDIO2_LOOP_INFINITE, 0.1f);
		Obj->SetNowMusic(L"walk");
		//----------------------------------------------------------------
	}
	//ステート実行中に毎ターン呼ばれる関数
	void WalkState::Execute(const shared_ptr<Player>& Obj) {
		//アニメーション更新
		Obj->LoopedAnimeUpdateMotion();
		//潰れて死んだらDiedアニメーションを流す
		if (Obj->GetDeath() == 1) {
			Obj->GetStateMachine()->ChangeState(DiedState::Instance());
		}
		//左スティックの値が0(入力されなくなった)ならWaitアニメを流す
		if (Obj->GetMoveVector(0) == 0.0f) {
			Obj->GetStateMachine()->ChangeState(WaitState::Instance());
		}
	}
	//ステートにから抜けるときに呼ばれる関数
	void WalkState::Exit(const shared_ptr<Player>& Obj) {
		m_AudioObjectPtr->Stop(Obj->GetNowMusic());
	}

	//--------------------------------------------------------------------------------------
	//	class DiedState : public ObjState<Player>;
	//	用途: 死亡状態
	//--------------------------------------------------------------------------------------
	//ステートのインスタンス取得
	shared_ptr<DiedState> DiedState::Instance() {
		static shared_ptr<DiedState> instance;
		if (!instance) {
			instance = shared_ptr<DiedState>(new DiedState);
		}
		return instance;
	}
	//ステートに入ったときに呼ばれる関数
	void DiedState::Enter(const shared_ptr<Player>& Obj) {
		//死亡アニメを呼び出す
		Obj->AnimeChangeMotion(L"Died_1", false);
		//操作を受け付けなくする
		Obj->SetGameOverFlag(true);
		//Velocityを0にする
		Obj->GetComponent<Rigidbody>()->SetVelocityZero();
		//---------------------------------------------------------------
		wstring DataDir;
		//サンプルのためアセットディレクトリを取得
		//App::GetApp()->GetAssetsDirectory(DataDir);
		//各ゲームは以下のようにデータディレクトリを取得すべき
		App::GetApp()->GetDataDirectory(DataDir);

		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"dead");
		m_AudioObjectPtr->Start(L"dead", XAUDIO2_NO_LOOP_REGION, 0.1f);
		Obj->SetNowMusic(L"dead");
		//----------------------------------------------------------------
	}
	//ステート実行中に毎ターン呼ばれる関数
	void DiedState::Execute(const shared_ptr<Player>& Obj) {
		//アニメーション更新
		Obj->LoopedAnimeUpdateMotion();
		//アニメーションが終わったら
		if (Obj->IsAnimeEnd()) {
			//ゲームオーバーシーンに遷移する
			Obj->SetFadeFlag(true);
		}
	}
	//ステートにから抜けるときに呼ばれる関数
	void DiedState::Exit(const shared_ptr<Player>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class GoalState : public ObjState<Player>;
	//	用途: ゴール到達状態
	//--------------------------------------------------------------------------------------
	//ステートのインスタンス取得
	shared_ptr<GoalState> GoalState::Instance() {
		static shared_ptr<GoalState> instance;
		if (!instance) {
			instance = shared_ptr<GoalState>(new GoalState);
		}
		return instance;
	}
	//ステートに入ったときに呼ばれる関数
	void GoalState::Enter(const shared_ptr<Player>& Obj) {
		Obj->SetFps(60.0f);
		Obj->AnimeChangeMotion(L"curtsey", false);
		Obj->SetGameClearFlag(true);
		Obj->GetComponent<Rigidbody>()->SetVelocityZero();
	}
	//ステート実行中に毎ターン呼ばれる関数
	void GoalState::Execute(const shared_ptr<Player>& Obj) {
		//アニメーション更新
		Obj->LoopedAnimeUpdateMotion();
		if (Obj->IsAnimeEnd()) {
			Obj->SetFadeFlag(true);
		}
	}
	//ステートにから抜けるときに呼ばれる関数
	void GoalState::Exit(const shared_ptr<Player>& Obj) {
	}

}
//end basecross

