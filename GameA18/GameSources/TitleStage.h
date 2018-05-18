#pragma once
#include "stdafx.h"

namespace basecross

{
	class TitleStage : public Stage
	{
		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateTitleSprite();

		void CreateFadeSprite();
	public:
		//構築と破棄
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
	};

}