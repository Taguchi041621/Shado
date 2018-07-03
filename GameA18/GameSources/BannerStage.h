#pragma once
#include "stdafx.h"

namespace basecross {
	class BannerStage : public Stage {
		void CreateBanner();
		void CreateViewLight();
		bool CreditFlag = false;
		float FadeTime = 0.0f;
	public:
		//構築と破棄
		BannerStage() : Stage() {}
		virtual ~BannerStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;

	};

	//--------------------------------------------------------------------------------------
	//	SpriteStudioのバナー
	//--------------------------------------------------------------------------------------
	class SpriteStudioBanner : public SS5ssae {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		bool BannerEnd = false;

	public:
		//構築と破棄
		SpriteStudioBanner(const shared_ptr<Stage>& StagePtr,
			const wstring BaseDir,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
			);

		virtual ~SpriteStudioBanner() {};
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate();

		bool GetBannerEnd() { return BannerEnd; };
	};
}