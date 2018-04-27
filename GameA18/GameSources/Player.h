/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	プレイヤー
	//--------------------------------------------------------------------------------------
	class Player : public SS5ssae {

		shared_ptr< StateMachine<Player> >  m_StateMachine;	//ステートマシーン
		//カメラのZ軸の切り替え
		float CameraPosZ;
		//カメラの切り替えに使う
		int m_CameraNumber;
		//プレイヤーのHP
		int m_PlayerHP;
		//最高速度
		float m_MaxSpeed;
		//減速率
		float m_Decel;
		//質量
		float m_Mass;
		//文字列の表示
		void DrawStrings();
		//データとゲームとの変換行列
		Mat4x4 m_ToAnimeMatrixLeft;
		Mat4x4 m_ToAnimeMatrixRight;
	public:
		//構築と破棄
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	StagePtr	ステージ
		*/
		//--------------------------------------------------------------------------------------
		Player(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Player() {}
		//アクセサ
		//--------------------------------------------------------------------------------------
		/*!
		コントローラから方向ベクトルを得る
		*/
		//--------------------------------------------------------------------------------------
		float GetMoveVector(int LR) const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	最高速度を得る
		@return	最高速度
		*/
		//--------------------------------------------------------------------------------------
		float GetMaxSpeed() const {
			return m_MaxSpeed;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	減速値を得る
		@return	減速値
		*/
		//--------------------------------------------------------------------------------------
		float GetDecel() const {
			return m_Decel;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	質量を得る
		@return	質量
		*/
		//--------------------------------------------------------------------------------------
		float GetMass() const {
			return m_Mass;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	後更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate2() override;

		//衝突したとき
		virtual void OnCollision(vector<shared_ptr<GameObject>>& OtherVec) override;
		//衝突しているとき
		virtual void OnCollisionExcute(vector<shared_ptr<GameObject>>& OtherVec) override;
		//衝突が終わった時
		virtual void OnCollisionExit(vector<shared_ptr<GameObject>>& OtherVec) override;


		//LRが押されたときカメラを変える
		void CameraChanger();

		//プレイヤーのHP
		void PlayerHP();

		//アクセサ
		shared_ptr< StateMachine<Player> > GetStateMachine() const {
			return m_StateMachine;
		}

		void AnimeChangeMotion(const wstring& key, bool looped);
		void LoopedAnimeUpdateMotion();

		//モーションを実装する関数群
		//移動して向きを移動方向にする
		//移動距離を返す
		float MoveRotationMotion();
	};

	//--------------------------------------------------------------------------------------
	//	class WaitState : public ObjState<Player>;
	//	用途: 待機状態
	//--------------------------------------------------------------------------------------
	class WaitState : public ObjState<Player>
	{
		WaitState() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<WaitState> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};


}
//end basecross

