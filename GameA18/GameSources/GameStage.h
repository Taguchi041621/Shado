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
		//プレートの作成
		void CreatePlate();
		//かべ
		void CreateWall();
		//プレイヤーの作成
		void CreatePlayer();
		//白いブロックの作成
		void CreateWhiteCube();
		//
		void CreateGoal();
		//
		void CreateKeyItem();

		CsvFile m_Csv;//CSV関連の変数
					  //DataIDを管理するフラグ
		bool dataIdFlag = false;
	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		//作るステージを選択する
		void CreateStage(int num);
		void Csv();
	};


}
//end basecross

