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
		m_Scale(Scale), m_Rotation(Rotation), m_Obj(Obj), m_ScaleZ(0.25f)
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

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetFogEnabled(true);

		PtrDraw->SetMeshResource(m_Obj.GetComponent<BcPNTStaticDraw>()->GetMeshResource());
		PtrDraw->SetOwnShadowActive(true);
		//�^����
		PtrDraw->SetColorAndAlpha(Col4(1.0f, 1.0f, 1.0f, 0.0f));
	}

	//�ω�
	void ShadowObject::OnUpdate() {
	}
	void ShadowObject::OnUpdate2() {
		//auto velo = ShadowLocation() - GetComponent<Transform>()->GetPosition();
		//velo = velo / App::GetApp()->GetElapsedTime();
		//GetComponent<Rigidbody>()->SetVelocity(velo);
		//�e�̃|�W�V�����̍X�V
		GetComponent<Transform>()->SetPosition(ShadowLocation());
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
		//m_kagePos.x += m_Obj.GetComponent<Transform>()->GetScale().x/2 - m_Scale.x;

		return m_kagePos;
	}
	//------------------------------------------------------------------------------------------
	///�S�[���̖���������e
	//------------------------------------------------------------------------------------------
	ShadowGoal::ShadowGoal(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale, const Vec3& Rotation, GameObject& Obj)
		: GameObject(StagePtr),
		m_Scale(Scale),m_Rotation(Rotation),m_Obj(Obj), m_ScaleZ(0.25f)
	{}

	void ShadowGoal::OnCreate() {
		//�X�P�[����Z���Œ�̑傫����
		m_Scale.z = m_ScaleZ;

		auto PtrTransform = GetComponent<Transform>();
		//�e�̃X�P�[��,�p�x,�|�W�V�����̐ݒ�
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(ShadowLocation());

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetFogEnabled(true);
		//���̂���`�������Ă���
		PtrDraw->SetMeshResource(m_Obj.GetComponent<BcPNTStaticDraw>()->GetMeshResource());
		PtrDraw->SetOwnShadowActive(true);

		//�^����
		PtrDraw->SetColorAndAlpha(Col4(1.0f, 0.0f, 0.0f, 1.0f));
	}

	void ShadowGoal::OnUpdate() {
		OnTriggerEnter();
		GetComponent<Transform>()->SetPosition(ShadowLocation());
	}

	void ShadowGoal::OnTriggerEnter(){
		SPHERE t;
		t.m_Center = this->GetComponent<Transform>()->GetPosition();
		t.m_Center.z = 0;
		t.m_Radius = 0.20;

		SPHERE p;
		p.m_Center = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetWorldPosition();
		p.m_Center.z = 0;
		p.m_Radius = 0.20;

		if (HitTest::SPHERE_SPHERE(t, p)){
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
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
}