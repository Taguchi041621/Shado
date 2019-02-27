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
	WhiteCube::WhiteCube(const shared_ptr<Stage>& StagePtr,
		const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos, const Vec3& StartSpeed, const bool& Move) :
		GameObject(StagePtr),
		m_StartScale(StartScale),
		m_StartQt(StartQt),
		m_StartPos(StartPos),
		m_MoveFlag(Move),
		m_HengMoveFlag(true),
		m_VerticalMoveFlag(true),
		m_Speed(StartSpeed),
		m_HengTimer(0),
		m_VerticalTimer(0),
		m_alpha(0.7f)
	{}

	void WhiteCube::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale);
		PtrTransform->SetQuaternion(m_StartQt);
		PtrTransform->SetPosition(m_StartPos);

		m_Rigidbody = AddComponent<Rigidbody>();

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

	void WhiteCube::OnUpdate() {

		float ElapsedTime = App::GetApp()->GetElapsedTime();

		m_HengTimer += ElapsedTime;
		m_VerticalTimer += ElapsedTime;
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		if (!ScenePtr->GetPauseFlag()) {
			if (m_MoveFlag) {
				if (m_HengMoveFlag)
					m_Rigidbody->SetVelocity(Vec3(-m_Speed.x, m_Speed.y, 0));
				if (!m_HengMoveFlag)
					m_Rigidbody->SetVelocity(Vec3(m_Speed.x, m_Speed.y, 0));

				if (m_HengTimer >= 3 && m_HengMoveFlag) {
					m_HengMoveFlag = false;
					m_HengTimer = 0;
				}
				if (m_HengTimer >= 3 && !m_HengMoveFlag) {
					m_HengMoveFlag = true;
					m_HengTimer = 0;
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
		m_HengMoveFlag(true),
		m_VerticalMoveFlag(true),
		m_Speed(StartSpeed),
		m_HengTimer(0),
		m_VerticalTimer(0),
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

		m_HengTimer += ElapsedTime;
		m_VerticalTimer += ElapsedTime;
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		if (!ScenePtr->GetPauseFlag()) {
			if (m_MoveFlag) {
				if (m_HengMoveFlag)
					m_Rigidbody->SetVelocity(Vec3(-m_Speed.x, m_Speed.y, 0));
				if (!m_HengMoveFlag)
					m_Rigidbody->SetVelocity(Vec3(m_Speed.x, m_Speed.y, 0));

				if (m_HengTimer >= 3 && m_HengMoveFlag) {
					m_HengMoveFlag = false;
					m_HengTimer = 0;
				}
				if (m_HengTimer >= 3 && !m_HengMoveFlag) {
					m_HengMoveFlag = true;
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
		m_HengMoveFlag(true),
		m_VerticalMoveFlag(true),
		m_Speed(StartSpeed),
		m_HengTimer(0),
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
			m_HengTimer += ElapsedTime;
			m_VerticalTimer += ElapsedTime;
			if (m_MoveFlag) {
				if (m_HengMoveFlag)
					m_Rigidbody->SetVelocity(Vec3(0, -m_Speed.y, 0));
				if (!m_HengMoveFlag)
					m_Rigidbody->SetVelocity(Vec3(0, m_Speed.y, 0));

				if (m_HengTimer >= 3 && m_HengMoveFlag) {
					m_HengMoveFlag = false;
					m_HengTimer = 0;
				}
				if (m_HengTimer >= 3 && !m_HengMoveFlag) {
					m_HengMoveFlag = true;
					m_HengTimer = 0;
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
	///	大砲の元(左false,右true)
	//--------------------------------------------------------------------------------------
	CannonBase::CannonBase(const shared_ptr<Stage>& StagePtr,
		const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos, bool LR) :
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
		//オブジェクトの影のコンストラクタ呼び出し
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		//左向き
		GetStage()->AddGameObject<Cannon>(
			DataDir+L"Cannon\\",
			GetComponent<Transform>()->GetScale(),
			GetComponent<Transform>()->GetRotation(),
			GetThis<GameObject>(),
			m_LR
			);
	}

	void CannonBase::OnUpdate() {
	}

	//--------------------------------------------------------------------------------------
	///	ゴールオブジェ
	//--------------------------------------------------------------------------------------

	Goal::Goal(const shared_ptr<Stage>& StagePtr,
		const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_StartScale(StartScale),
		m_StartQt(StartQt),
		m_StartPos(StartPos)
	{}

	void Goal::OnCreate() {
		vector<VertexPositionNormalTexture> vertices;
		vector<VertexPositionNormal> new_vertices;

		vector<uint16_t> indices;
		MeshUtill::CreateCube(1.0f, vertices, indices);
		for (size_t i = 0; i < vertices.size(); i++) {
			VertexPositionNormal new_v;
			new_v.position = vertices[i].position;
			new_v.normal = vertices[i].normal;
			new_vertices.push_back(new_v);
		}
		m_MeshResource = MeshResource::CreateMeshResource(new_vertices, indices, false);

		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(0.80f, 1.60f, 1);
		PtrTransform->SetQuaternion(m_StartQt);
		PtrTransform->SetPosition(m_StartPos);

		//auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//PtrDraw->SetMeshResource(m_MeshResource);

		//影をつける
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//ShadowPtr->SetMeshResource(m_MeshResource);
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

	void Goal::OnUpdate() {
		//OnTriggerEnter();
	}

	void Goal::OnTriggerEnter(){
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
		//m_Rotation = m_Rotation*(DegToRad);
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