#include "stdafx.h"
#include "Project.h"

namespace basecross {
	LightController::LightController(const shared_ptr<Stage>&StagePtr) :
		GameObject(StagePtr),
		m_LightAngle(0.0f, 0.0f, -0.1f), m_LightDistance(0.1f), m_MaxAngle(0.8f), m_Speed(0.4f)
	{}
	LightController::~LightController() {}
	void LightController::OnCreate() {

	}
	//�A�b�v�f�[�g
	void LightController::OnUpdate() {
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		if (!GetStage()->GetSharedGameObject<Player>(L"Player")->GetGameOverFlag() &&
			!GetStage()->GetSharedGameObject<Player>(L"Player")->GetGameClearFlag() &&
			ScenePtr->GetStartFlag()&&
			!ScenePtr->GetPauseFlag()) {
			//&&GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetParent()) {
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			//Elapsed�^�C���̎擾
			auto ElapsedTime = App::GetApp()->GetElapsedTime();
			//�E�X�e�B�b�N�������Ă�����
			if (CntlVec[0].fThumbRX != 0 || CntlVec[0].fThumbRY != 0) {
				//X�����ɃX�e�b�N���|��Ă�����
				if (m_LightAngle.x >= -m_MaxAngle && CntlVec[0].fThumbRX > 0.4f) {
					m_LightAngle.x += -CntlVec[0].fThumbRX * ElapsedTime*m_Speed;
					m_Lingering.x = -CntlVec[0].fThumbRX*m_Speed;
				}
				else if (m_LightAngle.x <= m_MaxAngle && CntlVec[0].fThumbRX < -0.4f) {
					m_LightAngle.x += -CntlVec[0].fThumbRX * ElapsedTime*m_Speed;
					m_Lingering.x = -CntlVec[0].fThumbRX*m_Speed;
				}
				//Y�����ɃX�e�B�b�N���|��Ă�����
				if (m_LightAngle.y >= -m_MaxAngle && CntlVec[0].fThumbRY > 0.4f) {
					m_LightAngle.y += -CntlVec[0].fThumbRY * ElapsedTime*m_Speed;
					m_Lingering.y = -CntlVec[0].fThumbRY*m_Speed;
				}
				else if (CntlVec[0].fThumbRY < -0.4f) {
					if (m_LightAngle.y <= m_MaxAngle) {
						m_LightAngle.y += -CntlVec[0].fThumbRY * ElapsedTime*m_Speed;
						m_Lingering.y = -CntlVec[0].fThumbRY*m_Speed;
					}
				}
			}
			//�X�e�B�b�N�����������������
			else if (m_Lingering.x >= 0.1f || m_Lingering.y >= 0.1f||
				m_Lingering.x <= -0.1f || m_Lingering.y <= -0.1f) {
				m_LightAngle.x += m_Lingering.x * ElapsedTime;
				m_LightAngle.y += m_Lingering.y * ElapsedTime;
				m_Lingering *= 0.8f;
				//�}�b�N�X�A���O���𒴂�����}�b�N�X�A���O���̒l�ɖ߂�
				if (m_LightAngle.x >= m_MaxAngle) {
					m_LightAngle.x = m_MaxAngle;
				}
				if (m_LightAngle.x <= -m_MaxAngle) {
					m_LightAngle.x = -m_MaxAngle;
				}
				if (m_LightAngle.y >= m_MaxAngle) {
					m_LightAngle.y = m_MaxAngle;
				}
				if (m_LightAngle.y <= -m_MaxAngle) {
					m_LightAngle.y = -m_MaxAngle;
				}
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
			//	}
		}
	}

	Vec3 LightController::GetLightAngle() {
		return m_LightAngle;
	}

}