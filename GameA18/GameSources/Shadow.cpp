#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class ShadowObject : public GameObject;
	//	�p�r: �I�u�W�F�N�g�̉e
	//--------------------------------------------------------------------------------------
	ShadowObject::ShadowObject(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale, const Vec3& Rotation, weak_ptr<GameObject> Obj)
		: GameObject(StagePtr),
		m_Scale(Scale), m_Rotation(Rotation), m_Obj(Obj), m_ScaleZ(0.05f)
	{
	}
	
	ShadowObject::~ShadowObject() {}
	//������
	void ShadowObject::OnCreate() {
		//�X�P�[����Z���Œ�̑傫����
		m_Scale.z = m_ScaleZ;
		auto PtrTransform = AddComponent<Transform>();
		//�e�̃X�P�[��,�p�x,�|�W�V�����̐ݒ�
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(ShadowLocation());

		auto PtrObb = AddComponent<CollisionObb>();
		PtrObb->SetFixed(true);
		//PtrObb->SetDrawActive(true);

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		auto obj = m_Obj.lock();
		PtrDraw->SetMeshResource(obj->GetComponent<BcPNTStaticDraw>()->GetMeshResource());
		//�^����
		PtrDraw->SetColorAndAlpha(Col4(1.0f, 1.0f, 1.0f, 0.0f));
		PtrDraw->SetTextureResource(L"Shadow_Blur_TX");
	}

	//�ω�
	void ShadowObject::OnUpdate() {
		GetComponent<Transform>()->SetPosition(ShadowLocation());
		if (GetStage()->GetSharedGameObject<Player>(L"Player")->GetFadeFlag()) {
			m_RemoveTime += App::GetApp()->GetElapsedTime();
			if (m_RemoveTime >= 0.6f) {
				GetStage()->RemoveGameObject<ShadowObject>(GetThis<ShadowObject>());
			}
		}
	}
	void ShadowObject::OnUpdate2() {
	}

	//���̂ƃ��C�g�̈ʒu����A�e�̈ʒu�𓱂��o��
	Vec3 ShadowObject::ShadowLocation() {
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
		const Vec3& m_Scale, const Vec3& Rotation, weak_ptr<GameObject> Obj)
		: SS5ssae(StagePtr, BaseDir, L"DoorSS_0605.ssae", L"Lock"),
		m_Scale(m_Scale),m_Rotation(Rotation),m_Obj(Obj), m_ScaleZ(0.05f)
	{
		m_ToAnimeMatrixDark.affineTransformation(
			Vec3(1.8f, 1.5f, 0.1f),
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
		SetFps(10);
		//�A�j���[�V�����̃��[�v�ݒ�
		SetLooped(true);
		//�A�j���[�V�����ɂ����郁�g���b�N�X�̐ݒ�
		SetToAnimeMatrix(m_ToAnimeMatrixDark);
		SetAlphaActive(true);
		GetStage()->SetSharedGameObject(L"ShadowGoal", GetThis<ShadowGoal>());
	}

	void ShadowGoal::OnUpdate() {
		OnTriggerEnter();
		GetComponent<Transform>()->SetPosition(ShadowLocation());

		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//�A�j���[�V�������X�V����
		UpdateAnimeTime(ElapsedTime);
		if (m_LightFlag){
			m_LightFlag = false;
			SetFps(60.0f);
			ChangeAnimation(L"Unlock");
			SetLooped(false);
		}
	}

	void ShadowGoal::OnTriggerEnter(){
		OBB t;
		t.m_Center = this->GetComponent<Transform>()->GetWorldPosition();
		t.m_Center.y = t.m_Center.y - 0.2f;//�h�A�̔���ʒu��������
		t.m_Center.z = 0;
		t.m_Size = this->GetComponent<Transform>()->GetScale() * 0.3f;
		OBB p;
		p.m_Center = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetWorldPosition();
		p.m_Center.z = 0;
		p.m_Size = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetScale() * 0.5f;
		//�v���C���[���S�[���ɐG�ꂽ���𒲂ׂ锻��
		if (HitTest::OBB_OBB(t, p) && !flag) {
			if (!GetStage()->GetSharedGameObject<Player>(L"Player")->GetGameOverFlag()) {
				GetStage()->GetSharedGameObject<Player>(L"Player")->InGoal();
				flag = true;
			}
		}
	}

	//���̂ƃ��C�g�̈ʒu����A�e�̈ʒu�𓱂��o��
	Vec3 ShadowGoal::ShadowLocation() {
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
	//------------------------------------------------------------------------------------------
	///���̖���������e
	//------------------------------------------------------------------------------------------
	ShadowKey::ShadowKey(const shared_ptr<Stage>& StagePtr,const wstring BaseDir,
		const Vec3& Scale, const Vec3& Rotation, weak_ptr<GameObject> Obj)
		: SS5ssae(StagePtr, BaseDir, L"KeySS_0522.ssae", L"anime_1"),
		m_Scale(Scale), m_Rotation(Rotation), m_Obj(Obj), m_ScaleZ(0.05f)
	{
		m_ToAnimeMatrix.affineTransformation(
			Vec3(0.9f, 0.9f, 0.7f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.0f, 0.6f, 0.0f)
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
		//�������ꂽ��
		if (m_GoGoal) {
			//�v�Z�̂��߂̎��ԉ��Z
			m_Lerp += App::GetApp()->GetElapsedTime()*2.5f;
			//��]�̂��߂̎��ԉ��Z
			m_spin += App::GetApp()->GetElapsedTime();
			//�x�W�G�Ȑ��ŏI�ʒu�̐ݒ�
			p1 = GetStage()->GetSharedGameObject<ShadowGoal>(L"ShadowGoal")->
				GetComponent<Transform>()->GetWorldPosition() + Vec3(0.0f,3.0f, 0.0f);
			//���
			GetComponent<Transform>()->SetRotation(Vec3(0.0f, 0.0f, m_spin*30.0f));
			//�ʒu�v�Z
			m_Position.x = (1 - m_Lerp)*p0.x + m_Lerp*p1.x;
			m_Position.y = (1 - m_Lerp)*p0.y + m_Lerp*p1.y;
			GetComponent<Transform>()->SetPosition(m_Position);
			//�������I�������
			if (m_Lerp >= 1.0f) {
				//�S�[���̃A�j���N���̃t���O�𗧂Ă�
				GetStage()->GetSharedGameObject<ShadowGoal>(L"ShadowGoal")->SetLightFlag(true);
				//��������
				GetStage()->RemoveGameObject<ShadowKey>(GetThis<ShadowKey>());
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
		t.m_Size = this->GetComponent<Transform>()->GetScale() * 0.6f;
		//�C�f�A
		OBB p;
		p.m_Center = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetWorldPosition();
		p.m_Center.z = 0;
		p.m_Size = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetScale() * 0.5f;
		//�v���C���[�����ɐG�ꂽ���𒲂ׂ锻��
		if (HitTest::OBB_OBB(t, p) && !m_GoGoal) {
			//�v���C���[�̏��������𑝂₷
			GetStage()->GetSharedGameObject<Player>(L"Player")->AddKey();
			//�S�[���Ɍ������t���O�𗧂Ă�
			m_GoGoal = true;
			//�x�W�G�Ȑ������ʒu�̐ݒ�
			p0 = GetComponent<Transform>()->GetWorldPosition();

			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"KeySound");
			m_AudioObjectPtr->Start(L"KeySound", XAUDIO2_NO_LOOP_REGION, 0.6f);
		}
	}
	//���̂ƃ��C�g�̈ʒu����A�e�̈ʒu�𓱂��o��
	Vec3 ShadowKey::ShadowLocation() {
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
}