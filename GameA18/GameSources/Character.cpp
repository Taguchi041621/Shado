/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	�Ԃ��u���b�N
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
		//�I�u�W�F�N�g�̉e�̃R���X�g���N�^�Ăяo��
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
				//�X�e�B�b�N�𑀍삵�ĂȂ��Ȃ�Z������
				if (!GetStage()->GetSharedGameObject<Player>(L"Player")->GetMoveRightVectorX()
					&& !GetStage()->GetSharedGameObject<Player>(L"Player")->GetMoveLeftVectorX()) {
					if (m_alpha <= 0.7f) {
						m_alpha += 0.05f;
					}
				}
				else {//��������
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
		//�I�u�W�F�N�g�̉e�̃R���X�g���N�^�Ăяo��
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
				//���E�ړ�����
				if (m_HengMove == MoveLR::L) {
					m_Rigidbody->SetVelocity(Vec3(-m_Speed.x, m_Speed.y, 0));
				}
				else {
					m_Rigidbody->SetVelocity(Vec3(m_Speed.x, m_Speed.y, 0));
				}
				//3�b���ƂɈړ�����������ς��
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
			//�E�X�e�B�b�N�𑀍삵�ĂȂ��Ȃ�Z������
			if (ScenePtr->GetStartFlag()) {
				if (!GetStage()->GetSharedGameObject<Player>(L"Player")->GetMoveRightVectorX()
					&& !GetStage()->GetSharedGameObject<Player>(L"Player")->GetMoveLeftVectorX()) {
					if (m_alpha <= 0.7f) {
						m_alpha += 0.05f;
					}
				}
				else {//��������
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
		//�I�u�W�F�N�g�̉e�̃R���X�g���N�^�Ăяo��
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
				//�X�e�B�b�N�𑀍삵�ĂȂ��Ȃ�Z������
				if (!GetStage()->GetSharedGameObject<Player>(L"Player")->GetMoveRightVectorX()
					&& !GetStage()->GetSharedGameObject<Player>(L"Player")->GetMoveLeftVectorX()) {
					if (m_alpha <= 0.7f) {
						m_alpha += 0.05f;
					}
				}
				else {//��������
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
	///	��C�̌�
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
		//�I�u�W�F�N�g�̉e�̃R���X�g���N�^�Ăяo��
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
	///	�����̃S�[���I�u�W�F
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
		//�I�u�W�F�N�g�̉e�̃R���X�g���N�^�Ăяo��
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
	///�@�����d��
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

	//������
	void StageLight::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();

		PtrTransform->SetPosition(m_Position);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetScale(m_Scale);

		Mat4x4 SpanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		SpanMat.affineTransformation(
			Vec3(0.1f, 1.0f, 0.1f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//���f�����f
		auto PtrDraw = AddComponent<PNTStaticModelDraw>();
		PtrDraw->SetMeshResource(L"LIGHT_MESH");
		PtrDraw->SetMeshToTransformMatrix(SpanMat);

	}

	void StageLight::OnUpdate() {
	}

	//end basecross
}