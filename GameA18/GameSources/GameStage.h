/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

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
	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;

	};


}
//end basecross

