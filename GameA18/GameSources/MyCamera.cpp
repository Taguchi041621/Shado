#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MyCamera::MyCamera(const shared_ptr<GameStage>&StagePtr) :
		Camera(),
		m_StagePtr(StagePtr)
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
	void MyCamera::OnCreate() {
		SetUp(Vec3(0, 1.0f, 0));
		Camera::OnCreate();
	}
	void MyCamera::OnUpdate() {
		auto TargetPtr = m_TargetObject.lock();
		if (TargetPtr) {
			auto TargetPos = TargetPtr->GetComponent<Transform>()->GetPosition();
			Vec3 ArmVec(0, 0.0f, -5.0f);
			Vec3 Eye = TargetPos + ArmVec;
			SetAt(TargetPos);
			SetEye(Eye);
		}
	}
}