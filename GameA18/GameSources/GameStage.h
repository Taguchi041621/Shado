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
		//����
		void CreateWall();
		//���̎擾�󋵕\��
		void CreateHaveKeys();
		//�G
		void CreateEnemy();
		//�~�j�}�b�v
		void CreateMiniMap();
		//��ʒ[��m�点�鉉�o
		void CreateMoveEnd();
		//���C�g�̈ʒu��m�点�鉉�o
		void CreateLightSign();
		//���C�g����̃I�u�W�F�N�g
		void CreateLightObject();
		CsvFile m_Csv;//CSV�֘A�̕ϐ�
					  //DataID���Ǘ�����t���O
		bool dataIdFlag = false;

		bool m_ClearFlag;

		//�t�F�[�h�̍쐬
		void CreateFadeOutSprite();
		void CreateFadeSprite();

		void CreatePause();

		void CreateTutorial();

		//�I���֌W
		bool ActionFlag;
		bool ControllerFlag;
		bool SelectFlag;
		float ThumbTimer;
		bool ThumbFlag;
		int NowSelect;

		float m_ScaleTimer;
		bool m_ScaleFlag;

	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		void Csv();

		bool GetClearFlag() { return m_ClearFlag; }
		void SetClearFlag(bool f) { m_ClearFlag = f; }
	};


}
//end basecross

