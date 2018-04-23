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
		SS5ssae(StagePtr, BaseDir, L"Idea1.ssae", L"Walk"),
		m_MaxSpeed(40.0f),	//最高速度
		m_Decel(0.65f),	//減速値
		m_Mass(0.5f)	//質量
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.1f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(-0.3f, 0.5f, 0.0f)
		);
		m_ToAnimeMatrixRight.affineTransformation(
			Vec3(-0.1f, 0.1f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.3f, 0.5f, 0.0f)
		);

	}


	float Player::GetMoveVector() const {
		float MoveX = 0;
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].fThumbLX != 0) {
				//コントローラの向き計算
				MoveX = CntlVec[0].fThumbLX;
			}
		}
		return MoveX;
	}

	//モーションを実装する関数群
	//移動して向きを移動方向にする
	//移動距離を返す
	float  Player::MoveRotationMotion() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto MoveX = GetMoveVector();
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
		if (MoveX >= 0.0f) {
			SetToAnimeMatrix(m_ToAnimeMatrixRight);
		}
		else {
			SetToAnimeMatrix(m_ToAnimeMatrixLeft);
		}
		//MoveXを返す
		return MoveX;
	}

	void Player::OnCollision(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto &obj : OtherVec) {
			//シャドウオブジェクトを検出
			auto ShadowPtr = dynamic_pointer_cast<ShadowObject>(obj);
			//当たったのがシャドウオブジェクトで
			//ペアレント化してるオブジェクトが無かったらペアレント化
			if (ShadowPtr && !GetComponent<Transform>()->GetParent()) {
				//イデアの判定
				SPHERE t;
				t.m_Center = GetComponent<Transform>()->GetPosition();
				t.m_Radius = GetComponent<Transform>()->GetScale().y;
				//シャドウの判定
				OBB p;
				p.m_Center = obj->GetComponent<Transform>()->GetPosition();
				//p.m_Center.y += obj->GetComponent<Transform>()->GetScale().y / 4;
				p.m_Size = obj->GetComponent<Transform>()->GetScale()/2.0f;
				//p.m_Size.y /= 2.0f;
				Vec3 HitPoint;
				//イデアとシャドウの接触判定
				if (HitTest::SPHERE_OBB(t, p, HitPoint)) {
					//ペアレント化する
					GetComponent<Transform>()->SetParent(ShadowPtr);
					HitPoint.y += GetComponent<Transform>()->GetScale().y/2.0f;
					GetComponent<Transform>()->SetWorldPosition(HitPoint);
				}
			}
		}
	}

	//衝突している時
	void Player::OnCollisionExcute(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto &obj : OtherVec) {
			if (GetComponent<Transform>()->GetParent() == obj) {
				//イデアの判定
				SPHERE t;
				t.m_Center = GetComponent<Transform>()->GetPosition();
				t.m_Radius = GetComponent<Transform>()->GetScale().y;
				//シャドウの判定
				OBB p;
				p.m_Center = obj->GetComponent<Transform>()->GetPosition();
				p.m_Size = obj->GetComponent<Transform>()->GetScale()/2.0f;
				Vec3 HitPoint;
				//イデアとシャドウの接触判定
				if (HitTest::SPHERE_OBB(t, p, HitPoint)) {
					HitPoint.y += GetComponent<Transform>()->GetScale().y/2.0f;
					GetComponent<Transform>()->SetWorldPosition(HitPoint);
				}
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
				//イデアの判定
				SPHERE t;
				t.m_Center = GetComponent<Transform>()->GetPosition();
				t.m_Radius = GetComponent<Transform>()->GetScale().y/2.0f;
				//シャドウの判定
				OBB p;
				p.m_Center = obj->GetComponent<Transform>()->GetPosition();
				p.m_Size = obj->GetComponent<Transform>()->GetScale()/2.0f;
				Vec3 HitPoint;
				//イデアとシャドウの接触判定
				if (!HitTest::SPHERE_OBB(t, p,HitPoint)){
					//ペアレント化を解く
					GetComponent<Transform>()->ClearParent();
				}
			}
		}
	}

	//初期化
	void Player::OnCreate() {
		CameraPosZ = -10;
		//初期位置などの設定
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
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
		auto PtrCol = AddComponent<CollisionSphere>();
		PtrCol->SetIsHitAction(IsHitAction::Auto);
		//コリジョンを表示する場合は以下を設定
		PtrCol->SetDrawActive(true);
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
		//WaitStateの初期化実行を行う
		m_StateMachine->GetCurrentState()->Enter(GetThis<Player>());
	}

	//更新
	void Player::OnUpdate() {

		//ステートマシンのUpdateを行う
		//この中でステートの切り替えが行われる
		m_StateMachine->Update();
		//プレイヤーの移動
		MoveRotationMotion();

		//重力を加える
		auto PtrGrav = GetBehavior<Gravity>();
		PtrGrav->SetGravity(Vec3(0.0f,-4.9f,0.0f));
		PtrGrav->Execute();
		//カメラを得る
		//auto PtrCamera = dynamic_pointer_cast<LookAtCamera>(OnGetDrawCamera());
		//if (PtrCamera) {
		//	//LookAtCameraである
		//	//LookAtCameraに注目するオブジェクト（プレイヤー）の設定
		//	PtrCamera->SetTargetObject(GetThis<GameObject>());
		//	//playerの位置とカメラ位置を同期する
		//	auto p_pos = GetThis<GameObject>()->GetComponent<Transform>()->GetPosition();
		//	PtrCamera->SetEye(Vec3(p_pos.x, p_pos.y+10.0f, -20.0f));
		//}


	}

	void Player::OnUpdate2() {
		//文字列の表示
		DrawStrings();

		CameraChanger();

		PlayerHP();


	}

	void Player::CameraChanger() {
		auto PtrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
				CameraPosZ += 0.2;
				if (CameraPosZ >= -10) {
					CameraPosZ = -10;
				}
			}
			else if (CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER){
				CameraPosZ -= 0.2;
				if (CameraPosZ <= -20) {
					CameraPosZ = -20;
				}
			}
		}

	    auto TargetPos = this->GetComponent<Transform>()->GetWorldPosition();
		Vec3 ArmVec(0, 0.0f, CameraPosZ);
		Vec3 Eye = TargetPos + ArmVec;
		PtrCamera->SetAt(TargetPos);
		PtrCamera->SetEye(Eye);
	}
	void Player::PlayerHP() {
		m_PlayerHP = 3;

		auto PlayerPos = this->GetComponent<Transform>()->GetPosition();
		//落下死
		if (PlayerPos.y < -5){
			m_PlayerHP = 0;
		}

		if (m_PlayerHP == 0){
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOver");
		}
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
		wstring WPositionStr(L"WPosition:\t");
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
		Obj->AnimeChangeMotion(L"Walk", true);
	}
	//ステート実行中に毎ターン呼ばれる関数
	void WaitState::Execute(const shared_ptr<Player>& Obj) {
		//アニメーション更新
		Obj->LoopedAnimeUpdateMotion();
	}
	//ステートにから抜けるときに呼ばれる関数
	void WaitState::Exit(const shared_ptr<Player>& Obj) {
	}

}
//end basecross

