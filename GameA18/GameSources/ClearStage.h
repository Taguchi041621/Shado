#pragma once
#include "stdafx.h"

namespace basecross

{
	class ClearStage : public Stage
	{
		//ビューの作成
		void CreateViewLight();
		//スプライトの作成
		void CreateTitleSprite();
	public:
		//構築と破棄
		ClearStage() :Stage() {}
		virtual ~ClearStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
	};

}