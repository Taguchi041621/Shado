#pragma once
#include "stdafx.h"

namespace basecross {
	class LightController :public GameObject {
		//���C�g�̈ʒu
		Vec3 m_LightPosition;
		//���C�g�̊�{����
		float m_LightDistance;
		//���C�g�̍ő�p�x
		float m_MaxAngle;
		//���C�g�̊p�x
		Vec3 m_LightAngle;
	public:
		LightController(const shared_ptr<Stage>& StagePtr);
		virtual ~LightController();
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		Vec3 GetLightAngle();
	};
}