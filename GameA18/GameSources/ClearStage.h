#pragma once
#include "stdafx.h"

namespace basecross

{
	class ClearStage : public Stage
	{
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateTitleSprite();
		void CreateUI();

		void CreateFadeOutSprite();
		void CreateFadeSprite();
		bool m_SelectFlag;

		//�I���֌W
		bool ActionFlag;
		bool ControllerFlag;
		bool SelectFlag;
		float ThumbTimer;
		bool ThumbFlag;
		int NowSelect;

		float m_ScaleTimer;
		bool m_ScaleFlag;
		int Number;
	public:
		//�\�z�Ɣj��
		ClearStage() :Stage() {}
		virtual ~ClearStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		//�V�[���J�ڂ̃Z���N�g
		void Select();
	};

}