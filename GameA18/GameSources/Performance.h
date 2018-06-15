#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//演出用輪っか
	//--------------------------------------------------------------------------------------
	class DirectingRing : public GameObject {
		Vec3 m_Position;
		Vec3 m_Scale;
		//演出を出すオブジェクトからどれだけずらすかを持つ
		Vec3 m_Shift;
		float m_Time = 0;
		wstring m_Texture;
		shared_ptr<MeshResource> m_SquareMeshResource;
	public:
		DirectingRing(const shared_ptr<Stage>& StagePtr, Vec3 position,Vec3 scale, Vec3 shift,wstring texture);
		virtual ~DirectingRing();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate();
	};
}