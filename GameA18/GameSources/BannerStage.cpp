#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void BannerStage::CreateViewLight()
	{
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 0.0f, -10.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
		//auto PtrView = CreateView<SingleView>();
	}
	void BannerStage::CreateBanner() {
		wstring DateDir;
		App::GetApp()->GetDataDirectory(DateDir);
		auto banner = AddGameObject<SpriteStudioBanner>(DateDir,Vec3(0.5f,0.5f,0.5f),Vec3(0.0f,0.0f,0.0f),Vec3(0.0f,0.0f,0.0f));
		SetSharedGameObject(L"Banner", banner);
	}
	void BannerStage::OnCreate() {
		CreateViewLight();
		CreateBanner();
	}
	void BannerStage::OnUpdate() {
		if (!CreditFlag) {
			//スプライトスタジオロゴのアニメが終わったら
			if (GetSharedGameObject<SpriteStudioBanner>(L"Banner")->GetBannerEnd()) {
				//スプライトスタジオロゴの消去
				RemoveGameObject<SpriteStudioBanner>(GetSharedGameObject<SpriteStudioBanner>(L"Banner"));
				//クレジット画像の表示
				AddGameObject<Sprite>(L"Credit_Link_TX", true,Vec2(1280.0f, 800.0f), Vec3(0, 0.0f, 0.0f));
				//クレジットを表示したというフラグ
				CreditFlag = true;
				//3秒後にシーン遷移
				PostEvent(3.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			}
		}
		else {
			FadeTime += App::GetApp()->GetElapsedTime();
			if (FadeTime >= 2.2f) {
				 auto fade = AddGameObject<SpriteFade>(L"Shadow_TX", true,
					Vec2(840, 600), Vec3(900.0f, 0.0f, 0.0f));
				 fade->SetActionflag(true);
				 FadeTime = -10.0f;
			}
		}
	}

	SpriteStudioBanner::SpriteStudioBanner(const shared_ptr<Stage>& StagePtr,const wstring BaseDir,
		const Vec3& Scale,const Vec3& Rotation,const Vec3& Position)
		: SS5ssae(StagePtr,BaseDir + L"SpriteStudioBanner\\splash512\\",L"splash512_instance.ssae", L"in"),
		m_Scale(Scale), m_Rotation(Rotation),m_Position(Position){
	}
	void SpriteStudioBanner::OnCreate() {
		auto PtrTransform = AddComponent<Transform>();
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(m_Position);
		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(60);
		//アニメーションのループ設定
		SetLooped(false);
		//SetSpriteDraw(true);
	}
	void SpriteStudioBanner::OnUpdate() {
		if (IsAnimeEnd()) {
			BannerEnd = true;
		}

		UpdateAnimeTime(App::GetApp()->GetElapsedTime());
	}
}