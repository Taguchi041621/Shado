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
		GameObject& m_Obj;
		//スケールのZの固定値
		float m_ScaleZ;
	public:
		//構築と破棄
		ShadowObject(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			GameObject& Obj
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

	//--------------------------------------------------------------------------------------
	//	class ShadowObject2 : public GameObject;
	//	用途: オブジェクトの影
	//--------------------------------------------------------------------------------------
	class ShadowObject2 : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		//対応した実態オブジェクトのポインタ
		GameObject& m_Obj;
		//スケールのZの固定値
		float m_ScaleZ;
	public:
		//構築と破棄
		ShadowObject2(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			GameObject& Obj
		);

		virtual ~ShadowObject2();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate();
		virtual void OnUpdate2();
		//影の場所を計算する
		Vec3 ShadowLocation();
	};
	//--------------------------------------------------------------------------------------
	//	class ShadowObject3 : public GameObject;
	//	用途: オブジェクトの影
	//--------------------------------------------------------------------------------------
	class ShadowObject3 : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		//対応した実態オブジェクトのポインタ
		GameObject& m_Obj;
		//スケールのZの固定値
		float m_ScaleZ;
	public:
		//構築と破棄
		ShadowObject3(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			GameObject& Obj
		);

		virtual ~ShadowObject3();
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
		GameObject& m_Obj;
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
			const Vec3& m_Scale, const Vec3& Rotation, GameObject& Obj);
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
		GameObject& m_Obj;
		//スケールのZの固定値
		float m_ScaleZ;
		//ゴールに飛んでいくフラグ
		bool m_GoGoal = false;
		//ゴールに飛ぶ前に回る際の現在時間
		float m_spin = 0.0f;
		//補完の際に使う現在時間
		float m_Lerp = 0.0f;
		//経路を出すための点
		Vec3 p0,p1,p2,p3;
		shared_ptr<MeshResource> m_MeshResource;
		Mat4x4 m_ToAnimeMatrix;

		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		wstring m_StopNowMusic;

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
			const Vec3& m_Scale, const Vec3& Rotation, GameObject& Obj);
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
		void SetNowMusic(wstring NowMusic) {
			m_StopNowMusic = NowMusic;
		}
		wstring GetNowMusic() {
			return m_StopNowMusic;
		}

		void OnTriggerEnter();

		//影の場所を計算する
		Vec3 ShadowLocation();
	};

}