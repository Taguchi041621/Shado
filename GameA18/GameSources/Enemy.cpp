#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//��C
	//--------------------------------------------------------------------------------------
	Cannon::Cannon(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
		const Vec3& Scale, const Vec3& Rotation, weak_ptr<GameObject> Obj, CannonBase::CanonDirection LR)
		: SS5ssae(StagePtr, BaseDir, L"Cannon.ssae", L"Fire"),
		m_Scale(Scale), m_Rotation(Rotation), m_Obj(Obj), m_ScaleZ(0.05f), m_CoolTime(0), m_BulletFlag(false),m_LR(LR)
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.13f, 0.12f, 0.7f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.0f, -0.01f, 0.0f)
		);
		m_ToAnimeMatrixRight.affineTransformation(
			Vec3(-0.13f, 0.12f, 0.7f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.0f, -0.01f, 0.0f)
		);
	}

	Cannon::~Cannon() {}
	//������
	void Cannon::OnCreate() {
		//�X�P�[����Z���Œ�̑傫����
		m_Scale.z = m_ScaleZ;

		auto PtrTransform = GetComponent<Transform>();
		//�e�̃X�P�[��,�p�x,�|�W�V�����̐ݒ�
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(ShadowLocation());

		//�e�N���X�̃N���G�C�g���Ă�
		SS5ssae::OnCreate();
		//�l�͕b������̃t���[����
		SetFps(60);
		//�A�j���[�V�����̃��[�v�ݒ�
		SetLooped(false);
		if (m_LR == CannonBase::CanonDirection::LEFT) {
			//�A�j���[�V�����ɂ����郁�g���b�N�X�̐ݒ�
			SetToAnimeMatrix(m_ToAnimeMatrixLeft);
		}
		else {
			//�A�j���[�V�����ɂ����郁�g���b�N�X�̐ݒ�
			SetToAnimeMatrix(m_ToAnimeMatrixRight);
		}
		//SetAlphaActive(true);
		//auto PtrCol = AddComponent<CollisionObb>();
		//PtrCol->SetDrawActive(true);
		UpdateAnimeTime(0);
	}

	//�ω�
	void Cannon::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		if (!m_BulletFlag) {
			m_CoolTime += ElapsedTime;
			UpdateAnimeTime(0);
		}

		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		if (!ScenePtr->GetPauseFlag()) {
			if (m_CoolTime >= 5)
			{
				m_BulletFlag = true;
				ChangeAnimation(L"Fire");
				m_CoolTime = 0;
			}
			if (m_BulletFlag) {
				UpdateAnimeTime(ElapsedTime);

				if (IsAnimeEnd()) {
					//������
					if (m_LR == CannonBase::CanonDirection::LEFT) {
						GetStage()->AddGameObject<Bullet>(
							GetComponent<Transform>()->GetScale(),
							GetComponent<Transform>()->GetRotation(),
							GetComponent<Transform>()->GetPosition() - Vec3(1, -0.4f, 0),
							m_LR
							);
						//������
						GetStage()->AddGameObject<DirectingRing>(GetComponent<Transform>()->GetWorldPosition(),
							Vec3(1.5f, 1.5f, 0.05f), Vec3(-1.0f, 0.5f, 0.0f), L"Smoke_Black_TX");
					}
					//�E����
					else {
						GetStage()->AddGameObject<Bullet>(
							GetComponent<Transform>()->GetScale(),
							GetComponent<Transform>()->GetRotation(),
							GetComponent<Transform>()->GetPosition() - Vec3(-1, -0.4f, 0),
							m_LR
							);
						//������
						GetStage()->AddGameObject<DirectingRing>(GetComponent<Transform>()->GetWorldPosition(),
							Vec3(1.5f, 1.5f, 0.05f), Vec3(1.0f, 0.5f, 0.0f), L"Smoke_Black_TX");

					}
					m_BulletFlag = false;


					if (m_StopNowMusic != L"")
					{
						m_AudioObjectPtr->Stop(m_StopNowMusic);
					}
					wstring DataDir;
					//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
					//App::GetApp()->GetAssetsDirectory(DataDir);
					//�e�Q�[���͈ȉ��̂悤�Ƀf�[�^�f�B���N�g�����擾���ׂ�
					App::GetApp()->GetDataDirectory(DataDir);

					m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
					m_AudioObjectPtr->AddAudioResource(L"se4");
					m_AudioObjectPtr->Start(L"se4", XAUDIO2_NO_LOOP_REGION, 0.1f);
					SetNowMusic(L"se4");
				}
			}
		}
	}

	void Cannon::OnUpdate2() {
		//�e�̃|�W�V�����̍X�V
		GetComponent<Transform>()->SetPosition(ShadowLocation());

	}

	//���̂ƃ��C�g�̈ʒu����A�e�̈ʒu�𓱂��o��
	Vec3 Cannon::ShadowLocation() {
		auto obj = m_Obj.lock();
		//���̃u���b�N�̃|�W�V����
		auto ObjPos = obj->GetComponent<Transform>()->GetPosition();
		//���C�g�̃R���g���[���[�������Ă���
		auto ptrMyLight = GetStage()->GetSharedGameObject<LightController>(L"LightController");
		//�p�x�����o��
		auto LightAngle = ptrMyLight->GetLightAngle();

		//���C�g�̊p�x�ƑΉ��������ԃu���b�N�̕ǂ܂ł̋�������e�̈ʒu���o��
		Vec3 m_kagePos;
		m_kagePos.x = ObjPos.x - ObjPos.z * tanf(LightAngle.x);
		m_kagePos.y = ObjPos.y - ObjPos.z * tanf(LightAngle.y);

		m_kagePos.z = 0;

		return m_kagePos;
	}

	//--------------------------------------------------------------------------------------
	//�e
	//--------------------------------------------------------------------------------------
	Bullet::Bullet(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale, const Vec3& Rotation, const Vec3& Position,CannonBase::CanonDirection LR)
		: GameObject(StagePtr),
		m_Scale(Scale), m_Rotation(Rotation), m_Position(Position), m_ScaleZ(0.05f),m_LR(LR)
	{
	}

	Bullet::~Bullet() {}
	//������
	void Bullet::OnCreate() {
		if (m_LR == CannonBase::CanonDirection::RIGTH) {
			m_Scale *= -1.0f;
		}
		//�X�P�[����Z���Œ�̑傫����
		m_Scale.z = m_ScaleZ;
		//AddComponent<Rigidbody>();
		auto PtrTransform = AddComponent<Transform>();
		//�e�̃X�P�[��,�p�x,�|�W�V�����̐ݒ�
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(m_Position);

		//���_�z��
		vector<VertexPositionNormalTexture> vertices;
		//�C���f�b�N�X���쐬���邽�߂̔z��
		vector<uint16_t> indices;
		//Square�̍쐬(�w���p�[�֐��𗘗p)
		MeshUtill::CreateSquare(1.0f, vertices, indices);

		//���㒸�_
		vertices[0].textureCoordinate = Vec2(0, 0);
		//�E�㒸�_
		vertices[1].textureCoordinate = Vec2(1, 0);
		//�������_
		vertices[2].textureCoordinate = Vec2(0, 1.0f);
		//�E�����_
		vertices[3].textureCoordinate = Vec2(1, 1.0f);
		//���_�̌^��ς����V�������_���쐬
		vector<VertexPositionColorTexture> new_vertices;
		for (auto& v : vertices) {
			VertexPositionColorTexture nv;
			nv.position = v.position;
			nv.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
			nv.textureCoordinate = v.textureCoordinate;
			new_vertices.push_back(nv);
		}
		//�V�������_���g���ă��b�V�����\�[�X�̍쐬
		m_SquareMeshResource = MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true);

		auto DrawComp = AddComponent<PCTStaticDraw>();
		DrawComp->SetMeshResource(m_SquareMeshResource);
		//�`�悷��e�N�X�`����ݒ�
		DrawComp->SetTextureResource(L"BULLET_TX");
		//��������
		SetAlphaActive(true);
		auto PtrRedid = AddComponent<Rigidbody>();
		auto PtrCol = AddComponent<CollisionObb>();
	}
	//�����蔻��
	void Bullet::OnCollision(vector<shared_ptr<GameObject>>& OtherVec) {
		auto playerTrans = GetComponent<Transform>();
		for (auto &obj : OtherVec) {
			//�V���h�E�I�u�W�F�N�g�����o
			auto ShadowPtr = dynamic_pointer_cast<ShadowObject>(obj);
			auto BulletPtr = dynamic_pointer_cast<Bullet>(obj);
			auto PlayerPtr = dynamic_pointer_cast<Player>(obj);
			//�e�u���b�N�Ɠ�����
			if (ShadowPtr) {
				//�ւ������o��
				GetStage()->AddGameObject<DirectingRing>(playerTrans->GetWorldPosition(),
					Vec3(1.0f,1.0f,0.05f), Vec3(-0.5f, 0.0f, 0.0f),L"Ring_TX");
				GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
			}
			//�e�Ɠ�����
			else if (BulletPtr) {
				//�ւ������o��
				GetStage()->AddGameObject<DirectingRing>(playerTrans->GetWorldPosition(),
					Vec3(1.0f, 1.0f, 0.05f), Vec3(-0.5f, 0.0f, 0.0f), L"Ring_TX");
				GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
			}
			//�C�f�A�Ɠ����肤
			else if (PlayerPtr) {
				PlayerPtr->Damage(m_LR);
				//�ւ������o��
				GetStage()->AddGameObject<DirectingRing>(playerTrans->GetWorldPosition(),
					Vec3(1.0f, 1.0f, 0.05f), Vec3(-0.5f, 0.0f, 0.0f),L"Ring_TX");
				GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
			}
		}
	}

	//�ω�
	void Bullet::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto PtrTransform = AddComponent<Transform>();
		auto Pos = PtrTransform->GetPosition();
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		if (!ScenePtr->GetPauseFlag()) {
			if (m_LR == CannonBase::CanonDirection::LEFT) {
				Pos.x -= 7.0f*ElapsedTime;
				PtrTransform->SetPosition(Pos);

				//OnTriggerEnter();
				if (Pos.x <= -30) {
					GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
				}
			}
			else {
				Pos.x += 7.0f*ElapsedTime;
				PtrTransform->SetPosition(Pos);
				if (Pos.x >= 30) {
					GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
				}
			}
		}
	}
	void Bullet::OnUpdate2() {

	}

}