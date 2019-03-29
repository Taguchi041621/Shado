#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MyCamera::MyCamera(const shared_ptr<GameStage>&StagePtr) :
		Camera(),
		m_StagePtr(StagePtr),
		m_FarstPosZ(-56.0f),
		m_StartPosZ(-20.0f),
		CameraAngle(0),
		CameraPos(0)
	{}

	MyCamera::~MyCamera() {}

	void MyCamera::SetTargetObject(const shared_ptr<GameObject>& Obj) {
		m_TargetObject = Obj;
	}

	shared_ptr<GameObject>MyCamera::GetTargetObject()const {
		auto ShPtr = m_TargetObject.lock();
		if (ShPtr) {
			return ShPtr;
		}
		return nullptr;
	}

	void MyCamera::SetToTargetLerp(float f)
	{
	}

	//�J��������������߂Â����肷��
	void MyCamera::CameraChanger() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		if (m_StartFlag) {
			if (!ScenePtr->GetPauseFlag()) {
				if (CntlVec[0].bConnected) {
					if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
						m_CameraPosZ += 0.2;
						if (m_CameraPosZ >= -10) {
							m_CameraPosZ = -10;
						}
					}
					else if (CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
						m_CameraPosZ -= 0.2;
						if (m_CameraPosZ <= -30) {
							m_CameraPosZ = -30;
						}
					}
				}
			}
		}
		//�X�e�[�W�J�n��(���X�^�[�g���͂��Ȃ�)
		else{
			//�ǂ̕��ɋߊ��
			//�S�[���Ɋ��I���̂Ɠ��^�C�~���O�ŃX�^�[�gZ�ʒu�܂œ����I���
			m_CameraPosZ += (-m_FarstPosZ + m_StartPosZ) / 180.0f;
			if (m_CameraPosZ >= m_StartPosZ) {
				m_CameraPosZ = m_StartPosZ;
			}
		}
		//XINPUT_GAMEPAD_DPAD_DOWN
		auto TargetPos = GetTargetObject()->GetComponent<Transform>()->GetWorldPosition();
		TargetPos.x += CameraPos.x;
		TargetPos.y += CameraPos.y;
		Vec3 ArmVec(-CameraAngle, CameraAngle, m_CameraPosZ);
		Vec3 Eye = TargetPos + ArmVec;
		SetAt(TargetPos);
		SetEye(Eye);
		ScenePtr->SetCameraAngle(CameraAngle);
		ScenePtr->SetCameraPosZ(m_CameraPosZ);
	}

	void MyCamera::OnCreate() {
		SetUp(Vec3(0, 1.0f, 0));
		Camera::OnCreate();
		m_StartFlag = false;
		//�J������Z�ɏ����ʒu������
		m_CameraPosZ = m_FarstPosZ;
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		ScenePtr->SetStartFlag(m_StartFlag);
		//���X�^�[�g��
		if (ScenePtr->GetRespawnFlag())
		{
			m_StartFlag = true;
			ScenePtr->SetStartFlag(m_StartFlag);
			m_CameraPosZ = ScenePtr->GetCameraPosZ();
			CameraAngle = ScenePtr->GetCameraAngle();
		}
	}
	void MyCamera::OnUpdate() {
		auto TargetPtr = m_TargetObject.lock();
		if (TargetPtr) {
			//�J��������������߂Â����肷��
			CameraChanger();
		}
	}

}