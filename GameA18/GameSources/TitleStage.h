#pragma once
#include "stdafx.h"

namespace basecross

{
	class TitleStage : public Stage
	{
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		wstring m_StopNowMusic;
		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateTitleSprite();

		void CreateFadeSprite();

		bool m_SelectFlag;
	public:
		//構築と破棄
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;

		///音声
		void SetNowMusic(wstring NowMusic) {
			m_StopNowMusic = NowMusic;
		}
		wstring GetNowMusic() {
			return m_StopNowMusic;
		}
	};

}