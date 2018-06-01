#include "stdafx.h"
#include "Project.h"

namespace basecross
{

	void StageSelect::CreateViewLight()
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

	void StageSelect::CreateTitleSprite()
	{
		////ステージへのゲームオブジェクトの追加
		//auto Ptr = AddGameObject<GameObject>();
		//auto PtrTrans = Ptr->GetComponent<Transform>();
		//Quat Qt;
		//Qt.rotationRollPitchYawFromVector(Vec3(0.60, 0, 0));
		//PtrTrans->SetScale(5.0f, 4.0f, 1.0f);
		//PtrTrans->SetQuaternion(Qt);
		//PtrTrans->SetPosition(0.0f, -0.5f, 0.0f);

		//auto ColPtr = Ptr->AddComponent<CollisionRect>();
		////描画コンポーネントの追加
		//auto DrawComp = Ptr->AddComponent<BcPNTStaticDraw>();
		////描画コンポーネントに形状（メッシュ）を設定
		//DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		//DrawComp->SetFogEnabled(true);
		////自分に影が映りこむようにする
		//DrawComp->SetOwnShadowActive(true);

		////描画コンポーネントテクスチャの設定
		//DrawComp->SetTextureResource(L"SELECT_TX");
		AddGameObject<Sprite>(L"WallTexture_TX", false,
			Vec2(1280.0f, 800.0f), Vec3(0, 0.0f, 0.1f));
		AddGameObject<ScaleChangeSprite>(L"SELECT_TEXT_TX", true,
			Vec2(960, 200), Vec3(0, 300, 0.1f), 1.0f);
	}

	void StageSelect::CreateFadeOutSprite()
	{
		auto Fade = AddGameObject<SpriteFadeOut>(L"Shadow_TX", true,
			Vec2(50000 / 4, 30000 / 4), Vec3(0.0f, 0.0f, 0.0f));
		SetSharedGameObject(L"FadeOut", Fade);

	}

	void StageSelect::CreateFadeSprite()
	{
		auto Fade = AddGameObject<SpriteFade>(L"Shadow_TX", true,
			Vec2(840, 600), Vec3(900.0f, 0.0f, 0.0f));
		SetSharedGameObject(L"FadeIn", Fade);

	}
	void StageSelect::StageNumberSprite()
	{
		auto Door = AddGameObject<Sprite>(L"Door_TX", false,
			Vec2(100.0f, 200.0f), Vec3(0, -200.0f, 0.1f));
		SetSharedGameObject(L"0", Door);
		auto Num = AddGameObject<Sprite>(L"0_TX", true,
			Vec2(50.0f, 100.0f), Vec3(0, -10.0f, 0.1f));
		SetSharedGameObject(L"0Num", Num);

		Door = AddGameObject<Sprite>(L"Door_TX", false,
			Vec2(100.0f, 200.0f), Vec3(200, -200.0f, 0.1f));
		SetSharedGameObject(L"1", Door);
		Num = AddGameObject<Sprite>(L"1_TX", true,
			Vec2(50.0f, 100.0f), Vec3(200, -10.0f, 0.1f));
		SetSharedGameObject(L"1Num", Num);

		Door = AddGameObject<Sprite>(L"Door_TX", false,
			Vec2(100.0f, 200.0f), Vec3(400, -200.0f, 0.1f));
		SetSharedGameObject(L"2", Door);
		Num = AddGameObject<Sprite>(L"2_TX", true,
			Vec2(50.0f, 100.0f), Vec3(400, -10.0f, 0.1f));
		SetSharedGameObject(L"2Num", Num);

		Door = AddGameObject<Sprite>(L"Door_TX", false,
			Vec2(100.0f, 200.0f), Vec3(600, -200.0f, 0.1f));
		SetSharedGameObject(L"3", Door);
		Num = AddGameObject<Sprite>(L"3_TX", true,
			Vec2(50.0f, 100.0f), Vec3(600, -10.0f, 0.1f));
		SetSharedGameObject(L"3Num", Num);

		Door = AddGameObject<Sprite>(L"Door_TX", false,
			Vec2(100.0f, 200.0f), Vec3(800, -200.0f, 0.1f));
		SetSharedGameObject(L"4", Door);
		Num = AddGameObject<Sprite>(L"4_TX", true,
			Vec2(50.0f, 100.0f), Vec3(800, -10.0f, 0.1f));
		SetSharedGameObject(L"4Num", Num);

		Door = AddGameObject<Sprite>(L"Door_TX", false,
			Vec2(100.0f, 200.0f), Vec3(1000, -200.0f, 0.1f));
		SetSharedGameObject(L"5", Door);
		Num = AddGameObject<Sprite>(L"5_TX", true,
			Vec2(50.0f, 100.0f), Vec3(1000, -10.0f, 0.1f));
		SetSharedGameObject(L"5Num", Num);

		Door = AddGameObject<Sprite>(L"Door_TX", false,
			Vec2(100.0f, 200.0f), Vec3(1200, -200.0f, 0.1f));
		SetSharedGameObject(L"6", Door);
		Num = AddGameObject<Sprite>(L"6_TX", true,
			Vec2(50.0f, 100.0f), Vec3(1200, -10.0f, 0.1f));
		SetSharedGameObject(L"6Num", Num);

		Door = AddGameObject<Sprite>(L"Door_TX", false,
			Vec2(100.0f, 200.0f), Vec3(1400, -200.0f, 0.1f));
		SetSharedGameObject(L"7", Door);
		Num = AddGameObject<Sprite>(L"7_TX", true,
			Vec2(50.0f, 100.0f), Vec3(1400, -10.0f, 0.1f));
		SetSharedGameObject(L"7Num", Num);

		Door = AddGameObject<Sprite>(L"Door_TX", false,
			Vec2(100.0f, 200.0f), Vec3(1400, -200.0f, 0.1f));
		SetSharedGameObject(L"8", Door);
		Num = AddGameObject<Sprite>(L"8_TX", true,
			Vec2(50.0f, 100.0f), Vec3(1400, -10.0f, 0.1f));
		SetSharedGameObject(L"8Num", Num);

		Door = AddGameObject<Sprite>(L"Door_TX", false,
			Vec2(100.0f, 200.0f), Vec3(1400, -200.0f, 0.1f));
		SetSharedGameObject(L"9", Door);
		Num = AddGameObject<Sprite>(L"9_TX", true,
			Vec2(50.0f, 100.0f), Vec3(1400, -10.0f, 0.1f));
		SetSharedGameObject(L"9Num", Num);

		Door->AddComponent<Action>();
		Door->GetComponent<Action>()->AllActionClear();
		SetSharedGameObject(L"Door", Door);

	}



