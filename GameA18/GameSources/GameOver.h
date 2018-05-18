#pragma once
#include "stdafx.h"

namespace basecross

{
	class GameOverStage : public Stage
	{
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateTitleSprite();
		//�t�F�[�h�̍쐬
		void CreateFadeOutSprite();
		void CreateFadeSprite();
		bool m_SelectFlag;
	public:
		//�\�z�Ɣj��
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
	};

}