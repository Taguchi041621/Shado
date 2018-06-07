#pragma once
#include "stdafx.h"

namespace basecross

{

	//--------------------------------------------------------------------------------------
	///	スプライト
	//--------------------------------------------------------------------------------------
	class Sprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;

		bool m_Actionflag;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	TextureKey	テクスチャキー
		@param[in]	Trace	透明処理するかどうか
		@param[in]	StartScale	初期スケール
		@param[in]	StartPos	初期位置
		*/
		//--------------------------------------------------------------------------------------
		Sprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Sprite();
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

		void SetActionflag(bool Action) { m_Actionflag = Action; }
		bool SetActionflag() { return m_Actionflag; };
	};

	//------------------------------------------------------------------------------------------
	///鍵の取得状況を画面に表示する
	//------------------------------------------------------------------------------------------
	class HaveKeys : public GameObject {
		//ステージにある鍵の数
		int m_StageKeys;
		//プレイヤーが持っている鍵の数
		int m_haveKeys;
		//テクスチャのキー
		const wstring& m_TextureKey;
		//表示する左からの順番
		int m_order;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	TextureKey	表示するテクスチャのキー
		@param[in]	order	何番目の鍵
		*/
		//-------------------------------------------------------------------------------------
		HaveKeys(const shared_ptr<Stage>& StagePtr, wstring& TextureKey,int order);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~HaveKeys();
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
	};

	class MiniMap : public GameObject {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	TextureKey	表示するテクスチャのキー
		@param[in]	order	何番目の鍵
		*/
		//-------------------------------------------------------------------------------------
		MiniMap(const shared_ptr<Stage>& StagePtr);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~MiniMap();
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
	};

	//------------------------------------------------------------------------------------------
	///大きさの変わるスプライト
	//------------------------------------------------------------------------------------------
	class ScaleChangeSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;

		bool m_SceleFlag;
		float m_Timer;
		float f;

		bool m_ScaleChangeFlag;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	TextureKey	テクスチャキー
		@param[in]	Trace	透明処理するかどうか
		@param[in]	StartScale	初期スケール
		@param[in]	StartPos	初期位置
		*/
		//--------------------------------------------------------------------------------------
		ScaleChangeSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos, const float f,bool ScaleChangeFlag);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~ScaleChangeSprite();
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

		bool GetScaleChangeFlag() { return m_ScaleChangeFlag; }
		void SetScaleChangeFlag(bool f) { m_ScaleChangeFlag = f; }
	};

	//--------------------------------------------------------------------------------------
	///	数字スプライト
	//--------------------------------------------------------------------------------------
	class ScoreSprite : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_Score;
		//桁数
		UINT m_NumberOfDigits;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices;

		bool m_SceleFlag;
		float m_Timer;
		float m_ChangeFloat;

		bool m_ScaleChangeFlag;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		@param[in]	StagePtr	ステージ
		@param[in]	NumberOfDigits	桁数
		@param[in]	TextureKey	テクスチャキー
		@param[in]	Trace	透明処理するかどうか
		@param[in]	StartScale	初期スケール
		@param[in]	StartPos	初期位置
		*/
		//--------------------------------------------------------------------------------------
		ScoreSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos ,float Score,bool ScaleChange,float ChangeFloat);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~ScoreSprite() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief スコアのセット
		@param[in]	f	値
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetScore(float f) {
			m_Score = f;
		}
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

		void ScaleChange(float f);

		int GetNumberOfDigits() { return m_NumberOfDigits; }
		void SetNumberOfDigits(int i) { m_NumberOfDigits = 1; }

		bool GetScaleChangeFlag() { return m_ScaleChangeFlag; }
		void SetScaleChangeFlag(bool f) { m_ScaleChangeFlag = f; }
	};

	//------------------------------------------------------------------------------------------
	///Tutorial
	//------------------------------------------------------------------------------------------
	class Tutorial : public SS5ssae {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		float m_ScaleZ;

		shared_ptr<MeshResource> m_MeshResource;
		Mat4x4 m_ToAnimeMatrix;
	public:
		//--------------------------------------------------------------------------------------
		//コンストラクタ
		//--------------------------------------------------------------------------------------
		Tutorial(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
			const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Tutorial() {}
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
	};

}