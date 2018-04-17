#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class ShadowObject : public GameObject;
	//	�p�r: �I�u�W�F�N�g�̉e
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
		//�\�z�Ɣj��
		ShadowObject(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const wstring& Mesh,
			GameObject& Obj
			);

		virtual ~ShadowObject();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate();
		//�e�̏ꏊ���v�Z����
		Vec3 ShadowLocation();
		//1�O�̍��W�Ƃ̍����o��
		Vec3 GetPoorBefor();
	};

}