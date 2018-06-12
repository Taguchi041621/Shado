#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MyCamera::MyCamera(const shared_ptr<GameStage>&StagePtr) :
		Camera(),
		m_StagePtr(StagePtr),
		CameraPosZ(-56.0f),
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

	//カメラを引いたり近づけたりする
	void MyCamera::CameraChanger() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		if (m_StartFlag && !ScenePtr->GetPauseFlag()) {
			if (CntlVec[0].bConnected) {
				if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
					CameraPosZ += 0.2;
					if (CameraPosZ >= -10) {
						CameraPosZ = -10;
					}
				}
				else if (CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
					CameraPosZ -= 0.2;
					if (CameraPosZ <= -30) {
						CameraPosZ = -30;
					}
				}
			}

				/*if (CntlVec[0].bConnected) {
					if (CntlVec[0].wButtons & XINPUT_GAMEPAD_X) {
						CameraAngle += 0.2;
						if (CameraAngle >= 12) {
							CameraAngle = 12;
						}
					}
					else if (CntlVec[0].wButtons & XINPUT_GAMEPAD_Y) {
						CameraAngle -= 0.2;
						if (CameraAngle <= 0) {
							CameraAngle = 0;
						}
					}
				}*/
		}
		//ステージ開始時(リスタート時はやらない)
		else if(!m_StartFlag) {
			//壁の方に近寄る
			CameraPosZ += 0.2;
			if (CameraPosZ >= -16) {
				CameraPosZ = -16;
			}
		}
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].fThumbLX != 0 || CntlVec[0].fThumbLY != 0) {
				//CameraPos.x += CntlVec[0].fThumbLX;
				//CameraPos.y += CntlVec[0].fThumbLY;
			}
		}
		//XINPUT_GAMEPAD_DPAD_DOWN
		auto TargetPos = GetTargetObject()->GetComponent<Transform>()->GetWorldPosition();
		TargetPos.x += CameraPos.x;
		TargetPos.y += CameraPos.y;
		Vec3 ArmVec(-CameraAngle, CameraAngle, CameraPosZ);
		Vec3 Eye = TargetPos + ArmVec;
		SetAt(TargetPos);
		SetEye(Eye);
		ScenePtr->SetCameraAngle(CameraAngle);
		ScenePtr->SetCameraPosZ(CameraPosZ);
	}

	void MyCamera::OnCreate() {
		SetUp(Vec3(0, 1.0f, 0));
		Camera::OnCreate();
		m_StartFlag = false;
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		ScenePtr->SetStartFlag(m_StartFlag);
		//リスタート時
		if (ScenePtr->GetRespawnFlag())
		{
			m_StartFlag = true;
			ScenePtr->SetStartFlag(m_StartFlag);
			CameraPosZ = ScenePtr->GetCameraPosZ();
			CameraAngle = ScenePtr->GetCameraAngle();
		}
	}
	void MyCamera::OnUpdate() {
		auto TargetPtr = m_TargetObject.lock();
		if (TargetPtr) {
			//カメラを引いたり近づけたりする
			CameraChanger();
		}
	}

}