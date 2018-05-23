#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MyCamera::MyCamera(const shared_ptr<GameStage>&StagePtr) :
		Camera(),
		m_StagePtr(StagePtr),
		CameraPosZ(-40.0f)
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
	//ÉJÉÅÉâÇà¯Ç¢ÇΩÇËãﬂÇ√ÇØÇΩÇËÇ∑ÇÈ
	void MyCamera::CameraChanger() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (m_StartFlag) {
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
		}
		else {
			CameraPosZ += 0.2;
			if (CameraPosZ >= -10) {
				CameraPosZ = -10;
				m_StartFlag = true;
				auto ScenePtr = App::GetApp()->GetScene<Scene>();
				ScenePtr->SetStartFlag(m_StartFlag);
			}
		}
		auto TargetPos = GetTargetObject()->GetComponent<Transform>()->GetWorldPosition();
		Vec3 ArmVec(0.0f, 0.0f, CameraPosZ);
		Vec3 Eye = TargetPos + ArmVec;
		SetAt(TargetPos);
		SetEye(Eye);
	}


	void MyCamera::OnCreate() {
		SetUp(Vec3(0, 1.0f, 0));
		Camera::OnCreate();
		m_StartFlag = false;
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		ScenePtr->SetStartFlag(m_StartFlag);
	}
	void MyCamera::OnUpdate() {
		auto TargetPtr = m_TargetObject.lock();
		if (TargetPtr) {
			//ÉJÉÅÉâÇà¯Ç¢ÇΩÇËãﬂÇ√ÇØÇΩÇËÇ∑ÇÈ
			CameraChanger();
		}
	}

}