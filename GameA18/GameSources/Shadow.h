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
	};

}