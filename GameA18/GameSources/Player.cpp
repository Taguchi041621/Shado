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
	Player::Player(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir,const Vec3 pos) :
		SS5ssae(StagePtr, BaseDir, L"Idea1.ssae", L"Wait"),m_Position(pos),
		m_MaxSpeed(80.0f),	//最高速度
		m_Decel(0.65f),	//減速値
		m_Mass(0.5f),	//質量
		m_Key(0),		//鍵の取得状況
		m_Death(0),		//死因を0(生存)に
		m_FallSpeedFirst(-7.4f)
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.05f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(-0.5f, 0.03f, 0.0f)
		);
		m_ToAnimeMatrixRight.affineTransformation(
			Vec3(-0.1f, 0.05f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.5f, 0.03f, 0.0f)
		);
	}
	//----------------------------------------------------------------------------------------------------------
	//初期化
	//----------------------------------------------------------------------------------------------------------
	void Player::OnCreate() {
		m_GameClearFlag = false;
		m_GameOverFlag = false;
		m_ParentFlag = false;
		m_StandFlag = false;
		m_DamageFlag = false;
		m_FadeFlag = false;
		//初期位置などの設定
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(0.80f, 1.60f, 0.5f);
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(m_Position);

		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(49.0f);

		//元となるオブジェクトからアニメーションオブジェクトへの行列の設定
		SetToAnimeMatrix(m_ToAnimeMatrixRight);

		//Rigidbodyをつける
		auto PtrRedid = AddComponent<Rigidbody>();
		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionObb>();
		PtrCol->SetIsHitAction(IsHitAction::None);
		//デバッグ用文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		//Actionをつける
		//レイヤー変更用
		auto PtrAction = AddComponent<Action>();
		//アクションは無効にしておく
		PtrAction->SetUpdateActive(false);

		//ステートマシンの構築
		m_StateMachine = make_shared< StateMachine<Player> >(GetThis<Player>());
		//最初のステートをWaitStateに設定
		m_StateMachine->SetCurrentState(WaitState::Instance());
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		if (ScenePtr->GetRespawnFlag())
		{
			m_StateMachine->ChangeState(StandState::Instance());
		}
		//WaitStateの初期化実行を行う
		m_StateMachine->GetCurrentState()->Enter(GetThis<Player>());

	}

	//----------------------------------------------------------------------------------------------------------
	//更新
	//----------------------------------------------------------------------------------------------------------
	void Player::OnUpdate() {
		//ステートマシンのUpdateを行う
		//この中でステートの切り替えが行われる
		m_StateMachine->Update();
	}

	void Player::OnUpdate2() {
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		auto PtrRedit = GetComponent<Rigidbody>();
		if (m_ParentFlag && !m_GameOverFlag && !m_GameClearFlag && ScenePtr->GetStartFlag() && !m_StandFlag && !m_DamageFlag) {
			//プレイヤーの移動
			MoveRotationMotion();
		}
		//影に乗っていないから落ちる
		else if (!m_ParentFlag) {
			PtrRedit->SetVelocityZero();
			GetComponent<Rigidbody>()->SetVelocity(Vec3(0.0f, m_FallSpeed, 0.0f));
			m_FallSpeed += -0.08f;
		}
		PlayerHP();
	}

	//----------------------------------------------------------------------------------------------------------
	//左スティック
	//----------------------------------------------------------------------------------------------------------
	float Player::GetMoveLeftVectorX() const {
		float MoveX = 0;

		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		//接続してなかったら0返す
		if (!CntlVec.bConnected) {
			return 0;
		}
		if (CntlVec.fThumbLX != 0) {
			//コントローラの向き計算
			MoveX = CntlVec.fThumbLX;
		}
		return MoveX;
	}
	//----------------------------------------------------------------------------------------------------------
	//右スティック
	//----------------------------------------------------------------------------------------------------------
	float Player::GetMoveRightVectorX() const{
		float MoveX = 0;

		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		//接続してなかったら0返す
		if (!CntlVec.bConnected) {
			return 0;
		}
		if (CntlVec.fThumbRX != 0) {
			//コントローラの向き計算
			MoveX = CntlVec.fThumbRX;
		}
		return MoveX;
	}

	//----------------------------------------------------------------------------------------------------------
	//移動して向きを移動方向にする
	//移動距離を返す
	//----------------------------------------------------------------------------------------------------------
	float  Player::MoveRotationMotion() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto MoveX = GetMoveLeftVectorX();
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
			m_RightOrLeft = PlayerDirection::RIGHT;
		}
		else if (MoveX < 0.0f) {
			SetToAnimeMatrix(m_ToAnimeMatrixLeft);
			m_RightOrLeft = PlayerDirection::LEFT;
		}
		//MoveXを返す
		return MoveX;
	}

	//----------------------------------------------------------------------------------------------------------
	//衝突時
	//----------------------------------------------------------------------------------------------------------
	void Player::OnCollision(vector<shared_ptr<GameObject>>& OtherVec) {
		auto playerTrans = GetComponent<Transform>();
		for (auto &obj : OtherVec) {
			//シャドウオブジェクトを検出
			auto ShadowPtr = dynamic_pointer_cast<ShadowObject>(obj);
			//当たったのがシャドウオブジェクトで
			if (ShadowPtr) {
				Extrusion(ShadowPtr);//押し出す関数
				FindParent(ShadowPtr);//親にするか調べる関数
			}
		}
	}

	//----------------------------------------------------------------------------------------------------------
	//衝突している時
	//----------------------------------------------------------------------------------------------------------
	void Player::OnCollisionExcute(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto &obj : OtherVec) {
			auto ShadowPtr = dynamic_pointer_cast<ShadowObject>(obj);
			if (ShadowPtr) {
				Extrusion(ShadowPtr);
				FindParent(ShadowPtr);
			}
		}
	}

	//----------------------------------------------------------------------------------------------------------
	//衝突しなくなった時
	//----------------------------------------------------------------------------------------------------------
	void Player::OnCollisionExit(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto &obj : OtherVec) {
			if (obj == GetComponent<Transform>()->GetParent()) {
				//親と離れているかを検出
				GetComponent<Transform>()->ClearParent();
				m_ParentFlag = false;
				//落下スピードの初期化
				m_FallSpeed = m_FallSpeedFirst;
			}
		}
	}
	//----------------------------------------------------------------------------------------------------------
	//親になる条件を満たしているかを調べて、満たしていたら親にする
	//----------------------------------------------------------------------------------------------------------
	void Player::FindParent(const shared_ptr<GameObject>& OtherVec) {
		auto playerTrans = GetComponent<Transform>();
		auto playerPos = playerTrans->GetWorldPosition();
		auto playerSca = playerTrans->GetScale();
		auto ObjPos = OtherVec->GetComponent<Transform>()->GetWorldPosition();
		auto ObjSca = OtherVec->GetComponent<Transform>()->GetScale() * 0.5f;
		//影の上に乗っているかを調べる
		if ((ObjPos.x - ObjSca.x) < playerPos.x + playerSca.x * 0.5f
			&& (ObjPos.x + ObjSca.x) > playerPos.x - playerSca.x * 0.5f
			&& ObjPos.y + ObjSca.y <= playerPos.y - playerTrans->GetScale().y * 0.48f) {
			if (!playerTrans->GetParent()) {
				playerTrans->SetParent(OtherVec);
				m_ParentFlag = true;
			}
		}
	}
	//----------------------------------------------------------------------------------------------------------
	//押し出し
	//----------------------------------------------------------------------------------------------------------
	void Player::Extrusion(const shared_ptr<GameObject>& OtherVec) {
		auto playerPos = GetComponent<Transform>()->GetWorldPosition();
		auto playerScale = GetComponent<Transform>()->GetScale() * 0.5f;
		auto otherPos = OtherVec->GetComponent<Transform>()->GetWorldPosition();
		auto otherScale = OtherVec->GetComponent<Transform>()->GetScale() * 0.5f;
		//自機と相手が衝突しているかの判定
		if (playerPos.y - playerScale.y < otherPos.y + otherScale.y && playerPos.y + playerScale.y > otherPos.y - otherScale.y &&
			playerPos.x - playerScale.x < otherPos.x + otherScale.x && playerPos.x + playerScale.x > otherPos.x - otherScale.x) {
			//死亡判定用のOBB
			//敵
			OBB p;
			p.m_Center = otherPos;
			p.m_Size = otherScale;
			//イデア
			OBB m;
			m.m_Center = GetComponent<Transform>()->GetWorldPosition();
			m.m_Size = GetComponent<Transform>()->GetScale() * 0.3f;
			m.m_Size.z = 1.0f;

			//各方向のめり込みを確認
			float diff[4] = {
				(otherPos.x + otherScale.x) - (playerPos.x - playerScale.x), // 右
				(playerPos.x + playerScale.x) - (otherPos.x - otherScale.x), // 左
				(otherPos.y + otherScale.y) - (playerPos.y - playerScale.y), // 上
				(playerPos.y + playerScale.y) - (otherPos.y - otherScale.y), // 下
			};
			// 側面の距離が最小になっている要素を見つける
			int min = 0;
			for (int i = 0; i < 4; i++) {
				if (diff[i] < diff[min]) {
					min = i;
				}
			}
			//もっともめり込みが少ない面に押し返す
			switch (min) {
			case 0:
				//段差があったら登る
				if (diff[2] < 0.4f && diff[2] >0.0f && GetMoveLeftVectorX() < -0.6f) {
					playerPos.y += diff[2];
					break;
				}
				playerPos.x += diff[min];
				//頭中心あたりが当たったら死ぬ
				if (HitTest::OBB_OBB(p, m)) {
					m_Death = 1;
				}
				break;
			case 1:
				//段差があったら登る
				if (diff[2] < 0.4f && diff[2] > 0.0f && GetMoveLeftVectorX() > 0.6f) {
					playerPos.y += diff[2];
					break;
				}
				playerPos.x -= diff[min];
				//頭中心あたりが当たったら死ぬ
				if (HitTest::OBB_OBB(p, m)) {
					m_Death = 1;
				}
				break;
			case 2:
				playerPos.y += diff[min];
				break;
			case 3:
				//playerPos.y -= diff[min];
				//頭中心あたりが当たったら死ぬ
				if (HitTest::OBB_OBB(p, m)) {
					m_Death = 1;
				}
				break;
			default:
				break;
			}
			GetComponent<Transform>()->SetWorldPosition(playerPos);
		}
	}

	//----------------------------------------------------------------------------------------------------------
	// 死亡の判定
	//----------------------------------------------------------------------------------------------------------
	void Player::PlayerHP() {
		auto PlayerPos = this->GetComponent<Transform>()->GetWorldPosition();
		//落下死
		if (PlayerPos.y < -25.0f && !m_GameOverFlag){
			m_GameOverFlag = true;
			m_FadeFlag = true;
		}
	}
	//----------------------------------------------------------------------------------------------------------
	//着地したときの演出
	//----------------------------------------------------------------------------------------------------------
	void Player::LandingDirecting() {
		GetStage()->AddGameObject<DirectingRing>(GetComponent<Transform>()->GetWorldPosition(),
			Vec3(1.0f, 1.0f, 0.05f), Vec3(0.0f, -0.7f, 0.0f), L"Smoke_Black_TX");
	}
	//----------------------------------------------------------------------------------------------------------
	//GameOverSceneに移行する
	//----------------------------------------------------------------------------------------------------------
	void Player::GoGameOverScene() {
		m_GameOverFlag = true;
	}
	//----------------------------------------------------------------------------------------------------------
	//GameOverSceneに移行する
	//----------------------------------------------------------------------------------------------------------
	void Player::GoGameClearScene() {
		m_GameClearFlag = true;
	}
	//----------------------------------------------------------------------------------------------------------
	// ステートをゴールステートに切り替える
	//----------------------------------------------------------------------------------------------------------
	void Player::InGoal() {
		GetStateMachine()->ChangeState(GoalState::Instance());
	}
	//----------------------------------------------------------------------------------------------------------
	//アニメーションを更新する
	//----------------------------------------------------------------------------------------------------------
	void Player::LoopedAnimeUpdateMotion() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//アニメーションを更新する
		UpdateAnimeTime(ElapsedTime);
	}
	//----------------------------------------------------------------------------------------------------------
	//アニメーションを切り替える
	//----------------------------------------------------------------------------------------------------------
	void Player::AnimeChangeMotion(const wstring& key, bool looped) {
		ChangeAnimation(key);
		SetLooped(looped);
	}
	//----------------------------------------------------------------------------------------------------------
	//攻撃を受けたときの演出
	//----------------------------------------------------------------------------------------------------------
	void Player::Damage(CannonBase::CanonDirection LR) {
		if (!m_DamageFlag) {
			m_DamageFlag = true;
			auto PtrRedit = GetComponent<Rigidbody>();
			PtrRedit->SetVelocityZero();
			if (LR == CannonBase::CanonDirection::LEFT) {
				//左に飛ぶ
				GetComponent<Rigidbody>()->SetVelocity(Vec3(-3.0f, 0, 0.0f));
			}
			else {
				//右に飛ぶ
				GetComponent<Rigidbody>()->SetVelocity(Vec3(3.0f, 0, 0.0f));
				if (m_RightOrLeft == PlayerDirection::LEFT) {
					m_RightOrLeft = PlayerDirection::RIGHT;
				}
				else {
					m_RightOrLeft = PlayerDirection::LEFT;
				}
			}
			GetStateMachine()->ChangeState(DamageState1::Instance());
		}
	}

	//--------------------------------------------------------------------------------------
	//	class WaitState : public ObjState<Player>;
	//	用途: 待機状態
	//--------------------------------------------------------------------------------------
	shared_ptr<WaitState> WaitState::Instance() {
		static shared_ptr<WaitState> instance;
		if (!instance) {
			instance = shared_ptr<WaitState>(new WaitState);
		}
		return instance;
	}
	void WaitState::Enter(const shared_ptr<Player>& Obj) {
		Obj->AnimeChangeMotion(L"Wait_1", true);
		Obj->SetFps(49.0f);
	}
	void WaitState::Execute(const shared_ptr<Player>& Obj) {
		//アニメーション更新
		Obj->LoopedAnimeUpdateMotion();
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		//潰れて死んだらDiedアニメを流す
		if (Obj->GetDeath() == 1) {
			Obj->GetStateMachine()->ChangeState(DiedState::Instance());
		}
		//親がいなかったらFallアニメを流す
		if (!Obj->GetParentFlag()) {
			Obj->GetStateMachine()->ChangeState(FallState::Instance());
		}
		//左スティックの値が0以外ならWalkアニメを流す
		if (Obj->GetParentFlag() && Obj->GetMoveLeftVectorX()&& ScenePtr->GetStartFlag()) {
			Obj->GetStateMachine()->ChangeState(WalkState::Instance());
		}
	}
	void WaitState::Exit(const shared_ptr<Player>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class FallState : public ObjState<Player>;
	//	用途: 落ちてるとき
	//--------------------------------------------------------------------------------------
	shared_ptr<FallState> FallState::Instance() {
		static shared_ptr<FallState> instance;
		if (!instance) {
			instance = shared_ptr<FallState>(new FallState);
		}
		return instance;
	}
	void FallState::Enter(const shared_ptr<Player>& Obj) {
		Obj->AnimeChangeMotion(L"Down_loop", true);
		m_Timer = 0;
		m_FallFlag = false;
	}
	void FallState::Execute(const shared_ptr<Player>& Obj) {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_Timer += ElapsedTime;

		if (m_Timer >= 0.7f){
			Obj->AnimeChangeMotion(L"Fall", false);
			m_FallFlag = true;
			m_Timer = -10;
		}
		//潰れて死んだらDiedアニメを流す
		if (Obj->GetDeath() == 1) {
			Obj->GetStateMachine()->ChangeState(DiedState::Instance());
		}

		//アニメーション更新
		Obj->LoopedAnimeUpdateMotion();
		if (Obj->GetParentFlag() && m_FallFlag) {
			//煙だす
			Obj->LandingDirecting();
			Obj->GetStateMachine()->ChangeState(StandState::Instance());
		}
		else if (Obj->GetParentFlag()) {
			Obj->GetStateMachine()->ChangeState(LandingState::Instance());
		}
	}
	void FallState::Exit(const shared_ptr<Player>& Obj) {
		Obj->GetComponent<Rigidbody>()->SetVelocityZero();
	}
	//--------------------------------------------------------------------------------------
	//	class LandingState : public ObjState<Player>;
	//	用途: 着地
	//--------------------------------------------------------------------------------------
	shared_ptr<LandingState> LandingState::Instance() {
		static shared_ptr<LandingState> instance;
		if (!instance) {
			instance = shared_ptr<LandingState>(new LandingState);
		}
		return instance;
	}
	void LandingState::Enter(const shared_ptr<Player>& Obj) {
		Obj->AnimeChangeMotion(L"Down_landing", false);

			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"se5");
			m_AudioObjectPtr->Start(L"se5", XAUDIO2_NO_LOOP_REGION, 0.32f);
			Obj->SetNowMusic(L"se5");
	}
	void LandingState::Execute(const shared_ptr<Player>& Obj) {
		//アニメーション更新
		Obj->LoopedAnimeUpdateMotion();
		if (Obj->IsAnimeEnd()) {
			Obj->GetStateMachine()->ChangeState(WaitState::Instance());
		}
	}
	void LandingState::Exit(const shared_ptr<Player>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	class StandState : public ObjState<Player>;
	//	用途: 起き上がり
	//--------------------------------------------------------------------------------------
	shared_ptr<StandState> StandState::Instance() {
		static shared_ptr<StandState> instance;
		if (!instance) {
			instance = shared_ptr<StandState>(new StandState);
		}
		return instance;
	}
	void StandState::Enter(const shared_ptr<Player>& Obj) {
		Obj->AnimeChangeMotion(L"Stand", false);
		Obj->SetFps(45.0f);
		Obj->SetStandFlag(true);

		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"se6");
		m_AudioObjectPtr->Start(L"se6", XAUDIO2_NO_LOOP_REGION, 0.32f);
		Obj->SetNowMusic(L"se6");
	}
	void StandState::Execute(const shared_ptr<Player>& Obj) {
		//アニメーション更新
		Obj->LoopedAnimeUpdateMotion();
		if (Obj->IsAnimeEnd()) {
			Obj->GetStateMachine()->ChangeState(WaitState::Instance());
			Obj->SetStandFlag(false);
		}
	}
	void StandState::Exit(const shared_ptr<Player>& Obj) {

	}

	//--------------------------------------------------------------------------------------
	//	class WalkState : public ObjState<Player>;
	//	用途: 歩き状態
	//--------------------------------------------------------------------------------------
	shared_ptr<WalkState> WalkState::Instance() {
		static shared_ptr<WalkState> instance;
		if (!instance) {
			instance = shared_ptr<WalkState>
				(new WalkState);
		}
		return instance;
	}
	void WalkState::Enter(const shared_ptr<Player>& Obj) {
		Obj->SetFps(49.0f);
		Obj->AnimeChangeMotion(L"Walk", true);

		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"walk");
		m_AudioObjectPtr->Start(L"walk", XAUDIO2_LOOP_INFINITE, 0.28f);
		Obj->SetNowMusic(L"walk");
	}
	void WalkState::Execute(const shared_ptr<Player>& Obj) {
		//アニメーション更新
		Obj->LoopedAnimeUpdateMotion();
		//潰れて死んだらDiedアニメを流す
		if (Obj->GetDeath() == 1) {
			Obj->GetStateMachine()->ChangeState(DiedState::Instance());
		}
		//親が居なかったら落ちるアニメーション
		if (!Obj->GetParentFlag()) {
			Obj->GetStateMachine()->ChangeState(FallState::Instance());
		}
		//左スティックの値が0(入力されなくなった)ならWaitアニメを流す
		if (Obj->GetMoveLeftVectorX() == 0.0f) {
			Obj->GetStateMachine()->ChangeState(WaitState::Instance());
		}
	}
	void WalkState::Exit(const shared_ptr<Player>& Obj) {
		m_AudioObjectPtr->Stop(Obj->GetNowMusic());
	}

	//--------------------------------------------------------------------------------------
	//	class DiedState : public ObjState<Player>;
	//	用途: 死亡状態
	//--------------------------------------------------------------------------------------
	shared_ptr<DiedState> DiedState::Instance() {
		static shared_ptr<DiedState> instance;
		if (!instance) {
			instance = shared_ptr<DiedState>(new DiedState);
		}
		return instance;
	}
	void DiedState::Enter(const shared_ptr<Player>& Obj) {
		//死亡アニメを呼び出す
		Obj->AnimeChangeMotion(L"Died_1", false);
		//操作を受け付けなくする
		Obj->SetGameOverFlag(true);
		//Velocityを0にする
		Obj->GetComponent<Rigidbody>()->SetVelocityZero();

		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"se3");
		m_AudioObjectPtr->Start(L"se3", XAUDIO2_NO_LOOP_REGION, 1.0f);
		Obj->SetNowMusic(L"se3");
	}
	void DiedState::Execute(const shared_ptr<Player>& Obj) {
		//アニメーション更新
		Obj->LoopedAnimeUpdateMotion();
		//アニメーションが終わったら
		if (Obj->IsAnimeEnd()) {
			//ゲームオーバーシーンに遷移する
			Obj->SetFadeFlag(true);
		}
	}
	void DiedState::Exit(const shared_ptr<Player>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class GoalState : public ObjState<Player>;
	//	用途: ゴール到達状態
	//--------------------------------------------------------------------------------------
	shared_ptr<GoalState> GoalState::Instance() {
		static shared_ptr<GoalState> instance;
		if (!instance) {
			instance = shared_ptr<GoalState>(new GoalState);
		}
		return instance;
	}
	void GoalState::Enter(const shared_ptr<Player>& Obj) {
		Obj->SetFps(60.0f);
		Obj->AnimeChangeMotion(L"curtsey", false);
		Obj->SetGameClearFlag(true);
		Obj->GetComponent<Rigidbody>()->SetVelocityZero();
	}
	void GoalState::Execute(const shared_ptr<Player>& Obj) {
		//アニメーション更新
		Obj->LoopedAnimeUpdateMotion();
		if (Obj->IsAnimeEnd()) {
			Obj->SetFadeFlag(true);
		}
	}
	void GoalState::Exit(const shared_ptr<Player>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	class DamageState1 : public ObjState<Player>;
	//	用途: Damage状態
	//--------------------------------------------------------------------------------------
	shared_ptr<DamageState1> DamageState1::Instance() {
		static shared_ptr<DamageState1> instance;
		if (!instance) {
			instance = shared_ptr<DamageState1>(new DamageState1);
		}
		return instance;
	}
	void DamageState1::Enter(const shared_ptr<Player>& Obj) {
		Obj->SetFps(60.0f);
		if (Obj->GetRightOrLeft() == Player::PlayerDirection::RIGHT) {
			Obj->AnimeChangeMotion(L"Knockdown", false);
		}
		else {
			Obj->AnimeChangeMotion(L"Knockdown_front", false);
		}
	}
	void DamageState1::Execute(const shared_ptr<Player>& Obj) {
		//アニメーション更新
		Obj->LoopedAnimeUpdateMotion();
		if (Obj->IsAnimeEnd()) {
			Obj->GetStateMachine()->ChangeState(DamageState2::Instance());
		}
	}
	void DamageState1::Exit(const shared_ptr<Player>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	class DamageState2 : public ObjState<Player>;
	//	用途: Damage状態
	//--------------------------------------------------------------------------------------
	shared_ptr<DamageState2> DamageState2::Instance() {
		static shared_ptr<DamageState2> instance;
		if (!instance) {
			instance = shared_ptr<DamageState2>(new DamageState2);
		}
		return instance;
	}
	void DamageState2::Enter(const shared_ptr<Player>& Obj) {
		Obj->SetFps(60.0f);
		if (Obj->GetRightOrLeft() == Player::PlayerDirection::RIGHT) {
			Obj->AnimeChangeMotion(L"StandUp", false);
		}
		else {
			Obj->AnimeChangeMotion(L"Stand", false);
		}
		auto PtrRedit = Obj->GetComponent<Rigidbody>();
		PtrRedit->SetVelocityZero();
		Obj->SetStandFlag(true);
	}
	void DamageState2::Execute(const shared_ptr<Player>& Obj) {
		//アニメーション更新
		Obj->LoopedAnimeUpdateMotion();
		if (Obj->IsAnimeEnd()) {
			Obj->GetStateMachine()->ChangeState(WaitState::Instance());
		}
	}
	void DamageState2::Exit(const shared_ptr<Player>& Obj) {
		Obj->SetDamageFlag(false);
		Obj->SetStandFlag(false);
	}
}
//end basecross

