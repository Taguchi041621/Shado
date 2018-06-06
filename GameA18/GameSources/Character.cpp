/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	白い立方体
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
		m_VerticalTimer(0)
	{}

	void WhiteCube::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale);
		PtrTransform->SetQuaternion(m_StartQt);
		PtrTransform->SetPosition(m_StartPos);

		m_Rigidbody = AddComponent<Rigidbody>();

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");

		PtrDraw->SetAlpha(0.5f);
		PtrDraw->SetTextureResource(L"Red_TX");

		SetAlphaActive(true);
		//影をつける
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//ShadowPtr->SetMeshResource(L"DEFAULT_SQUARE");
		//--------------------------------------------------------
		//オブジェクトの影のコンストラクタ呼び出し
		GetStage()->AddGameObject<ShadowObject>(
			GetComponent<Transform>()->GetScale(),
			GetComponent<Transform>()->GetRotation(),
			*GetThis<GameObject>()
			);
		/*GetStage()->AddGameObject<ShadowObject2>(
			GetComponent<Transform>()->GetScale(),
			GetComponent<Transform>()->GetRotation(),
			*GetThis<GameObject>()
			);*/
	}

	void WhiteCube::OnUpdate() {

		float ElapsedTime = App::GetApp()->GetElapsedTime();

		m_HengTimer += ElapsedTime;
		m_VerticalTimer += ElapsedTime;
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

			/*if (m_VerticalMoveFlag)
				m_Rigidbody->SetVelocity(Vec3(0, m_Speed.y, 0));
			if (!m_VerticalMoveFlag)
				m_Rigidbody->SetVelocity(Vec3(0, -m_Speed.y, 0));

			if (m_VerticalTimer >= 3 && m_VerticalMoveFlag) {
				m_VerticalMoveFlag = false;
				m_VerticalTimer = 0;
			}
			if (m_VerticalTimer >= 3 && !m_VerticalMoveFlag) {
				m_VerticalMoveFlag = true;
				m_VerticalTimer = 0;
			}*/
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
		m_VerticalTimer(0)
	{}

	void BlueCube::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale);
		PtrTransform->SetQuaternion(m_StartQt);
		PtrTransform->SetPosition(m_StartPos);

		m_Rigidbody = AddComponent<Rigidbody>();

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");

		PtrDraw->SetAlpha(0.5f);
		PtrDraw->SetTextureResource(L"Blue_TX");

		SetAlphaActive(true);
		//影をつける
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//ShadowPtr->SetMeshResource(L"DEFAULT_SQUARE");
		//--------------------------------------------------------
		//オブジェクトの影のコンストラクタ呼び出し
		GetStage()->AddGameObject<ShadowObject>(
			GetComponent<Transform>()->GetScale(),
			GetComponent<Transform>()->GetRotation(),
			*GetThis<GameObject>()
			);
		/*GetStage()->AddGameObject<ShadowObject2>(
		GetComponent<Transform>()->GetScale(),
		GetComponent<Transform>()->GetRotation(),
		*GetThis<GameObject>()
		);*/
	}

	void BlueCube::OnUpdate() {

		float ElapsedTime = App::GetApp()->GetElapsedTime();

		m_HengTimer += ElapsedTime;
		m_VerticalTimer += ElapsedTime;
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

			/*if (m_VerticalMoveFlag)
			m_Rigidbody->SetVelocity(Vec3(0, m_Speed.y, 0));
			if (!m_VerticalMoveFlag)
			m_Rigidbody->SetVelocity(Vec3(0, -m_Speed.y, 0));

			if (m_VerticalTimer >= 3 && m_VerticalMoveFlag) {
			m_VerticalMoveFlag = false;
			m_VerticalTimer = 0;
			}
			if (m_VerticalTimer >= 3 && !m_VerticalMoveFlag) {
			m_VerticalMoveFlag = true;
			m_VerticalTimer = 0;
			}*/
		}
	}
	//--------------------------------------------------------------------------------------
	///	三角形のオブジェ
	//--------------------------------------------------------------------------------------
	Triangle::Triangle(const shared_ptr<Stage>& StagePtr,
		const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_StartScale(StartScale),
		m_StartQt(StartQt),
		m_StartPos(StartPos)
	{}

	void Triangle::OnCreate() {
		vector<VertexPositionNormalTexture> vertices;
		vector<VertexPositionNormal> new_vertices;

		vector<uint16_t> indices;
		MeshUtill::CreateTetrahedron(1.0f, vertices, indices);
		for (size_t i = 0; i < vertices.size(); i++) {
			VertexPositionNormal new_v;
			new_v.position = vertices[i].position;
			new_v.normal = vertices[i].normal;
			new_vertices.push_back(new_v);
		}
		m_MeshResource = MeshResource::CreateMeshResource(new_vertices, indices, false);

		//トランスフォーム3種の設定
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale);
		PtrTransform->SetQuaternion(m_StartQt);
		PtrTransform->SetPosition(m_StartPos);

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetFogEnabled(true);
		//自分に影が映りこむようにする
		PtrDraw->SetOwnShadowActive(true);
		//オブジェクトの形の設定
		PtrDraw->SetMeshResource(m_MeshResource);

		//影をつける
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(m_MeshResource);
		//--------------------------------------------------------
		//オブジェクトの影のコンストラクタ呼び出し
		GetStage()->AddGameObject<ShadowObject>(
			GetComponent<Transform>()->GetScale(),
			GetComponent<Transform>()->GetRotation(),
			*GetThis<GameObject>()
			);
	}

	void Triangle::OnUpdate() {
	}

	//--------------------------------------------------------------------------------------
	///	大砲の元
	//--------------------------------------------------------------------------------------
	CannonBase::CannonBase(const shared_ptr<Stage>& StagePtr,
		const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_StartScale(StartScale),
		m_StartQt(StartQt),
		m_StartPos(StartPos)
	{}

	void CannonBase::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale);
		PtrTransform->SetQuaternion(m_StartQt);
		PtrTransform->SetPosition(m_StartPos);

		//auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//PtrDraw->SetMeshResource(L"DEFAULT_CUBE");

		/*PtrDraw->SetAlpha(0.5f);
		PtrDraw->SetTextureResource(L"Red_TX");*/

		SetAlphaActive(true);
		//影をつける
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//ShadowPtr->SetMeshResource(L"DEFAULT_SQUARE");
		//--------------------------------------------------------
		//オブジェクトの影のコンストラクタ呼び出し
		GetStage()->AddGameObject<Cannon>(
			GetComponent<Transform>()->GetScale(),
			GetComponent<Transform>()->GetRotation(),
			*GetThis<GameObject>()
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
			*GetThis<GameObject>()
			);

	}

	void Goal::OnUpdate() {
		//OnTriggerEnter();
	}

	void Goal::OnTriggerEnter(){
	}
	//end basecross
}