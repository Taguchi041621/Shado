#pragma once
#include "stdafx.h"

namespace basecross
{

	class MyCamera : public Camera
	{
		weak_ptr<GameObject>m_TargetObject;
		weak_ptr<GameStage>m_StagePtr;
		float CameraAngle;
		float CameraPosZ;

		Vec3 CameraPos;

		bool m_StartFlag;
	public:
		explicit MyCamera(const shared_ptr<GameStage>& StagePtr);
		virtual ~MyCamera();
		void SetTargetObject(const shared_ptr<GameObject>& Obj);
		shared_ptr<GameObject> GetTargetObject() const;
		void SetToTargetLerp(float f);
		//LR‚ª‰Ÿ‚³‚ê‚½‚Æ‚«ƒJƒƒ‰‚ğ•Ï‚¦‚é
		void CameraChanger();
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		bool GetStartFlag() { return m_StartFlag; }
	};
}