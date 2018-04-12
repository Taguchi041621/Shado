#pragma once
#include "stdafx.h"

namespace basecross
{
	class StageSelect : public Stage
	{
		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateTitleSprite();
	public:
		//構築と破棄
		StageSelect() :Stage() {}
		virtual ~StageSelect() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
	};

}