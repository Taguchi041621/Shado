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
		void CreateUI();

		void CreateFadeOutSprite();
		void CreateFadeSprite();
		bool m_SelectFlag;

		//選択関係
		bool ActionFlag;
		bool ControllerFlag;
		bool SelectFlag;
		float ThumbTimer;
		bool ThumbFlag;
		int NowSelect;

		float m_ScaleTimer;
		bool m_ScaleFlag;
		int Number;
	public:
		//構築と破棄
		ClearStage() :Stage() {}
		virtual ~ClearStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		//シーン遷移のセレクト
		void Select();
	};

}