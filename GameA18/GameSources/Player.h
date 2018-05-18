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
		//鍵の取得状況
		int m_Key;
		//データとゲームとの変換行列
		Mat4x4 m_ToAnimeMatrixLeft;
		Mat4x4 m_ToAnimeMatrixRight;
		//死亡判定のためのOBB
		OBB m_DieOBB;
		//死亡状態を持つ変数[1:圧殺]
		int m_Death;

		bool m_GameOverFlag;

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

		//プレイヤーのHP
		void PlayerHP();

		//鍵に触れたときに使う、m_Keyの値を増やす
		void AddKey() { m_Key += 1; }
		//m_Keyの値を取得する
		int GetKey() { return m_Key; }
		//m_Deathの値を取得する
		int GetDeath() { return m_Death; }

		//GameOverSceneを呼び出す
		void GoGameOverScene();
		//GameClearSceneを呼び出す
		void GoGameClearScene();
		//ゴールに入った時に呼ぶ、クリア演出をする
		void InGoal();

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
		//ゲームオーバー管理
		void SetGameOverFlag(bool f) { m_GameOverFlag = f; }
		bool GetGameOverFlag() { return m_GameOverFlag; }
	};

	//--------------------------------------------------------------------------------------
	//	class WaitState : public ObjState<Player>;
	//	用途: 待機状態
	//--------------------------------------------------------------------------------------
	class WaitState : public ObjState<Player>{
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
	//--------------------------------------------------------------------------------------
	//	class WalkState : public ObjState<Player>;
	//	用途: 歩き状態
	//--------------------------------------------------------------------------------------
	class WalkState : public ObjState<Player>{
		WalkState() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<WalkState> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class DiedState : public ObjState<Player>;
	//	用途: 死亡状態
	//--------------------------------------------------------------------------------------
	class DiedState : public ObjState<Player>{
		DiedState() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<DiedState> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class GoalState : public ObjState<Player>;
	//	用途: ゴール状態
	//--------------------------------------------------------------------------------------
	class GoalState : public ObjState<Player> {
		GoalState() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<GoalState> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};


}
//end basecross

