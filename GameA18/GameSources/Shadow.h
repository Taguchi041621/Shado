#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class ShadowObject : public GameObject;
	//	用途: オブジェクトの影
	//--------------------------------------------------------------------------------------
	class ShadowObject : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		wstring m_Mesh;
		GameObject& m_Obj;
		float m_ScaleZ;
		Vec3 PoorBefor;
		Vec3 m_LightPosition;
		Vec3 m_LightAngle;
		float m_LightDistance;
	public:
		//構築と破棄
		ShadowObject(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const wstring& Mesh,
			GameObject& Obj
			);

		virtual ~ShadowObject();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate();
		//影の場所を計算する
		Vec3 ShadowLocation();
		//1つ前の座標との差を出す
		Vec3 GetPoorBefor();
	};

}