#pragma once
#include "stdafx.h"

namespace basecross

{
	class GameOverStage : public Stage
	{
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		wstring m_StopNowMusic;
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateTitleSprite();
		//�t�F�[�h�̍쐬
		void CreateFadeOutSprite();
		void CreateFadeSprite();
		bool m_SelectFlag;
		//UI�̍쐬
		void CreateUI();
		float m_SelectScene;
	public:
		//�\�z�Ɣj��
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		///����
		void SetNowMusic(wstring NowMusic) {
			m_StopNowMusic = NowMusic;
		}
		wstring GetNowMusic() {
			return m_StopNowMusic;
		}
	};

}