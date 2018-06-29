/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

#define RadToDeg 180.0f / 3.1415f
#define DegToRad 3.1415f/180.0f

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		//かべ
		void CreateWall();
		//鍵の取得状況表示
		void CreateHaveKeys();
		//敵
		void CreateEnemy();
		//ミニマップ
		void CreateMiniMap();
		//画面端を知らせる演出
		void CreateMoveEnd();
		//ライトの位置を知らせる演出
		void CreateLightSign();
		//ライト代わりのオブジェクト
		void CreateLightObject();
		CsvFile m_Csv;//CSV関連の変数
					  //DataIDを管理するフラグ
		bool dataIdFlag = false;

		bool m_ClearFlag;

		//フェードの作成
		void CreateFadeOutSprite();
		void CreateFadeSprite();

		void CreatePause();

		void CreateTutorial();

		//選択関係
		bool ActionFlag;
		bool ControllerFlag;
		bool SelectFlag;
		float ThumbTimer;
		bool ThumbFlag;
		int NowSelect;

		float m_ScaleTimer;
		bool m_ScaleFlag;

	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		void Csv();

		bool GetClearFlag() { return m_ClearFlag; }
		void SetClearFlag(bool f) { m_ClearFlag = f; }
	};


}
//end basecross

