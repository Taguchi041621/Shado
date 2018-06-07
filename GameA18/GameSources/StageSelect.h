#pragma once
#include "stdafx.h"

namespace basecross
{
	class StageSelect : public Stage
	{
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		wstring m_StopNowMusic;
		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateTitleSprite();

		//フェードの作成
		void CreateFadeOutSprite();
		void CreateFadeSprite();
		bool m_SelectFlag;

		//ステージ番号の作成
		void StageNumberSprite();

		int m_StageNumber;
		bool onectrl;

		int m_MaxStageNumber;
		
		float m_CoolTime;

	public:
		//構築と破棄
		StageSelect() :Stage() {}
		virtual ~StageSelect() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		void SetNowMusic(wstring NowMusic) {
			m_StopNowMusic = NowMusic;
		}
		wstring GetNowMusic() {
			return m_StopNowMusic;
		}
	};

}