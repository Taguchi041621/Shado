#pragma once
#include "stdafx.h"

namespace basecross {
	//------------------------------------------------------------------------------------------
	///敵(影)
	//------------------------------------------------------------------------------------------
	class ShadowEnemy : public SS5ssae {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		GameObject& m_Obj;
		//スケールのZの固定値
		float m_ScaleZ;
		shared_ptr<MeshResource> m_MeshResource;
		Mat4x4 m_ToAnimeMatrix;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	StartScale	初期スケール
		@param[in]	StartQt	初期回転
		@param[in]	StartPos	初期位置
		*/
		//--------------------------------------------------------------------------------------
		ShadowEnemy(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
			const Vec3& m_Scale, const Vec3& Rotation, GameObject& Obj);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~ShadowEnemy() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief 更新
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;

		void OnTriggerEnter();

		//影の場所を計算する
		Vec3 ShadowLocation();
	};


	//------------------------------------------------------------------------------------------
	///敵の実体
	//------------------------------------------------------------------------------------------
	class Enemy : public GameObject {
		Vec3 m_KeyPos;
	public:
		Enemy(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		virtual ~Enemy() {}
		//初期化
		virtual void OnCreate() override;

		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//	大砲
	//--------------------------------------------------------------------------------------
	class Cannon : public SS5ssae {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		//対応した実態オブジェクトのポインタ
		GameObject& m_Obj;
		//スケールのZの固定値
		float m_ScaleZ;
		//このオブジェクトのみで使用するスクエアメッシュ
		shared_ptr<MeshResource> m_SquareMeshResource;

		float m_CoolTime;
		bool m_BulletFlag;

		Mat4x4 m_ToAnimeMatrix;

		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		wstring m_StopNowMusic;

	public:
		//構築と破棄
		Cannon(const shared_ptr<Stage>& StagePtr,
			const wstring BaseDir,
			const Vec3& Scale,
			const Vec3& Rotation,
			GameObject& Obj
		);

		virtual ~Cannon();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate();
		void SetNowMusic(wstring NowMusic) {
			m_StopNowMusic = NowMusic;
		}
		wstring GetNowMusic() {
			return m_StopNowMusic;
		}
		virtual void OnUpdate2();
		//影の場所を計算する
		Vec3 ShadowLocation();
	};

	//--------------------------------------------------------------------------------------
	//	弾
	//--------------------------------------------------------------------------------------

	class Bullet : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		//スケールのZの固定値
		float m_ScaleZ;
		//このオブジェクトのみで使用するスクエアメッシュ
		shared_ptr<MeshResource> m_SquareMeshResource;
	public:
		//構築と破棄
		Bullet(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);

		virtual ~Bullet();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate();
		virtual void OnUpdate2();
		void OnTriggerEnter();
	};
}