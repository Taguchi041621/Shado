/*!
@file Scene.h
@brief �V�[��
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase {
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		wstring m_StopNowMusic;
		//--------------------------------------------------------------------------------------
		/*!
		@brief ���\�[�X�̍쐬
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		void CreateResourses();

		//�Q�[���X�e�[�W�̍쐬�p�ϐ�
		int m_StageNumber=0;

		bool m_StartFlag;

		bool m_RespawnFlag;

	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		Scene() :SceneBase() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �C�x���g�擾
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		void SetStageNumber(int n) {
			m_StageNumber = n;
		}

		int GetStageNumber() {
			return m_StageNumber;
		}

		void SetStartFlag(bool f) {
			m_StartFlag = f;
		}

		bool GetStartFlag() {
			return m_StartFlag;
		}

		void SetRespawnFlag(bool f) {
			m_RespawnFlag = f;
		}

		bool GetRespawnFlag() {
			return m_RespawnFlag;
		}
	};

}

//end basecross
