/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

#define RadToDeg 180.0f / 3.1415f
#define DegToRad 3.1415f/180.0f

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

		CsvFile m_Csv;//CSV�֘A�̕ϐ�
					  //DataID���Ǘ�����t���O
		bool dataIdFlag = false;
	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		//���X�e�[�W��I������
		void CreateStage(int num);
		void Csv();
	};


}
//end basecross

