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
		//対応した実態オブジェクトのポインタ
		GameObject& m_Obj;
		//スケールのZの固定値
		float m_ScaleZ;
		//前の位置との差
		Vec3 PoorBefor;
		//ライトの位置
		Vec3 m_LightPosition;
		//ライトの角度
		Vec3 m_LightAngle;
		//ライトの基本距離
		float m_LightDistance;
		//ライトの最大角度
		float m_MaxAngle;
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
		virtual void OnUpdate2();
		//影の場所を計算する
		Vec3 ShadowLocation();
		//1つ前の座標との差を出す
		Vec3 GetPoorBefor();
	};

}