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
		m_LightPosition(0.01f, 0.01f, -0.1f)
	{
	}

	ShadowObject::~ShadowObject() {}
	//������
	void ShadowObject::OnCreate() {
		m_Scale.z = m_ScaleZ;
		AddComponent<Rigidbody>();
		auto PtrTransform = AddComponent<Transform>();
		//�e�̃|�W�V�������o��
		auto kagePos = ShadowLocation();

		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(kagePos);

		auto PtrObb = AddComponent<CollisionObb>();
		PtrObb->SetFixed(true);

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetFogEnabled(true);
		PtrDraw->SetMeshResource(m_Mesh);
		PtrDraw->SetOwnShadowActive(true);
		PtrDraw->SetTextureResource(L"Oreng_TX");
	}

	//�ω�
	void ShadowObject::OnUpdate() {
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
	}

	//���̂̈ʒu����A�e�̈ʒu�𓱂��o��
	Vec3 ShadowObject::ShadowLocation() {
		//���̃u���b�N�̃|�W�V����
		auto ObjPos = m_Obj.GetComponent<Transform>()->GetPosition();
		//�}���`���C�g���擾
		auto MultiLightPtr = dynamic_pointer_cast<MultiLight>(GetStage()->GetLight());
		Vec3 LightPos;
		if (MultiLightPtr) {
			//���C�����C�g�������Ă���
			auto mainIndex = MultiLightPtr->GetMainIndex();
			//���C�����C�g�̃|�W�V�������o��
			LightPos = MultiLightPtr->GetLight(mainIndex).m_Directional;
		}

		auto LightHeight = AddComponent<Shadowmap>()->GetLightHeight();
		//���C�g�̊p�x���o��
		auto AngleX = atan2(LightPos.x, LightPos.z);
		auto AngleY = atan2(LightPos.y, LightPos.z);

		//���̃u���b�N����ǂ܂ł�Y������P�ʕψʒl�ɏ�Z���āA���̃u���b�N����̉e��XY�̂�����Z�o�����
		Vec3 m_kagePos;
		m_kagePos.x = ObjPos.x - ObjPos.z * AngleX;
		m_kagePos.y = ObjPos.y - ObjPos.z * AngleY;
		m_kagePos.z = 0;

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
	//�O�̈ʒu�ƍ��̈ʒu���ׂ�Vec3��Ԃ�
	Vec3 ShadowObject::GetPoorBefor() {
		//�O�̃|�W�V�����ƍ��̃|�W�V�����̍����o��
		PoorBefor = ShadowLocation() - GetComponent<Transform>()->GetBeforePosition();
		//����Ԃ�
		return PoorBefor;
	}
}