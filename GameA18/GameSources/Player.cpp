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
		m_MaxSpeed(7.0f),	//最高速度
		m_Decel(0.65f),	//減速値
		m_Mass(0.5f)	//質量
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.1f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, -0.55f, 0.0f)
		);
		m_ToAnimeMatrixRight.affineTransformation(
			Vec3(-0.1f, 0.1f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, -0.55f, 0.0f)
		);

	}


	Vec3 Player::GetMoveVector() const {
		Vec3 Angle(0, 0, 0);
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].fThumbLX != 0 || CntlVec[0].fThumbLY != 0) {
				float MoveLength = 0;	//動いた時のスピード
				auto PtrTransform = GetComponent<Transform>();
				auto PtrCamera = OnGetDrawCamera();
				//進行方向の向きを計算
				Vec3 Front = PtrTransform->GetPosition() - PtrCamera->GetEye();
				Front.y = 0;
				Front.normalize();
				//進行方向向きからの角度を算出
				float FrontAngle = atan2(Front.z, Front.x);
				//コントローラの向き計算
				float MoveX = CntlVec[0].fThumbLX;
				float MoveZ = CntlVec[0].fThumbLY;
				Vec2 MoveVec(MoveX, MoveZ);
				float MoveSize = MoveVec.length();
				//コントローラの向きから角度を計算
				float CntlAngle = atan2(-MoveX, MoveZ);
				//トータルの角度を算出
				float TotalAngle = FrontAngle + CntlAngle;
				//角度からベクトルを作成
				Angle = Vec3(cos(TotalAngle), 0, sin(TotalAngle));
				//正規化する
				Angle.normalize();
				//移動サイズを設定。
				Angle *= MoveSize;
				//Y軸は変化させない
				Angle.y = 0;
			}
		}
		return Angle;
	}

	void Player::MovePlayer() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		Vec3 Angle = GetMoveVector();
		//Rigidbodyを取り出す
		auto PtrRedit = GetComponent<Rigidbody>();
		auto Velo = PtrRedit->GetVelocity();
		if (Angle.length() <= 0.0f && Velo.y == 0.0f) {
			//コントローラを離したとき対策
			Velo *= GetDecel();
			PtrRedit->SetVelocity(Velo);
			return;
		}
		//Transform
		auto PtrTransform = GetComponent<Transform>();
		//現在の速度を取り出す
		//目的地を最高速度を掛けて求める
		auto Target = Angle * GetMaxSpeed();
		//目的地に向かうために力のかける方向を計算する
		//Forceはフォースである
		auto Force = Target - Velo;
		//yは0にする
		Force.y = 0;
		//加速度を求める
		auto Accel = Force / GetMass();
		//ターン時間を掛けたものを速度に加算する
		Velo += (Accel * ElapsedTime);
		//ヴェロシティのz方向を0にする
		Velo.z = 0;
		//速度を設定する
		PtrRedit->SetVelocity(Velo);
		//回転の計算
		if (Angle.length() > 0.0f) {
			auto UtilPtr = GetBehavior<UtilBehavior>();
			UtilPtr->RotToHead(Angle, 1.0f);
		}
	}
	//衝突している時
	void Player::OnCollisionExcute(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto obj : OtherVec) {
			//シャドウオブジェクトを検出
			auto ShadowPtr = dynamic_pointer_cast<ShadowObject>(obj);
			//シャドウオブジェクトだったら
			if (ShadowPtr) {
				//シャドウオブジェクトの移動した距離を出す関数を呼び出し、
				//プレイヤーのポジションに加える
				//auto pos = GetComponent<Transform>()->GetPosition() + ShadowPtr->GetPoorBefor();
				//ポジションを適用する
				//GetComponent<Transform>()->SetPosition(pos);
				GetComponent<Transform>()->SetParent(ShadowPtr);
			}
		}
	}
	void Player::OnCollisionExit(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto obj : OtherVec) {
			//シャドウオブジェクトを検出
			auto ShadowPtr = dynamic_pointer_cast<ShadowObject>(obj);
			if (ShadowPtr == GetComponent<Transform>()->GetParent()) {
				GetComponent<Transform>()->SetParent(nullptr);
			}
		}
	}

	//初期化
	void Player::OnCreate() {
		CameraPosZ = -5;
		m_CameraNumber = 0;
		//初期位置などの設定
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(0.0f, 3.5f, -0.1f);

		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(30.0f);

		//Rigidbodyをつける
		auto PtrRedid = AddComponent<Rigidbody>();
		//衝突判定をつける
		auto PtrCol = AddComponent<CollisionSphere>();
		PtrCol->SetIsHitAction(IsHitAction::Auto);
		//デバッグ用文字列をつける
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
		//影をつける（シャドウマップを描画する）
		auto ShadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//描画するテクスチャを設定
		PtrDraw->SetTextureResource(L"TRACE_TX");
		//透明処理
		SetAlphaActive(true);
		//カメラを得る
		auto PtrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (PtrCamera) {
			PtrCamera->SetTargetObject(GetThis<GameObject>());
		}
	}

	//更新
	void Player::OnUpdate() {
		//プレイヤーの移動
		MovePlayer();

		//重力を加える
		auto PtrGrav = GetBehavior<Gravity>();
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
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) 
			{
				m_CameraNumber -= 1;
			}
			else if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				m_CameraNumber += 1;
			}
		}

		if (m_CameraNumber < 0) {
			m_CameraNumber = 2;
		}
		if (m_CameraNumber > 2) {
			m_CameraNumber = 0;
		}
		auto PtrMCamera = dynamic_pointer_cast<MyCamera>(GetStage()->GetView()->GetTargetCamera());
		PtrMCamera->SetToTargetLerp(0.5);

	    auto TargetPos = this->GetComponent<Transform>()->GetPosition();
		Vec3 ArmVec(0, 0.0f, CameraPosZ);
		Vec3 Eye = TargetPos + ArmVec;
		PtrCamera->SetAt(TargetPos);
		PtrCamera->SetEye(Eye);

		if (CameraPosZ > -10)
		{
			CameraPosFlag = true;
		}
		else if (CameraPosZ < -10)
		{
			CameraPosFlag = false;
		}
		switch (m_CameraNumber)
		{
		case 0:
		{
			if (CameraPosZ == -5)
			{
				break;
			}
			CameraPosZ += 0.2;
			if (CameraPosZ > -5)
			{
				CameraPosZ = -5;
			}
			break;
		}

		case 1:
		{
			if (CameraPosZ == -10)
			{
				break;
			}
			if (CameraPosFlag)
			{
				CameraPosZ -= 0.2;
			}
			else if (!CameraPosFlag)
			{
				CameraPosZ += 0.2;
			}

			if (CameraPosZ >= -10.2f && CameraPosZ <= -9.8f)
			{
				CameraPosZ = -10;
			}

			break;
		}
		case 2:
		{
			if (CameraPosZ == -15)
			{
				break;
			}
			CameraPosZ -= 0.2;
			if (CameraPosZ < -15)
			{
				CameraPosZ = -15;
			}
			break;
		}

		case 3:
		{

		}
		break;
		}
	}
	void Player::PlayerHP() {
		m_PlayerHP = 3;

		auto PlayerPos = this->GetComponent<Transform>()->GetPosition();
		//落下死
		if (PlayerPos.y < -5)
		{
			m_PlayerHP = 0;
		}

		if (m_PlayerHP == 0)
		{
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
		wstring str = FPS + PositionStr + RididStr +  HitObjectStr;
		//文字列をつける
		auto PtrString = GetComponent<StringSprite>();
		PtrString->SetText(str);
	}


}
//end basecross

