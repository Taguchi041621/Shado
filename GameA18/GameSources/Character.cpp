/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	赤いブロック
	//--------------------------------------------------------------------------------------
	RedCube::RedCube(const shared_ptr<Stage>& StagePtr,
		const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos, const Vec3& StartSpeed, const bool& Move) 
		:
		GameObject(StagePtr),
		m_StartScale(StartScale),
		m_StartQt(StartQt),
		m_StartPos(StartPos),
		m_MoveFlag(Move),
		m_Speed(StartSpeed),
		m_HengTimer(0),
		m_VerticalTimer(0),
		m_alpha(0.7f)
	{}

	void RedCube::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale);
		PtrTransform->SetQuaternion(m_StartQt);
		PtrTransform->SetPosition(m_StartPos);

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");

		PtrDraw->SetAlpha(1.0f);
		PtrDraw->SetTextureResource(L"Red_TX");

		SetAlphaActive(true);

		//--------------------------------------------------------
		//オブジェクトの影のコンストラクタ呼び出し
		GetStage()->AddGameObject<ShadowObject>(
			GetComponent<Transform>()->GetScale(),
			GetComponent<Transform>()->GetRotation(),
			GetThis<GameObject>()
			);
	}

	void RedCube::OnUpdate() {
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		if (!ScenePtr->GetPauseFlag()) {
			if (ScenePtr->GetStartFlag()) {
				//スティックを操作してないなら濃くする
				if (!GetStage()->GetSharedGameObject<Player>(L"Player")->GetMoveRightVectorX()
					&& !GetStage()->GetSharedGameObject<Player>(L"Player")->GetMoveLeftVectorX()) {
					if (m_alpha <= 0.7f) {
						m_alpha += 0.05f;
					}
				}
				else {//薄くする
					if (m_alpha >= 0.3f) {
						m_alpha += -0.05f;
					}
				}
			}
		}
		if (ScenePtr->GetStartFlag()) {
			GetComponent<BcPNTStaticDraw>()->SetAlpha(m_alpha);
		}
	}

	BlueCube::BlueCube(const shared_ptr<Stage>& StagePtr,
		const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos, const Vec3& StartSpeed, const bool& Move) :
		GameObject(StagePtr),
		m_StartScale(StartScale),
		m_StartQt(StartQt),
		m_StartPos(StartPos),
		m_MoveFlag(Move),
		m_HengMove(MoveLR::R),
		m_Speed(StartSpeed),
		m_HengTimer(0),
		m_alpha(0.7f)
	{}

	void BlueCube::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale);
		PtrTransform->SetQuaternion(m_StartQt);
		PtrTransform->SetPosition(m_StartPos);

		m_Rigidbody = AddComponent<Rigidbody>();

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");

		PtrDraw->SetAlpha(1.0f);
		PtrDraw->SetTextureResource(L"Blue_TX");

		

		SetAlphaActive(true);
		//--------------------------------------------------------
		//オブジェクトの影のコンストラクタ呼び出し
		GetStage()->AddGameObject<ShadowObject>(
			GetComponent<Transform>()->GetScale(),
			GetComponent<Transform>()->GetRotation(),
			GetThis<GameObject>()
			);
	}

	void BlueCube::OnUpdate() {

		float ElapsedTime = App::GetApp()->GetElapsedTime();

		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		if (!ScenePtr->GetPauseFlag()) {
			m_HengTimer += ElapsedTime;
			if (m_MoveFlag) {
				//左右移動する
				if (m_HengMove == MoveLR::L) {
					m_Rigidbody->SetVelocity(Vec3(-m_Speed.x, m_Speed.y, 0));
				}
				else {
					m_Rigidbody->SetVelocity(Vec3(m_Speed.x, m_Speed.y, 0));
				}
				//3秒ごとに移動する方向が変わる
				if (m_HengTimer >= 3.0f) {
					if (m_HengMove == MoveLR::L) {
						m_HengMove = MoveLR::R;
					}
					else {
						m_HengMove = MoveLR::L;
					}
					m_HengTimer = 0;
				}
			}
			//右スティックを操作してないなら濃くする
			if (ScenePtr->GetStartFlag()) {
				if (!GetStage()->GetSharedGameObject<Player>(L"Player")->GetMoveRightVectorX()
					&& !GetStage()->GetSharedGameObject<Player>(L"Player")->GetMoveLeftVectorX()) {
					if (m_alpha <= 0.7f) {
						m_alpha += 0.05f;
					}
				}
				else {//薄くする
					if (m_alpha >= 0.3f) {
						m_alpha += -0.05f;
					}
				}
			}
		}

		else {
			m_Rigidbody->SetVelocity(Vec3(0));
		}
		if (ScenePtr->GetStartFlag()) {
			GetComponent<BcPNTStaticDraw>()->SetAlpha(m_alpha);
		}
	}

	YellowCube::YellowCube(const shared_ptr<Stage>& StagePtr,
		const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos, const Vec3& StartSpeed, const bool& Move) :
		GameObject(StagePtr),
		m_StartScale(StartScale),
		m_StartQt(StartQt),
		m_StartPos(StartPos),
		m_MoveFlag(Move),
		m_VerticalMove(MoveUpDown::DOWN),
		m_Speed(StartSpeed),
		m_VerticalTimer(0),
		m_alpha(0.7f)
	{}

	void YellowCube::OnCreate() {

		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale);
		PtrTransform->SetQuaternion(m_StartQt);
		PtrTransform->SetPosition(m_StartPos);

		m_Rigidbody = AddComponent<Rigidbody>();

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");

		PtrDraw->SetAlpha(1.0f);
		PtrDraw->SetTextureResource(L"Yellow_TX");

		SetAlphaActive(true);

		//--------------------------------------------------------
		//オブジェクトの影のコンストラクタ呼び出し
		GetStage()->AddGameObject<ShadowObject>(
			GetComponent<Transform>()->GetScale(),
			GetComponent<Transform>()->GetRotation(),
			GetThis<GameObject>()
			);
	}

	void YellowCube::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		if (!ScenePtr->GetPauseFlag()) {
			m_VerticalTimer += ElapsedTime;
			if (m_MoveFlag) {
				if (m_VerticalMove == MoveUpDown::DOWN) {
					m_Rigidbody->SetVelocity(Vec3(0, -m_Speed.y, 0));
				}
				else{
					m_Rigidbody->SetVelocity(Vec3(0, m_Speed.y, 0));
				}
				if (m_VerticalTimer >= 3.0f) {
					if (m_VerticalMove == MoveUpDown::DOWN) {
						m_VerticalMove = MoveUpDown::UP;
					}
					else {
						m_VerticalMove = MoveUpDown::DOWN;
					}
					m_VerticalTimer = 0.0f;
				}
			}
			if (ScenePtr->GetStartFlag()) {
				//スティックを操作してないなら濃くする
				if (!GetStage()->GetSharedGameObject<Player>(L"Player")->GetMoveRightVectorX()
					&& !GetStage()->GetSharedGameObject<Player>(L"Player")->GetMoveLeftVectorX()) {
					if (m_alpha <= 0.7f) {
						m_alpha += 0.05f;
					}
				}
				else {//薄くする
					if (m_alpha >= 0.3f) {
						m_alpha += -0.05f;
					}
				}
			}
		}
		else {
			m_Rigidbody->SetVelocity(Vec3(0));
		}
		if (ScenePtr->GetStartFlag()) {
			GetComponent<BcPNTStaticDraw>()->SetAlpha(m_alpha);
		}
	}
	//--------------------------------------------------------------------------------------
	///	大砲の元
	//--------------------------------------------------------------------------------------
	CannonBase::CannonBase(const shared_ptr<Stage>& StagePtr,
		const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos, CanonDirection LR) :
		GameObject(StagePtr),
		m_StartScale(StartScale),
		m_StartQt(StartQt),
		m_StartPos(StartPos),
		m_LR(LR)
	{}

	void CannonBase::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale);
		PtrTransform->SetQuaternion(m_StartQt);
		PtrTransform->SetPosition(m_StartPos);

		SetAlphaActive(true);
		//---------------------------------------------------------------------------
		//オブジェクトの影のコンストラクタ呼び出し
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		GetStage()->AddGameObject<Cannon>(
			DataDir+L"Cannon\\",
			GetComponent<Transform>()->GetScale(),
			GetComponent<Transform>()->GetRotation(),
			GetThis<GameObject>(),
			m_LR
			);
	}

	//--------------------------------------------------------------------------------------
	///	現実のゴールオブジェ
	//--------------------------------------------------------------------------------------
	Goal::Goal(const shared_ptr<Stage>& StagePtr,
		const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_StartScale(StartScale),
		m_StartQt(StartQt),
		m_StartPos(StartPos)
	{}

	void Goal::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(0.80f, 1.60f, 1);
		PtrTransform->SetQuaternion(m_StartQt);
		PtrTransform->SetPosition(m_StartPos);

		//------------------------------------------------------------------
		//オブジェクトの影のコンストラクタ呼び出し
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		GetStage()->AddGameObject<ShadowGoal>(
			DataDir + L"Door\\",
			GetComponent<Transform>()->GetScale(),
			GetComponent<Transform>()->GetRotation(),
			GetThis<GameObject>()
			);

	}

	//--------------------------------------------------------------------------------------
	///　懐中電灯
	//--------------------------------------------------------------------------------------
	StageLight::StageLight(const shared_ptr<Stage>& StagePtr,
		const Vec3& Position,
		const Vec3& Rotation,
		const Vec3& Scale
	) :
		GameObject(StagePtr),
		m_Position(Position),
		m_Rotation(Rotation),
		m_Scale(Scale)
	{
	}
	StageLight::~StageLight() {}

	//初期化
	void StageLight::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetPosition(m_Position);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetScale(m_Scale);

		Mat4x4 SpanMat; // モデルとトランスフォームの間の差分行列
		SpanMat.affineTransformation(
			Vec3(0.1f, 1.0f, 0.1f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//モデル反映
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		PtrDraw->SetMeshResource(L"LIGHT_MESH");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);

	}

	void StageLight::OnUpdate() {
	}

	//end basecross
}