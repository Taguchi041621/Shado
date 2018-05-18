#pragma once
#include "stdafx.h"

namespace basecross
{
	class StageSelect : public Stage
	{
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateTitleSprite();

		//�t�F�[�h�̍쐬
		void CreateFadeOutSprite();
		void CreateFadeSprite();
		bool m_SelectFlag;

		//�X�e�[�W�ԍ��̍쐬
		void StageNumberSprite();

		int m_StageNumber;
		bool onectrl;

		

	public:
		//�\�z�Ɣj��
		StageSelect() :Stage() {}
		virtual ~StageSelect() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
	};

}