#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class ShadowObject : public GameObject;
	//	�p�r: �I�u�W�F�N�g�̉e
	//--------------------------------------------------------------------------------------
	ShadowObject::ShadowObject(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale, const Vec3& Rotation, const wstring& Mesh, GameObject& Obj)
		: GameObject(StagePtr),
		m_Scale(Scale), m_Rotation(Rotation), m_Mesh(Mesh), m_Obj(Obj), m_ScaleZ(1.0f),
		m_LightAngle(0.0f, 0.0f, 0.0f), m_LightDistance(0.1f)
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
		AddComponent<Rigidbody>();
		auto PtrTransform = AddComponent<Transform>();
		//�e�̃X�P�[��,�p�x,�|�W�V�����̐ݒ�
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(ShadowLocation());

		auto PtrObb = AddComponent<CollisionObb>();
		PtrObb->SetFixed(true);

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetFogEnabled(true);
		PtrDraw->SetMeshResource(m_Mesh);
		PtrDraw->SetOwnShadowActive(true);
		PtrDraw->SetTextureResource(L"Oreng_TX");
	}

	//�ω�
	/*void ShadowObject::OnUpdate() {
		//���C�g���E�X�e�B�b�N�œ�����
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
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
				if (m_LightPosition.x <= 0.1f && CntlVec[0].fThumbRX > 0.4f) {
					m_LightPosition.x += CntlVec[0].fThumbRX/10.0f * ElapsedTime;
				}
				else if (m_LightPosition.x >= -0.1f && CntlVec[0].fThumbRX < -0.4f) {
					m_LightPosition.x += CntlVec[0].fThumbRX/10.0f * ElapsedTime;
				}
				//Y�����ɃX�e�B�b�N���|��Ă�����
				if (m_LightPosition.y <= 0.1f && CntlVec[0].fThumbRY > 0.4f) {
					m_LightPosition.y += CntlVec[0].fThumbRY/10.0f * ElapsedTime;
				}
				else if (m_LightPosition.y >= -0.1f && CntlVec[0].fThumbRY < -0.4f) {
					m_LightPosition.y += CntlVec[0].fThumbRY/10.0f * ElapsedTime;
				}
				//�ύX�������C�g�̃|�W�V�����𔽉f
				PtrLight->GetLight(mainIndex).SetPositionToDirectional(m_LightPosition);
			}
		}

		//���C�g�̈ʒu����e�̈ʒu���v�Z���A�|�W�V������ς���
		//Vec3 ShadowToMe = ShadowLocation() - GetComponent<Transform>()->GetPosition();
		//GetComponent<Rigidbody>()->SetVelocity(ShadowToMe*10.0f);
		GetComponent<Transform>()->SetPosition(ShadowLocation());
	}*/
	void ShadowObject::OnUpdate() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
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
				if (m_LightAngle.x >= -0.9f && CntlVec[0].fThumbRX > 0.4f) {
					m_LightAngle.x += -CntlVec[0].fThumbRX * ElapsedTime;
				}
				else if (m_LightAngle.x <= 0.9f && CntlVec[0].fThumbRX < -0.4f) {
					m_LightAngle.x += -CntlVec[0].fThumbRX * ElapsedTime;
				}
				//Y�����ɃX�e�B�b�N���|��Ă�����
				if (m_LightAngle.y >= -0.9f && CntlVec[0].fThumbRY > 0.4f) {
					m_LightAngle.y += -CntlVec[0].fThumbRY * ElapsedTime;
				}
				else if (m_LightAngle.y <= 0.9f && CntlVec[0].fThumbRY < -0.4f) {
					m_LightAngle.y += -CntlVec[0].fThumbRY * ElapsedTime;
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
		//�e�̃|�W�V�����̍X�V
		GetComponent<Transform>()->SetPosition(ShadowLocation());
	}

	//���̂ƃ��C�g�̈ʒu����A�e�̈ʒu�𓱂��o��
	Vec3 ShadowObject::ShadowLocation() {
		//���̃u���b�N�̃|�W�V����
		auto ObjPos = m_Obj.GetComponent<Transform>()->GetPosition();
		//���C�g�̊p�x�ƑΉ��������ԃu���b�N�̕ǂ܂ł̋�������e�̈ʒu���o��
		Vec3 m_kagePos;
		m_kagePos.x = ObjPos.x - ObjPos.z * m_LightAngle.x;
		m_kagePos.y = ObjPos.y - ObjPos.z * m_LightAngle.y;
		m_kagePos.z = 0;

		//���C�g�̊p�x��ʕϐ��Ŏ���
		auto AngleX = m_LightAngle.x;
		auto AngleY = m_LightAngle.y;

		if (AngleX < 0) {
			AngleX *= -1.0f;
		}
		if (AngleY < 0) {
			AngleY *= -1.0f;
		}

		//�X�P�[���ɃA���O���̒l����
		GetComponent<Transform>()->SetScale(m_Scale.x + AngleX, m_Scale.y + AngleY, m_ScaleZ);
		//m_kagePos.x += m_Scale.x - m_Obj.GetComponent<Transform>()->GetScale().x;
		//m_kagePos.y += m_Scale.x - m_Obj.GetComponent<Transform>()->GetScale().y;

		return m_kagePos;
	}
	//�O�̈ʒu�ƍ��̈ʒu���ׂ�Vec3��Ԃ�
	Vec3 ShadowObject::GetPoorBefor() {
		//�O�̃|�W�V�����ƍ��̃|�W�V�����̍����o��
		PoorBefor = ShadowLocation() - GetComponent<Transform>()->GetBeforePosition();
		//����Ԃ�
		return PoorBefor;
	}
}