#pragma once
#include "stdafx.h"

namespace basecross {
	class BannerStage : public Stage {
		void CreateBanner();
		void CreateViewLight();
		bool CreditFlag = false;
		float FadeTime = 0.0f;
	public:
		//�\�z�Ɣj��
		BannerStage() : Stage() {}
		virtual ~BannerStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;

	};

	//--------------------------------------------------------------------------------------
	//	SpriteStudio�̃o�i�[
	//--------------------------------------------------------------------------------------
	class SpriteStudioBanner : public SS5ssae {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		bool BannerEnd = false;

	public:
		//�\�z�Ɣj��
		SpriteStudioBanner(const shared_ptr<Stage>& StagePtr,
			const wstring BaseDir,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
			);

		virtual ~SpriteStudioBanner() {};
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate();

		bool GetBannerEnd() { return BannerEnd; };
	};
}