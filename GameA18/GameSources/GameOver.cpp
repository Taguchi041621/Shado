#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void GameOverStage::CreateViewLight()
	{
		//auto PtrView = CreateView<SingleView>();
		////ビューのカメラの設定
		//auto PtrCamera = ObjectFactory::Create<Camera>();
		//PtrView->SetCamera(PtrCamera);
		//PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		//PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		////マルチライトの作成
		//auto PtrMultiLight = CreateLight<MultiLight>();
		////デフォルトのライティングを指定
		//PtrMultiLight->SetDefaultLighting();
		auto PtrView = CreateView<SingleView>();
		//シャドウマップは使用しない
		SetShadowmapDraw(false);
	}

	void GameOverStage::CreateTitleSprite()
	{
		////ステージへのゲームオブジェクトの追加
		//auto Ptr = AddGameObject<GameObject>();
		//auto PtrTrans = Ptr->GetComponent<Transform>();
		//Quat Qt;
		//Qt.rotationRollPitchYawFromVector(Vec3(1.0, 0, 0));
		//PtrTrans->SetScale(5.5f, 4.0f, 1.0f);
		//PtrTrans->SetQuaternion(Qt);
		//PtrTrans->SetPosition(0.0f, 0.5f, 0.0f);

		//auto ColPtr = Ptr->AddComponent<CollisionRect>();
		////描画コンポーネントの追加
		//auto DrawComp = Ptr->AddComponent<BcPNTStaticDraw>();
		////描画コンポーネントに形状（メッシュ）を設定
		//DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		//DrawComp->SetFogEnabled(true);
		////自分に影が映りこむようにする
		//DrawComp->SetOwnShadowActive(true);

		////描画コンポーネントテクスチャの設定
		//DrawComp->SetTextureResource(L"GAMEOVER_TX");

		//AddGameObject<TitleSprite>(L"TITLE_TX", false,
		//	Vec2(1000.0f, 600.0f), Vec2(0.0f, 0.0f));
		AddGameObject<Sprite>(L"GAMEOVER_TX", false,
			Vec2(1280.0f, 800.0f), Vec3(0, 0.0f, 0.1f));
	}
	void GameOverStage::CreateFadeOutSprite()
	{
		auto Fade = AddGameObject<SpriteFadeOut>(L"Shadow_TX", true,
			Vec2(50000 / 4, 30000 / 4), Vec3(0.0f, 600.0f, 0.1f));
		SetSharedGameObject(L"FadeOut", Fade);

	}

	void GameOverStage::CreateFadeSprite()
	{
		auto Fade = AddGameObject<SpriteFade>(L"Shadow_TX", true,
			Vec2(840, 600), Vec3(900.0f, 0.0f, 0.1f));
		SetSharedGameObject(L"FadeIn", Fade);

	}

	void GameOverStage::OnCreate()
	{
		m_SelectFlag = false;
		CreateViewLight();
		//スプライトの作成
		CreateTitleSprite();
		CreateFadeOutSprite();
		CreateFadeSprite();
	}

	//更新
	void GameOverStage::OnUpdate() {
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {

			//Aボタン
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A && !m_SelectFlag) {
				if (m_StopNowMusic != L"")
				{
					m_AudioObjectPtr->Stop(m_StopNowMusic);
				}
				wstring DataDir;
				//サンプルのためアセットディレクトリを取得
				//App::GetApp()->GetAssetsDirectory(DataDir);
				//各ゲームは以下のようにデータディレクトリを取得すべき
				App::GetApp()->GetDataDirectory(DataDir);

				m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
				m_AudioObjectPtr->AddAudioResource(L"se");
				m_AudioObjectPtr->Start(L"se", XAUDIO2_NO_LOOP_REGION, 0.1f);
				SetNowMusic(L"se");

				auto FadeIn = GetSharedGameObject<SpriteFade>(L"FadeIn");
				FadeIn->SetActionflag(true);
				m_SelectFlag = true;
				PostEvent(2.4f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStageSelect");
			}
		}
	}
}