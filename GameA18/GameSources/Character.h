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
		//濃さを持つ
		float m_alpha;

		float m_HengTimer;
		float m_VerticalTimer;
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
	class BlueCube : public GameObject {
		Vec3 m_StartScale;
		Quat m_StartQt;
		Vec3 m_StartPos;
		shared_ptr<MeshResource> m_MeshResource;

		shared_ptr<Rigidbody> m_Rigidbody;

		bool m_MoveFlag;
		bool m_HengMoveFlag;
		bool m_VerticalMoveFlag;
		Vec3 m_Speed;
		//濃さを持つ
		float m_alpha;

		float m_HengTimer;
		float m_VerticalTimer;
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
		BlueCube(const shared_ptr<Stage>& StagePtr,
			const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos, const Vec3& StartSpeed, const bool& Move);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~BlueCube() {}
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
	class YellowCube : public GameObject {
		Vec3 m_StartScale;
		Quat m_StartQt;
		Vec3 m_StartPos;
		shared_ptr<MeshResource> m_MeshResource;

		shared_ptr<Rigidbody> m_Rigidbody;

		bool m_MoveFlag;
		bool m_HengMoveFlag;
		bool m_VerticalMoveFlag;
		Vec3 m_Speed;
		//濃さを持つ
		float m_alpha;

		float m_HengTimer;
		float m_VerticalTimer;
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
		YellowCube(const shared_ptr<Stage>& StagePtr,
			const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos, const Vec3& StartSpeed, const bool& Move);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~YellowCube() {}
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

	//--------------------------------------------------------------------------------------
	///	大砲の元のオブジェクト
	//--------------------------------------------------------------------------------------
	class CannonBase : public GameObject {
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
		CannonBase(const shared_ptr<Stage>& StagePtr,
			const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~CannonBase() {}
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
	//--------------------------------------------------------------------------------------
	///	大砲の元のオブジェクト
	//--------------------------------------------------------------------------------------
	class CannonBaseR : public GameObject {
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
		CannonBaseR(const shared_ptr<Stage>& StagePtr,
			const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~CannonBaseR() {}
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


	//--------------------------------------------------------------------------------------
	///	Paper
	//--------------------------------------------------------------------------------------
	class StageLight : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:
		//構築と破棄
		StageLight(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~StageLight();
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;

	};

}
//end basecross
