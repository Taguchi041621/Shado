/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		//�v���[�g�̍쐬
		void CreatePlate();
		//����
		void CreateWall();
		//�v���C���[�̍쐬
		void CreatePlayer();
		//�����u���b�N�̍쐬
		void CreateWhiteCube();
		//
		void CreateGoal();
		//
		void CreateKeyItem();
	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;

	};


}
//end basecross

