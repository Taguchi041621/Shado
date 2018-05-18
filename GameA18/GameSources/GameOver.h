#pragma once
#include "stdafx.h"

namespace basecross

{
	class GameOverStage : public Stage
	{
		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateTitleSprite();
		//フェードの作成
		void CreateFadeOutSprite();
		void CreateFadeSprite();
		bool m_SelectFlag;
	public:
		//構築と破棄
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
	};

}