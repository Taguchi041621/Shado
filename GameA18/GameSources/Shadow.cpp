#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class ShadowObject : public GameObject;
	//	�p�r: �I�u�W�F�N�g�̉e
	//--------------------------------------------------------------------------------------
	ShadowObject::ShadowObject(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale, const Vec3& Rotation, GameObject& Obj)
		: GameObject(StagePtr),
		m_Scale(Scale), m_Rotation(Rotation), m_Obj(Obj), m_ScaleZ(0.05f)
	{
	}
	
	ShadowObject::~ShadowObject() {}
	//������
	void ShadowObject::OnCreate() {
		//�X�P�[����Z���Œ�̑傫����
		m_Scale.z = m_ScaleZ;
		//AddComponent<Rigidbody>();
		auto PtrTransform = AddComponent<Transform>();
		//�e�̃X�P�[��,�p�x,�|�W�V�����̐ݒ�
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(ShadowLocation());

		auto PtrObb = AddComponent<CollisionObb>();
		PtrObb->SetFixed(true);
		//PtrObb->SetDrawActive(true);

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(m_Obj.GetComponent<BcPNTStaticDraw>()->GetMeshResource());
		//�^����
		PtrDraw->SetColorAndAlpha(Col4(1.0f, 1.0f, 1.0f, 0.0f));
		//Mat4x4 au;
		/*au.affineTransformation(
			Vec3(1.0f, 1.0f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.0f, 0.0f, 0.0f)
			);
		PtrDraw->SetMeshToTransformMatrix(au);*/
		PtrDraw->SetTextureResource(L"Shadow_Blur_TX");
		//PtrDraw->SetAlpha(1.0f);



		//auto PtrDraw = AddComponent<PNTStaticDraw>();
		////�`�悷�郁�b�V����ݒ�
		//PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		////�`�悷��e�N�X�`����ݒ�
		//PtrDraw->SetTextureResource(L"Shadow_Blur_TX");
		////��������
		//SetAlphaActive(true);

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
	void ShadowObject::OnUpdate() {
		GetComponent<Transform>()->SetPosition(ShadowLocation());

	}
	void ShadowObject::OnUpdate2() {
	}

	//���̂ƃ��C�g�̈ʒu����A�e�̈ʒu�𓱂��o��
	Vec3 ShadowObject::ShadowLocation() {
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

		//���C�g�̊p�x��ʕϐ��Ŏ���
		auto AngleX = LightAngle.x;
		auto AngleY = LightAngle.y;
		//�}�C�i�X�̒l��������v���X�ɂ���
		if (AngleX < 0) {
			AngleX *= -1.0f;
		}
		if (AngleY < 0) {
			AngleY *= -1.0f;
		}
		//�X�P�[���ɃA���O���̒l����
		GetComponent<Transform>()->SetScale(m_Scale.x + AngleX, m_Scale.y + AngleY, m_ScaleZ);

		return m_kagePos;
	}

	//--------------------------------------------------------------------------------------
	//	class ShadowObject : public GameObject;
	//	�p�r: �I�u�W�F�N�g�̉e
	//--------------------------------------------------------------------------------------
	ShadowObject2::ShadowObject2(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale, const Vec3& Rotation, GameObject& Obj)
		: GameObject(StagePtr),
		m_Scale(Scale), m_Rotation(Rotation), m_Obj(Obj), m_ScaleZ(0.00005f)
	{
	}

	ShadowObject2::~ShadowObject2() {}
	//������
	void ShadowObject2::OnCreate() {
		//�X�P�[����Z���Œ�̑傫����
		m_Scale.z = m_ScaleZ;
		//AddComponent<Rigidbody>();
		auto PtrTransform = AddComponent<Transform>();
		//�e�̃X�P�[��,�p�x,�|�W�V�����̐ݒ�
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(ShadowLocation());

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



		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//�`�悷��e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"Shadow_Blur_TX");
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
	void ShadowObject2::OnUpdate() {
	}
	void ShadowObject2::OnUpdate2() {
		//�e�̃|�W�V�����̍X�V
		GetComponent<Transform>()->SetPosition(ShadowLocation());

	}

	//���̂ƃ��C�g�̈ʒu����A�e�̈ʒu�𓱂��o��
	Vec3 ShadowObject2::ShadowLocation() {
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
		m_kagePos.z = 0.1f;

		//���C�g�̊p�x��ʕϐ��Ŏ���
		auto AngleX = LightAngle.x;
		auto AngleY = LightAngle.y;
		//�}�C�i�X�̒l��������v���X�ɂ���
		if (AngleX < 0) {
			AngleX *= -1.0f;
		}
		if (AngleY < 0) {
			AngleY *= -1.0f;
		}
		//�X�P�[���ɃA���O���̒l����
		GetComponent<Transform>()->SetScale(m_Scale.x + AngleX, m_Scale.y + AngleY, m_ScaleZ);

		return m_kagePos;
	}
	//--------------------------------------------------------------------------------------
	//	class ShadowObject : public GameObject;
	//	�p�r: �I�u�W�F�N�g�̉e
	//--------------------------------------------------------------------------------------
	ShadowObject3::ShadowObject3(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale, const Vec3& Rotation, GameObject& Obj)
		: GameObject(StagePtr),
		m_Scale(Scale), m_Rotation(Rotation), m_Obj(Obj), m_ScaleZ(0.00005f)
	{
	}

	ShadowObject3::~ShadowObject3() {}
	//������
	void ShadowObject3::OnCreate() {
		//�X�P�[����Z���Œ�̑傫����
		m_Scale.z = m_ScaleZ;
		//AddComponent<Rigidbody>();
		auto PtrTransform = AddComponent<Transform>();
		//�e�̃X�P�[��,�p�x,�|�W�V�����̐ݒ�
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(ShadowLocation());

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



		auto PtrDraw = AddComponent<PNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//�`�悷��e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"Shadow_Blur_TX");
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
	void ShadowObject3::OnUpdate() {
	}
	void ShadowObject3::OnUpdate2() {
		//�e�̃|�W�V�����̍X�V
		GetComponent<Transform>()->SetPosition(ShadowLocation());

	}

	//���̂ƃ��C�g�̈ʒu����A�e�̈ʒu�𓱂��o��
	Vec3 ShadowObject3::ShadowLocation() {
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
		m_kagePos.z = 0.1f;

		//���C�g�̊p�x��ʕϐ��Ŏ���
		auto AngleX = LightAngle.x;
		auto AngleY = LightAngle.y;
		//�}�C�i�X�̒l��������v���X�ɂ���
		if (AngleX < 0) {
			AngleX *= -1.0f;
		}
		if (AngleY < 0) {
			AngleY *= -1.0f;
		}
		//�X�P�[���ɃA���O���̒l����
		GetComponent<Transform>()->SetScale(m_Scale.x + AngleX, m_Scale.y + AngleY, m_ScaleZ);

		return m_kagePos;
	}
	//------------------------------------------------------------------------------------------
	///�S�[���̖���������e
	//------------------------------------------------------------------------------------------
	ShadowGoal::ShadowGoal(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
		const Vec3& m_Scale, const Vec3& Rotation, GameObject& Obj)
		: SS5ssae(StagePtr, BaseDir, L"DoorSS_0605.ssae", L"Unlock_After"),
		m_Scale(m_Scale),m_Rotation(Rotation),m_Obj(Obj), m_ScaleZ(0.05f)
	{
		m_ToAnimeMatrixDark.affineTransformation(
			Vec3(1.18f, 1.14f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, 0.0f, 0.0f)
		);
		m_ToAnimeMatrixLight.affineTransformation(
			Vec3(0.0000018f, 0.0000014f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, 0.0f, 0.0f)
		);
	}

	void ShadowGoal::OnCreate() {
		//auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//PtrDraw->SetFogEnabled(true);
		////���̂���`�������Ă���
		//PtrDraw->SetMeshResource(m_Obj.GetComponent<BcPNTStaticDraw>()->GetMeshResource());
		//PtrDraw->SetOwnShadowActive(true);

		//flag = false;

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
		SetLooped(true);
		//�A�j���[�V�����ɂ����郁�g���b�N�X�̐ݒ�
		SetToAnimeMatrix(m_ToAnimeMatrixDark);
		SetAlphaActive(true);
		//auto PtrCol = AddComponent<CollisionObb>();
		//PtrCol->SetDrawActive(true);
		GetStage()->SetSharedGameObject(L"ShadowGoal", GetThis<ShadowGoal>());
	}

	void ShadowGoal::OnUpdate() {
		OnTriggerEnter();
		GetComponent<Transform>()->SetPosition(ShadowLocation());

		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//�A�j���[�V�������X�V����
		UpdateAnimeTime(ElapsedTime);
		if (!m_LightFlag&&GetStage()->GetSharedGameObject<Player>(L"Player")->GetKey())
		{
			m_LightFlag = true;
			/*ChangeAnimation(L"Light");
			SetToAnimeMatrix(m_ToAnimeMatrixLight);*/
		}
	}

	void ShadowGoal::OnTriggerEnter(){
		OBB t;
		t.m_Center = this->GetComponent<Transform>()->GetWorldPosition();
		t.m_Center.z = 0;
		t.m_Size = this->GetComponent<Transform>()->GetScale() * 0.5f;
		OBB p;
		p.m_Center = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetWorldPosition();
		p.m_Center.z = 0;
		p.m_Size = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetScale() * 0.5f;
		//�v���C���[���S�[���ɐG�ꂽ���𒲂ׂ锻��
		if (HitTest::OBB_OBB(t, p)&&!flag){
			if (!GetStage()->GetSharedGameObject<Player>(L"Player")->GetGameOverFlag()) {
				if (GetStage()->GetSharedGameObject<Player>(L"Player")->GetKey() >=
					GetStage()->GetSharedObjectGroup(L"KeyGroup")->size()) {
					GetStage()->GetSharedGameObject<Player>(L"Player")->InGoal();
					flag = true;
					//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
				}
			}
		}
	}

	//���̂ƃ��C�g�̈ʒu����A�e�̈ʒu�𓱂��o��
	Vec3 ShadowGoal::ShadowLocation() {
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
	//------------------------------------------------------------------------------------------
	///���̖���������e
	//------------------------------------------------------------------------------------------
	ShadowKey::ShadowKey(const shared_ptr<Stage>& StagePtr,const wstring BaseDir,
		const Vec3& Scale, const Vec3& Rotation, GameObject& Obj)
		: SS5ssae(StagePtr, BaseDir, L"KeySS_0531.ssae", L"anime_1"),
		m_Scale(Scale), m_Rotation(Rotation), m_Obj(Obj), m_ScaleZ(0.05f)
	{
		m_ToAnimeMatrix.affineTransformation(
			Vec3(0.3f, 0.3f, 0.7f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.0f, 0.4f, 0.0f)
			);
	}

	void ShadowKey::OnCreate() {
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
		SetFps(30.0f);
		//�A�j���[�V�����̃��[�v�ݒ�
		SetLooped(true);

		SetAlphaActive(true);
		//�A�j���[�V�����ɂ����郁�g���b�N�X�̐ݒ�
		SetToAnimeMatrix(m_ToAnimeMatrix);
	}

	void ShadowKey::OnUpdate() {
		OnTriggerEnter();
		if (m_GoGoal) {
			//��]�̂��߂̎��ԉ��Z
			m_spin += App::GetApp()->GetElapsedTime();
			//��]���Ԃ��I�������
			if (m_spin>=1.0f) {
				//�v�Z�̂��߂̎��ԉ��Z
				m_Lerp += App::GetApp()->GetElapsedTime();
				//�S�[���ʒu�͓����̂ōX�V����
				p3 = GetStage()->GetSharedGameObject<ShadowGoal>(L"ShadowGoal")->
					GetComponent<Transform>()->GetWorldPosition();
				//�ʒu�v�Z
				m_Position.x = (1 - m_Lerp)*(1 - m_Lerp)*(1 - m_Lerp)*p0.x + 3 * (1 - m_Lerp)*(1 - m_Lerp)*m_Lerp*p1.x
					+ 3 * (1 - m_Lerp)*m_Lerp*m_Lerp*p2.x + m_Lerp*m_Lerp*m_Lerp*p3.x;
				m_Position.y = (1 - m_Lerp)*(1 - m_Lerp)*(1 - m_Lerp)*p0.y + 3 * (1 - m_Lerp)*(1 - m_Lerp)*m_Lerp*p1.y
					+ 3 * (1 - m_Lerp)*m_Lerp*m_Lerp*p2.y + m_Lerp*m_Lerp*m_Lerp*p3.y;
				GetComponent<Transform>()->SetPosition(m_Position);
				//�������I�������
				if (m_Lerp >= 1) {
					//��������
					GetStage()->RemoveGameObject<ShadowKey>(GetThis<ShadowKey>());
				}
			}
			else {
				//���
				GetComponent<Transform>()->SetRotation(Vec3(0.0f,0.0f,m_spin*30.0f));
			}
		}
		else {
			GetComponent<Transform>()->SetPosition(ShadowLocation());
		}

		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//�A�j���[�V�������X�V����
		UpdateAnimeTime(ElapsedTime);
	}
	//�����������̔���
	void ShadowKey::OnTriggerEnter() {
		//��
		OBB t;
		t.m_Center = this->GetComponent<Transform>()->GetWorldPosition();
		t.m_Center.z = 0;
		t.m_Size = this->GetComponent<Transform>()->GetScale() * 0.5f;
		//�C�f�A
		OBB p;
		p.m_Center = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetWorldPosition();
		p.m_Center.z = 0;
		p.m_Size = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetScale() * 0.5f;
		//�v���C���[�����ɐG�ꂽ���𒲂ׂ锻��
		if (HitTest::OBB_OBB(t, p) && !m_GoGoal) {
			//���̏������̕\����ς���
			/*GetStage()->AddGameObject<HaveKeys>((wstring)L"UI_Key_TX",
				GetStage()->GetSharedGameObject<Player>(L"Player")->GetKey()
			);*/
			//�v���C���[�̏��������𑝂₷
			GetStage()->GetSharedGameObject<Player>(L"Player")->AddKey();
			//�S�[���Ɍ������t���O�𗧂Ă�
			m_GoGoal = true;
			//�x�W�G�Ȑ������ʒu�̐ݒ�
			p0 = GetComponent<Transform>()->GetWorldPosition();
			//�x�W�G�Ȑ��o�R�ʒu�̐ݒ�
			p1 = GetComponent<Transform>()->GetWorldPosition() + Vec3(-1.0f,4.0f,0.0f);
			p2 = GetStage()->GetSharedGameObject<ShadowGoal>(L"ShadowGoal")->
				GetComponent<Transform>()->GetWorldPosition() + Vec3(-3.0f,3.0f, 0.0f);

			if (m_StopNowMusic != L""){
				m_AudioObjectPtr->Stop(m_StopNowMusic);
			}
			wstring DataDir;
			//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
			//�e�Q�[���͈ȉ��̂悤�Ƀf�[�^�f�B���N�g�����擾���ׂ�
			App::GetApp()->GetDataDirectory(DataDir);

			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"KeySound");
			m_AudioObjectPtr->Start(L"KeySound", XAUDIO2_NO_LOOP_REGION, 0.1f);
			SetNowMusic(L"KeySound");
		}
	}
	//���̂ƃ��C�g�̈ʒu����A�e�̈ʒu�𓱂��o��
	Vec3 ShadowKey::ShadowLocation() {
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
}