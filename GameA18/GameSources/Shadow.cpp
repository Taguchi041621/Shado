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
		m_Scale(Scale), m_Rotation(Rotation), m_Mesh(Mesh), m_Obj(Obj),
		m_LightPosition(0.01f, 0.01f, -0.1f)
	{
	}

	ShadowObject::~ShadowObject() {}
	//������
	void ShadowObject::OnCreate() {
		m_Scale.z = 0.1f;
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
		//Vec3 ShadowToMe = ShadowLocation() - GetComponent<Transform>()->GetPosition();
		GetComponent<Transform>()->SetPosition(ShadowLocation());
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].fThumbRX != 0 || CntlVec[0].fThumbRY != 0) {
				//�}���`���C�g�������Ă���
				auto PtrLight = dynamic_pointer_cast<MultiLight>(GetStage()->GetLight());
				//�}���`���C�g�̒��̃��C�����C�g�������Ă���
				auto mainIndex = PtrLight->GetMainIndex();
				if (CntlVec[0].fThumbRX != 0 || CntlVec[0].fThumbRY != 0) {
					//X�����ɃX�e�b�N���|��Ă�����
					if (m_LightPosition.x <= 0.1f && CntlVec[0].fThumbRX > 0.4f) {
						m_LightPosition.x += 0.1f * App::GetApp()->GetElapsedTime();
					}
					else if (m_LightPosition.x >= -0.1f && CntlVec[0].fThumbRX < -0.4f) {
						m_LightPosition.x += -0.1f * App::GetApp()->GetElapsedTime();
					}
					//Y�����ɃX�e�B�b�N���|��Ă�����
					if (m_LightPosition.y <= 0.1f && CntlVec[0].fThumbRY > 0.4f) {
						m_LightPosition.y += 0.1f * App::GetApp()->GetElapsedTime();
					}
					else if (m_LightPosition.y >= -0.1f && CntlVec[0].fThumbRY < -0.4f) {
						m_LightPosition.y += -0.1f * App::GetApp()->GetElapsedTime();
					}
					PtrLight->GetLight(mainIndex).SetPositionToDirectional(m_LightPosition);
				}
			}
		}
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
		//���C�g�Ǝ��̃u���b�N��XYZ�̍����o��
		float m_X = LightPos.x * LightHeight - ObjPos.x;
		float m_Y = LightPos.y * LightHeight - ObjPos.y;
		float m_Z = -LightPos.z * LightHeight - (-ObjPos.z);
		auto AngleX = atan2(LightPos.x, LightPos.z);
		auto AngleY = atan2(LightPos.y, LightPos.z);

		//���̃u���b�N����ǂ܂ł�Y������P�ʕψʒl�ɏ�Z���āA���̃u���b�N����̉e��XY�̂�����Z�o�����
		Vec3 m_kagePos;
		m_kagePos.x = ObjPos.x - ObjPos.z * AngleX;
		m_kagePos.y = ObjPos.y - ObjPos.z * AngleY;
		m_kagePos.z = 0;

		return m_kagePos;
	}
}