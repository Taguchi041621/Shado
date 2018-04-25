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
		m_Scale(Scale), m_Rotation(Rotation), m_Obj(Obj), m_ScaleZ(0.25f),
		m_LightAngle(0.0f, 0.0f, 0.0f), m_LightDistance(0.1f),m_MaxAngle(0.8f)
	{
	}
	
	ShadowObject::~ShadowObject() {}
	//������
	void ShadowObject::OnCreate() {
		//���C�g�̈ʒu����
		auto MultiLightPtr = dynamic_pointer_cast<MultiLight>(GetStage()->GetLight());
		auto mainIndex = MultiLightPtr->GetMainIndex();
		m_LightPosition = MultiLightPtr->GetLight(mainIndex).m_Directional;
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
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float speed = 0.6f;
		if (CntlVec[0].bConnected) {
			//�E�X�e�B�b�N�������Ă�����
			if (CntlVec[0].fThumbRX != 0 || CntlVec[0].fThumbRY != 0) {
				//�}���`���C�g�������Ă���
				auto PtrLight = dynamic_pointer_cast<MultiLight>(GetStage()->GetLight());
				//�}���`���C�g�̒��̃��C�����C�g�������Ă���
				auto mainIndex = PtrLight->GetMainIndex();
				//Elapsed�^�C���̎擾
				auto ElapsedTime = App::GetApp()->GetElapsedTime();
				//X�����ɃX�e�b�N���|��Ă�����
				if (m_LightAngle.x >= -m_MaxAngle && CntlVec[0].fThumbRX > 0.4f) {
					m_LightAngle.x += -CntlVec[0].fThumbRX * ElapsedTime*speed;
				}
				else if (m_LightAngle.x <= m_MaxAngle && CntlVec[0].fThumbRX < -0.4f) {
					m_LightAngle.x += -CntlVec[0].fThumbRX * ElapsedTime*speed;
				}
				//Y�����ɃX�e�B�b�N���|��Ă�����
				if (m_LightAngle.y >= -m_MaxAngle && CntlVec[0].fThumbRY > 0.4f) {
					m_LightAngle.y += -CntlVec[0].fThumbRY * ElapsedTime*speed;
				}
				else if (m_LightAngle.y <= m_MaxAngle && CntlVec[0].fThumbRY < -0.4f) {
					m_LightAngle.y += -CntlVec[0].fThumbRY * ElapsedTime*speed;
				}
				//---------------------------------------------------------------------------------------
				//�p�x����|�W�V�����o��
				m_LightPosition.x = -m_LightDistance * sinf(m_LightAngle.x);
				float xZ = -m_LightDistance * cosf(m_LightAngle.x);
				//X���Ɋp�x�𔽉f���������Z�������Y�������̌v�Z������
				m_LightPosition.y = xZ * sinf(m_LightAngle.y);
				m_LightPosition.z = xZ * cosf(m_LightAngle.y);
				//�ύX�������C�g�̃|�W�V�����𔽉f
				PtrLight->GetLight(mainIndex).SetPositionToDirectional(m_LightPosition);
			}
		}
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
		//���C�g�̊p�x��ʕϐ��Ŏ���
		auto AngleX = m_LightAngle.x;
		auto AngleY = m_LightAngle.y;
		if (AngleX < 0) {
			AngleX *= -1.0f;
		}
		if (AngleY < 0) {
			AngleY *= -1.0f;
		}

		//���C�g�̊p�x�ƑΉ��������ԃu���b�N�̕ǂ܂ł̋�������e�̈ʒu���o��
		Vec3 m_kagePos;
		m_kagePos.x = ObjPos.x - ObjPos.z * tanf(m_LightAngle.x);
		m_kagePos.y = ObjPos.y - ObjPos.z * tanf(m_LightAngle.y);

		m_kagePos.z = 0;


		//�X�P�[���ɃA���O���̒l����
		GetComponent<Transform>()->SetScale(m_Scale.x + AngleX, m_Scale.y + AngleY, m_ScaleZ);
		//m_kagePos.x += m_Obj.GetComponent<Transform>()->GetScale().x/2 - m_Scale.x;

		return m_kagePos;
	}
}