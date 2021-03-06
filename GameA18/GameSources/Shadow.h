#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class ShadowObject : public GameObject;
	//	用途: オブジェクトの影
	//--------------------------------------------------------------------------------------
	class ShadowObject : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		//対応した実態オブジェクトのポインタ
		weak_ptr<GameObject> m_Obj;
		//スケールのZの固定値
		float m_ScaleZ;
		float m_RemoveTime = 0.0f;
	public:
		//構築と破棄
		ShadowObject(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			weak_ptr<GameObject> Obj
			);

		virtual ~ShadowObject();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate();
		virtual void OnUpdate2();
		//影の場所を計算する
		Vec3 ShadowLocation();
	};
	//------------------------------------------------------------------------------------------
	///ゴールの役割をする影
	//------------------------------------------------------------------------------------------
	class ShadowGoal : public SS5ssae {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		weak_ptr<GameObject> m_Obj;
		//スケールのZの固定値
		float m_ScaleZ;

		shared_ptr<MeshResource> m_MeshResource;
		Mat4x4 m_ToAnimeMatrixDark;
		Mat4x4 m_ToAnimeMatrixLight;

		bool flag;
		bool m_LightFlag;
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
		ShadowGoal(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
			const Vec3& m_Scale, const Vec3& Rotation, weak_ptr<GameObject> Obj);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~ShadowGoal() {}
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
		void SetLightFlag(bool f) { m_LightFlag = f; };

		//影の場所を計算する
		Vec3 ShadowLocation();
	};
	//------------------------------------------------------------------------------------------
	///鍵の役割をする影
	//------------------------------------------------------------------------------------------
	class ShadowKey : public SS5ssae {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		weak_ptr<GameObject> m_Obj;
		//スケールのZの固定値
		float m_ScaleZ;
		//ゴールに飛んでいくフラグ
		bool m_GoGoal = false;
		//ゴールに飛ぶ前に回る際の現在時間
		float m_spin = 0.0f;
		//補完の際に使う現在時間
		float m_Lerp = 0.0f;
		//経路を出すための点
		Vec3 p0,p1;
		shared_ptr<MeshResource> m_MeshResource;
		Mat4x4 m_ToAnimeMatrix;

		shared_ptr<MultiAudioObject> m_AudioObjectPtr;

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
		ShadowKey(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
			const Vec3& m_Scale, const Vec3& Rotation, weak_ptr<GameObject> Obj);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~ShadowKey() {}
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

}