	void StageSelect::OnCreate()
	{

		m_SelectFlag = true;
		m_StageNumber = 0;
		CreateViewLight();
		//スプライトの作成
		CreateTitleSprite();
		StageNumberSprite();
		CreateFadeOutSprite();
		CreateFadeSprite();
	}

	//更新
	void StageSelect::OnUpdate() {
		auto Door = GetSharedGameObject<Sprite>(L"Door");

		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (m_SelectFlag) {
			if (CntlVec[0].bConnected) {
				if (CntlVec[0].fThumbLX < -0.5) {
					if (onectrl == false)
					{
						Door->GetComponent<Action>()->AllActionClear();
						Door->GetComponent<Action>()->
							AddMoveTo(0.1f, Vec3(-200.0f, 0.0f, 0.0f));

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
						m_AudioObjectPtr->AddAudioResource(L"se2");
						m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.1f);
						SetNowMusic(L"se2");

						onectrl = true;
						m_StageNumber += -1;
					}
				}
				else if (CntlVec[0].fThumbLX > 0.5) {
					if (onectrl == false)
					{
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
						m_AudioObjectPtr->AddAudioResource(L"se2");
						m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.1f);
						SetNowMusic(L"se2");

						onectrl = true;
						m_StageNumber += 1;
					}
				}
				else
				{
					onectrl = false;
				}

				if (m_StageNumber < 0) {
					m_StageNumber = 9;
				}
				else if (m_StageNumber > 9) {
					m_StageNumber = 0;
				}
				//Aボタン
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
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
					m_SelectFlag = false;
					ScenePtr->SetRespawnFlag(false);
					PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
				}
			}
		}

		//ステージの数ループさせる
		for (int i = 0; i < 10; i++) {
			auto StageNum = to_wstring(i);
			auto Door = GetSharedGameObject<Sprite>(StageNum);
			auto Num = GetSharedGameObject<Sprite>(StageNum + L"Num");
			//今選んでるステージと同じならアクションする
			if (i == m_StageNumber) {
				Door->SetActionflag(true);
				Num->SetActionflag(true);
			}
			//違うステージならアクション切る
			if (i != m_StageNumber) {
				Door->SetActionflag(false);
				Num->SetActionflag(false);

			}
			ScenePtr->SetStageNumber(m_StageNumber);
		}
	}
}