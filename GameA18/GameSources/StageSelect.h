#pragma once
#include "stdafx.h"

namespace basecross
{
	class StageSelect : public Stage
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

		//�X�e�[�W�ԍ��̍쐬
		void StageNumberSprite();

		int m_StageNumber;
		bool onectrl;

		int m_MaxStageNumber;
		
		float m_CoolTime;

	public:
		//�\�z�Ɣj��
		StageSelect() :Stage() {}
		virtual ~StageSelect() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		void SetNowMusic(wstring NowMusic) {
			m_StopNowMusic = NowMusic;
		}
		wstring GetNowMusic() {
			return m_StopNowMusic;
		}
	};

}