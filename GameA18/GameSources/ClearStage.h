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
	public:
		//�\�z�Ɣj��
		ClearStage() :Stage() {}
		virtual ~ClearStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
	};

}