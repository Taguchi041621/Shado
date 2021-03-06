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
		//初期ポジション
		Vec3 m_Position;
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
		//死亡状態を持つ変数[1:圧殺]
		int m_Death;
		//落下スピード
		float m_FallSpeed;
		//落下スピードの初期値
		float m_FallSpeedFirst;

		bool m_GameClearFlag;
		bool m_GameOverFlag;
		bool m_FadeFlag;


		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		wstring m_StopNowMusic;

		bool m_ParentFlag;

		bool m_StandFlag;

		bool m_DamageFlag;

	public:
		enum class InputType {
			LeftStick,
			RightStick
		};
		enum class PlayerDirection {
			LEFT,
			RIGHT
		};
		PlayerDirection m_RightOrLeft;


		//構築と破棄
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		@param[in]	StagePtr	ステージ
		*/
		//--------------------------------------------------------------------------------------
		Player(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir,const Vec3 pos);
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
		float GetMoveLeftVectorX() const;//左
		float GetMoveRightVectorX() const;//右
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
		//物体にめり込まないように押し出す
		void Extrusion(const shared_ptr<GameObject>& OtherVec);
		//当たっているかを調べて、足元にいたら親にする
		void FindParent(const shared_ptr<GameObject>& OtherVec);
		//プレイヤーのHP
		void PlayerHP();
		//着地時に煙を出す
		void LandingDirecting();

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

		void Damage(CannonBase::CanonDirection LR);

		///音声
		void SetNowMusic(wstring NowMusic) {
			m_StopNowMusic = NowMusic;
		}
		wstring GetNowMusic() {
			return m_StopNowMusic;
		}

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

		void SetGameClearFlag(bool f) { m_GameClearFlag = f; }
		bool GetGameClearFlag() { return m_GameClearFlag; }

		void SetFadeFlag(bool f) { m_FadeFlag = f; }
		bool GetFadeFlag() { return m_FadeFlag; }

		void SetParentFlag(bool f) { m_ParentFlag = f; }
		bool GetParentFlag() { return m_ParentFlag; }

		void SetStandFlag(bool f) { m_StandFlag = f; }
		bool GetStandFlag() { return m_StandFlag; }

		void SetDamageFlag(bool f) { m_DamageFlag = f; }
		bool GetDamageFlag() { return m_DamageFlag; }

		void SetRightOrLeft(PlayerDirection f) { m_RightOrLeft = f; }
		PlayerDirection GetRightOrLeft() { return m_RightOrLeft; }
	};

	//--------------------------------------------------------------------------------------
	//	class FallState : public ObjState<Player>;
	//	用途: 落下状態
	//--------------------------------------------------------------------------------------
	class FallState : public ObjState<Player>
	{
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		float m_Timer;
		bool m_FallFlag;
		FallState() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<FallState> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class StandState : public ObjState<Player>;
	//	用途: 起き上がり状態
	//--------------------------------------------------------------------------------------
	class StandState : public ObjState<Player>
	{
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		StandState() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<StandState> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class LandingState : public ObjState<Player>;
	//	用途: 着地状態
	//--------------------------------------------------------------------------------------
	class LandingState : public ObjState<Player>
	{
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;

		LandingState() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<LandingState> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class WaitState : public ObjState<Player>;
	//	用途: 待機状態
	//--------------------------------------------------------------------------------------
	class WaitState : public ObjState<Player>
	{
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;

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
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
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
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;

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

	//--------------------------------------------------------------------------------------
	//	class DamageState1 : public ObjState<Player>;
	//	用途: Damage状態
	//--------------------------------------------------------------------------------------
	class DamageState1 : public ObjState<Player> {
		DamageState1() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<DamageState1> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class DamageState2 : public ObjState<Player>;
	//	用途: Damage状態
	//--------------------------------------------------------------------------------------
	class DamageState2 : public ObjState<Player> {
		DamageState2() {}
	public:
		//ステートのインスタンス取得
		static shared_ptr<DamageState2> Instance();
		//ステートに入ったときに呼ばれる関数
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//ステート実行中に毎ターン呼ばれる関数
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//ステートにから抜けるときに呼ばれる関数
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};


}
//end basecross

