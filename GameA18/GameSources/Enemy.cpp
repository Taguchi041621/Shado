#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//------------------------------------------------------------------------------------------
	///�G(�e)
	//------------------------------------------------------------------------------------------
	ShadowEnemy::ShadowEnemy(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
		const Vec3& Scale, const Vec3& Rotation, GameObject& Obj)
		: SS5ssae(StagePtr, BaseDir, L"SnakeTest.ssae", L"Attack"),
		m_Scale(Scale), m_Rotation(Rotation), m_Obj(Obj), m_ScaleZ(0.05f)
	{
		m_ToAnimeMatrix.affineTransformation(
			Vec3(0.10f, 0.10f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.0f, 0.0f, 0.0f)
		);
	}

	void ShadowEnemy::OnCreate() {
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
		SetFps(49.0f);
		//�A�j���[�V�����̃��[�v�ݒ�
		SetLooped(true);
		//�A�j���[�V�����ɂ����郁�g���b�N�X�̐ݒ�
		SetToAnimeMatrix(m_ToAnimeMatrix);
	}

	void ShadowEnemy::OnUpdate() {
		OnTriggerEnter();
		GetComponent<Transform>()->SetPosition(ShadowLocation());

		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//�A�j���[�V�������X�V����
		UpdateAnimeTime(ElapsedTime);
	}

	void ShadowEnemy::OnTriggerEnter() {
		OBB t;
		t.m_Center = this->GetComponent<Transform>()->GetWorldPosition();
		t.m_Center.z = 0;
		t.m_Size = this->GetComponent<Transform>()->GetScale() * 0.5f;

		OBB p;
		p.m_Center = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetWorldPosition();
		p.m_Center.z = 0;
		p.m_Size = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetScale() * 0.5f;
		//�v���C���[�����ɐG�ꂽ���𒲂ׂ锻��
		if (HitTest::OBB_OBB(t, p)) {
		}
	}
	//���̂ƃ��C�g�̈ʒu����A�e�̈ʒu�𓱂��o��
	Vec3 ShadowEnemy::ShadowLocation() {
		//���̃u���b�N�̃|�W�V����
		auto ObjPos = m_Obj.GetComponent<Transform>()->GetPosition();
		//���C�g�̃R���g���[���[�������Ă���
		auto ptrMyLight = GetStage()->GetSharedGameObject<LightController>(L"LightController");
		//�p�x�����o��
		auto LightAngle = ptrMyLight->GetLightAngle();

		//���C�g�̊p�x�ƑΉ��������ԃu���b�N�̕ǂ܂ł̋�������e�̈ʒu���o��
		Vec3 m_kagePos;
		m_kagePos.x = ObjPos.x - ObjPos.z * tanf(LightAngle.x);
		m_kagePos.y = ObjPos.y - ObjPos.z * tanf(LightAngle.y);

		m_kagePos.z = -1;

		return m_kagePos;
	}

	//--------------------------------------------------------------------------------------
	///	�G�̎���
	//--------------------------------------------------------------------------------------
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_KeyPos(StartPos)
	{}
	void Enemy::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetPosition(m_KeyPos);
		PtrTransform->SetScale(0.50, 1.00, 0.50);

		//�^�O
		AddTag(L"Enemy");
		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		////�`�悷��e�N�X�`����ݒ�
		//PtrDraw->SetTextureResource(L"UI_Key_TX");
		PtrDraw->SetDrawActive(false);

		/*auto group = GetStage()->GetSharedObjectGroup(L"Eeney");
		group->IntoGroup(GetThis<Enemy>());*/

		//�e������
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		//-------------------------------------------------
		//�e�̍쐬
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		GetStage()->AddGameObject<ShadowEnemy>(
			DataDir + L"Enemy\\",
			GetComponent<Transform>()->GetScale(),
			GetComponent<Transform>()->GetRotation(),
			*GetThis<GameObject>()
			);
	}

	void Enemy::OnUpdate()
	{
	}


	//--------------------------------------------------------------------------------------
	//��C
	//--------------------------------------------------------------------------------------
	Cannon::Cannon(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
		const Vec3& Scale, const Vec3& Rotation, GameObject& Obj)
		: SS5ssae(StagePtr, BaseDir, L"Cannon.ssae", L"Fire"),
		m_Scale(Scale), m_Rotation(Rotation), m_Obj(Obj), m_ScaleZ(0.05f), m_CoolTime(0), m_BulletFlag(false)
	{
		m_ToAnimeMatrix.affineTransformation(
			Vec3(0.13f, 0.12f, 0.7f),
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
		//�A�j���[�V�����ɂ����郁�g���b�N�X�̐ݒ�
		SetToAnimeMatrix(m_ToAnimeMatrix);
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

		if (m_CoolTime >= 5)
		{
			m_BulletFlag = true;
			ChangeAnimation(L"Fire");
			m_CoolTime = 0;
		}
		if (m_BulletFlag) {
			UpdateAnimeTime(ElapsedTime);

			if (IsAnimeEnd()) {
				GetStage()->AddGameObject<Bullet>(
					GetComponent<Transform>()->GetScale(),
					GetComponent<Transform>()->GetRotation(),
					GetComponent<Transform>()->GetPosition() - Vec3(1, -0.4f, 0)
					);
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
							GetStage()->AddGameObject<Bullet>(
								GetComponent<Transform>()->GetScale(),
								GetComponent<Transform>()->GetRotation(),
								GetComponent<Transform>()->GetPosition() - Vec3(1, -0.4f, 0)
								);
							m_BulletFlag = false;
						}
					}
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
		//���̃u���b�N�̃|�W�V����
		auto ObjPos = m_Obj.GetComponent<Transform>()->GetPosition();
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
		const Vec3& Scale, const Vec3& Rotation, const Vec3& Position)
		: GameObject(StagePtr),
		m_Scale(Scale), m_Rotation(Rotation), m_Position(Position), m_ScaleZ(0.05f)
	{
	}

	Bullet::~Bullet() {}
	//������
	void Bullet::OnCreate() {
		//�X�P�[����Z���Œ�̑傫����
		m_Scale.z = m_ScaleZ;
		//AddComponent<Rigidbody>();
		auto PtrTransform = AddComponent<Transform>();
		//�e�̃X�P�[��,�p�x,�|�W�V�����̐ݒ�
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(m_Position);

		//auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//PtrDraw->SetMeshResource(m_Obj.GetComponent<BcPNTStaticDraw>()->GetMeshResource());
		////�^����
		//PtrDraw->SetColorAndAlpha(Col4(1.0f, 1.0f, 1.0f, 0.0f));
		////Mat4x4 au;
		///*au.affineTransformation(
		//	Vec3(1.0f, 1.0f, 0.1f),
		//	Vec3(0, 0, 0),
		//	Vec3(0, 0, 0),
		//	Vec3(0.0f, 0.0f, 0.0f)
		//	);
		//PtrDraw->SetMeshToTransformMatrix(au);*/
		//PtrDraw->SetTextureResource(L"Shadow_Blur_TX");
		//PtrDraw->SetAlpha(1.0f);
		//PtrDraw->SetPerPixelLighting(false);
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
		/*Mat4x4 au;
		au.affineTransformation(
		Vec3(0.0f, 0.9f, 0.1f),
		Vec3(0, 0, 0),
		Vec3(0, 0, 0),
		Vec3(0.0f, 0.0f, 0.0f)
		);
		PtrDraw->SetMeshToTransformMatrix(au);*/

	}

	//�ω�
	void Bullet::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto PtrTransform = AddComponent<Transform>();
		auto Pos = PtrTransform->GetPosition();
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		if (!ScenePtr->GetPauseFlag()) {
			Pos.x -= 5.0f*ElapsedTime;
			PtrTransform->SetPosition(Pos);

			OnTriggerEnter();

			if (Pos.x <= -30) {
				GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
			}
		}
	}
	void Bullet::OnUpdate2() {

	}

	void Bullet::OnTriggerEnter() {
		auto PtrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");

		SPHERE t;
		t.m_Center = GetComponent<Transform>()->GetWorldPosition();
		t.m_Center.z = 0;
		t.m_Radius = GetComponent<Transform>()->GetScale().x/2;

		OBB p;
		p.m_Center = PtrPlayer->GetComponent<Transform>()->GetWorldPosition();
		p.m_Center.z = 0;
		p.m_Size = PtrPlayer->GetComponent<Transform>()->GetScale()/2.3;

		//�v���C���[���e�ɐG�ꂽ���𒲂ׂ锻��
		if (HitTest::SPHERE_OBB(t, p,Vec3(0))) {
			PtrPlayer->Damage();
		}
	}
}