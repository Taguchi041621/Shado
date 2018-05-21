#pragma once
#include "stdafx.h"

namespace basecross {
	class LightController :public GameObject {
		//ライトの位置
		Vec3 m_LightPosition;
		//ライトの基本距離
		float m_LightDistance;
		//ライトの最大角度
		float m_MaxAngle;
		//ライトの角度
		Vec3 m_LightAngle;
		//ライトを減速させる
		float m_Speed;
		//スティックを放したときのスピードをもつ
		Vec2 m_Lingering;
	public:
		LightController(const shared_ptr<Stage>& StagePtr);
		virtual ~LightController();
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		Vec3 GetLightAngle();
	};
}