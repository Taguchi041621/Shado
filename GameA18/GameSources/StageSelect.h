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