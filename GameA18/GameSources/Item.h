#pragma once
#include "stdafx.h"

namespace basecross {	
	//物体の方の鍵
	class KeyItem : public GameObject {
		Vec3 m_KeyPos;
	public:
		KeyItem(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		virtual ~KeyItem() {}
		//初期化
		virtual void OnCreate() override;

		virtual void OnUpdate() override;
		
		virtual void OnTriggerEnter();
	};

	//-----------------------------------------------------------------------------------------------------------
	//ステージ開始時にカメラが追いかける見えないオブジェクト
	//-----------------------------------------------------------------------------------------------------------
	class TargetObjectToStart : public GameObject {
		Vec3 m_TargetPos;
		Vec3 GoalPos;
		Vec3 PlayerPos;
		//補完の際に使う現在時間
		float m_Lerp = 0.0f;
	public:
		TargetObjectToStart(const shared_ptr<Stage>& StagePtr);
		virtual ~TargetObjectToStart() {}
		//初期化
		virtual void OnCreate() override;

		virtual void OnUpdate() override;
	};
}