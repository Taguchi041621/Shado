/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class WhiteCube : public GameObject {
		Vec3 m_StartScale;
		Quat m_StartQt;
		Vec3 m_StartPos;
		shared_ptr<MeshResource> m_MeshResource;

		shared_ptr<Rigidbody> m_Rigidbody;

		bool m_MoveFlag;
		bool m_HengMoveFlag;
		bool m_VerticalMoveFlag;
		Vec3 m_Speed;

		float m_Timer;
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
		WhiteCube(const shared_ptr<Stage>& StagePtr,
			const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos, const Vec3& StartSpeed, const bool& Move);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~WhiteCube() {}
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

		//virtual  const Light& OnGetDrawLight() const override {

		//}
	};

	class Goal : public GameObject {
		Vec3 m_StartScale;
		Quat m_StartQt;
		Vec3 m_StartPos;
		shared_ptr<MeshResource> m_MeshResource;
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
		Goal(const shared_ptr<Stage>& StagePtr,
			const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Goal() {}
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

		//virtual  const Light& OnGetDrawLight() const override {

		//}
	};

	class Triangle : public GameObject {
		Vec3 m_StartScale;
		Quat m_StartQt;
		Vec3 m_StartPos;
		shared_ptr<MeshResource> m_MeshResource;
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
		Triangle(const shared_ptr<Stage>& StagePtr,
			const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Triangle() {}
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
//end basecross
