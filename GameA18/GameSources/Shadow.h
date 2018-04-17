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
		//�Ή��������ԃI�u�W�F�N�g�̃|�C���^
		GameObject& m_Obj;
		//�X�P�[����Z�̌Œ�l
		float m_ScaleZ;
		//�O�̈ʒu�Ƃ̍�
		Vec3 PoorBefor;
		//���C�g�̈ʒu
		Vec3 m_LightPosition;
		//���C�g�̊p�x
		Vec3 m_LightAngle;
		//���C�g�̊�{����
		float m_LightDistance;
		//���C�g�̍ő�p�x
		float m_MaxAngle;
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
		virtual void OnUpdate2();
		//�e�̏ꏊ���v�Z����
		Vec3 ShadowLocation();
		//1�O�̍��W�Ƃ̍����o��
		Vec3 GetPoorBefor();
	};

}