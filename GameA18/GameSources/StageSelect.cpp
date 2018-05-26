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
		AddGameObject<Sprite>(L"SELECT_TX", false,
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
		auto Zero = AddGameObject<Sprite>(L"0_TX", false,
			Vec2(100.0f, 200.0f), Vec3(0, 0.0f, 0.1f));
		SetSharedGameObject(L"0", Zero);
		auto One = AddGameObject<Sprite>(L"1_TX", false,
			Vec2(100.0f, 200.0f), Vec3(200, 0.0f, 0.1f));
		SetSharedGameObject(L"1", One);
		auto Two = AddGameObject<Sprite>(L"2_TX", false,
			Vec2(100.0f, 200.0f), Vec3(400, 0.0f, 0.1f));
		SetSharedGameObject(L"2", Two);
		auto Three = AddGameObject<Sprite>(L"3_TX", false,
			Vec2(100.0f, 200.0f), Vec3(600, 0.0f, 0.1f));
		SetSharedGameObject(L"3", Three);
		auto Four = AddGameObject<Sprite>(L"4_TX", false,
			Vec2(100.0f, 200.0f), Vec3(800, 0.0f, 0.1f));
		SetSharedGameObject(L"4", Four);
		auto Five = AddGameObject<Sprite>(L"5_TX", false,
			Vec2(100.0f, 200.0f), Vec3(1000, 0.0f, 0.1f));
		SetSharedGameObject(L"5", Five);
		auto Six = AddGameObject<Sprite>(L"6_TX", false,
			Vec2(100.0f, 200.0f), Vec3(1200, 0.0f, 0.1f));
		SetSharedGameObject(L"6", Six);
		auto Seven = AddGameObject<Sprite>(L"7_TX", false,
			Vec2(100.0f, 200.0f), Vec3(1400, 0.0f, 0.1f));
		SetSharedGameObject(L"7", Seven);
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
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (m_SelectFlag) {
			if (CntlVec[0].bConnected) {
				if (CntlVec[0].fThumbLX < -0.5) {
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
					m_StageNumber = 7;
				}
				else if (m_StageNumber > 7) {
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

		auto Zero = GetSharedGameObject<Sprite>(L"0");
		auto One = GetSharedGameObject<Sprite>(L"1");
		auto Two = GetSharedGameObject<Sprite>(L"2");
		auto Three = GetSharedGameObject<Sprite>(L"3");
		auto Four = GetSharedGameObject<Sprite>(L"4");
		auto Five = GetSharedGameObject<Sprite>(L"5");
		auto Six = GetSharedGameObject<Sprite>(L"6");
		auto Seven = GetSharedGameObject<Sprite>(L"7");
		switch (m_StageNumber) {

		case 0:
			Zero->SetActionflag(true);
			One->SetActionflag(false);
			Two->SetActionflag(false);
			Three->SetActionflag(false);
			Four->SetActionflag(false);
			Five->SetActionflag(false);
			Six->SetActionflag(false);
			Seven->SetActionflag(false);
			ScenePtr->SetStageNumber(m_StageNumber);
			break;
		case 1:
			Zero->SetActionflag(false);
			One->SetActionflag(true);
			Two->SetActionflag(false);
			Three->SetActionflag(false);
			Four->SetActionflag(false);
			Five->SetActionflag(false);
			Six->SetActionflag(false);
			Seven->SetActionflag(false);
			ScenePtr->SetStageNumber(m_StageNumber);
			break;
		case 2:
			Zero->SetActionflag(false);
			One->SetActionflag(false);
			Two->SetActionflag(true);
			Three->SetActionflag(false);
			Four->SetActionflag(false);
			Five->SetActionflag(false);
			Six->SetActionflag(false);
			Seven->SetActionflag(false);
			ScenePtr->SetStageNumber(m_StageNumber);
			break;
		case 3:
			Zero->SetActionflag(false);
			One->SetActionflag(false);
			Two->SetActionflag(false);
			Three->SetActionflag(true);
			Four->SetActionflag(false);
			Five->SetActionflag(false);
			Six->SetActionflag(false);
			Seven->SetActionflag(false);
			ScenePtr->SetStageNumber(m_StageNumber);
			break;
		case 4:
			Zero->SetActionflag(false);
			One->SetActionflag(false);
			Two->SetActionflag(false);
			Three->SetActionflag(false);
			Four->SetActionflag(true);
			Five->SetActionflag(false);
			Six->SetActionflag(false);
			Seven->SetActionflag(false);
			ScenePtr->SetStageNumber(m_StageNumber);
			break;
		case 5:
			Zero->SetActionflag(false);
			One->SetActionflag(false);
			Two->SetActionflag(false);
			Three->SetActionflag(false);
			Four->SetActionflag(false);
			Five->SetActionflag(true);
			Six->SetActionflag(false);
			Seven->SetActionflag(false);
			ScenePtr->SetStageNumber(m_StageNumber);
			break;
		case 6:
			Zero->SetActionflag(false);
			One->SetActionflag(false);
			Two->SetActionflag(false);
			Three->SetActionflag(false);
			Four->SetActionflag(false);
			Five->SetActionflag(false);
			Six->SetActionflag(true);
			Seven->SetActionflag(false);
			ScenePtr->SetStageNumber(m_StageNumber);
			break;
		case 7:
			Zero->SetActionflag(false);
			One->SetActionflag(false);
			Two->SetActionflag(false);
			Three->SetActionflag(false);
			Four->SetActionflag(false);
			Five->SetActionflag(false);
			Six->SetActionflag(false);
			Seven->SetActionflag(true);
			ScenePtr->SetStageNumber(m_StageNumber);
			break;
		}

	}

}