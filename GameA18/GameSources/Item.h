#pragma once
#include "stdafx.h"

namespace basecross {	
	//���̂̕��̌�
	class KeyItem : public GameObject {
		Vec3 m_KeyPos;
	public:
		KeyItem(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		virtual ~KeyItem() {}
		//������
		virtual void OnCreate() override;

		virtual void OnUpdate() override;
		
		virtual void OnTriggerEnter();
	};

	//-----------------------------------------------------------------------------------------------------------
	//�X�e�[�W�J�n���ɃJ�������ǂ������錩���Ȃ��I�u�W�F�N�g
	//-----------------------------------------------------------------------------------------------------------
	class TargetObjectToStart : public GameObject {
		Vec3 m_TargetPos;
		Vec3 GoalPos;
		Vec3 PlayerPos;
		//�⊮�̍ۂɎg�����ݎ���
		float m_Lerp = 0.0f;
	public:
		TargetObjectToStart(const shared_ptr<Stage>& StagePtr);
		virtual ~TargetObjectToStart() {}
		//������
		virtual void OnCreate() override;

		virtual void OnUpdate() override;
	};
}