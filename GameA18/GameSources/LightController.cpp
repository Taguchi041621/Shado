#include "stdafx.h"
#include "Project.h"

namespace basecross {
	LightController::LightController(const shared_ptr<Stage>&StagePtr) :
		GameObject(StagePtr),
		m_LightAngle(0.0f, 0.0f, -0.1f), m_LightDistance(0.1f), m_MaxAngle(0.8f)
	{}
	LightController::~LightController() {}
	void LightController::OnCreate() {

	}
	//�A�b�v�f�[�g
	void LightController::OnUpdate() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float speed = 0.6f;
		//�E�X�e�B�b�N�������Ă�����
		if (CntlVec[0].fThumbRX != 0 || CntlVec[0].fThumbRY != 0) {
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
			//�}���`���C�g�������Ă���
			auto PtrLight = dynamic_pointer_cast<MultiLight>(GetStage()->GetLight());
			//�}���`���C�g�̒��̃��C�����C�g�������Ă���
			auto mainIndex = PtrLight->GetMainIndex();
			//�ύX�������C�g�̃|�W�V�����𔽉f
			PtrLight->GetLight(mainIndex).SetPositionToDirectional(m_LightPosition);
		}
	}

	Vec3 LightController::GetLightAngle() {
		return m_LightAngle;
	}

}