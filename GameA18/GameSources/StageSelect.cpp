#include "stdafx.h"
#include "Project.h"

namespace basecross
{

	void StageSelect::CreateViewLight()
	{
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		//auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		//PtrMultiLight->SetDefaultLighting();
		//auto PtrView = CreateView<SingleView>();
		////シャドウマップは使用しない
		//SetShadowmapDraw(false);

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
		AddGameObject<Sprite>(L"SELECT_TEXT_TX", true,
			Vec2(960, 200), Vec3(0, 270, 0.1f));
		AddGameObject<Sprite>(L"TITLE_SHADOW_TX", true,
			Vec2(1280.0f*1.1, 800.0f*1.1), Vec3(0, 0, 0.1f));
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
		int interval = 0;
		for (int i = 1; i <= m_MaxStageNumber; i++) {
			interval = 380 * (i - m_StageNumber);
			auto Door = AddGameObject<ScaleChangeSprite>(L"Door_TX", false,
				Vec2(200.0f*1.2, 400.0f*1.2f), Vec3(0 + interval, -160.0f, 0.0f),1.0f,false);
			shared_ptr<ScoreSprite> Number;
			if (i < 10) {
				Number = AddGameObject<ScoreSprite>(1,
					L"NUMBER_TX",
					true,
					Vec2(100.0f, 100.0f),
					Vec3(-10 + interval, -40.0f, 0.0f),
					i,
					false, 0.3f);
			}
			else {
				Number = AddGameObject<ScoreSprite>(2,
					L"NUMBER_TX",
					true,
					Vec2(100.0f, 100.0f),
					Vec3(-10 + interval, -40.0f, 0.0f),
					i,
					false, 0.3f);
			}
			interval += 380;
			SetSharedGameObject(L"Door" + Util::IntToWStr(i), Door);
			SetSharedGameObject(L"ScoreSprite" + Util::IntToWStr(i), Number);
			Door->AddComponent<Action>();
			Number->AddComponent<Action>();
			if (i == m_StageNumber)
			{
				Door->SetScaleChangeFlag(true);
				//Number->SetScaleChangeFlag(true);
			}
		}
	}



	void StageSelect::OnCreate()
	{
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		m_MaxStageNumber = 10;
		m_SelectFlag = true;
		m_StageNumber = ScenePtr->GetStageNumber();
		m_CoolTime = 0;
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
		auto Time = App::GetApp()->GetElapsedTime();
		if (onectrl)
		{
			m_CoolTime += Time;
			if (m_CoolTime >= 0.4f)
			{
				onectrl = false;
				m_CoolTime = 0;
			}
		}
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (m_SelectFlag) {
			if (CntlVec[0].bConnected) {
				if (CntlVec[0].fThumbLX < -0.5) {
					if (onectrl == false)
					{
						if (!(m_StageNumber == 1)) {
							for (int i = 1; i < m_MaxStageNumber; i++) {
								auto Door = GetSharedGameObject<ScaleChangeSprite>(L"Door" + Util::IntToWStr(i));
								auto Number = GetSharedGameObject<ScoreSprite>(L"ScoreSprite" + Util::IntToWStr(i));
								Door->GetComponent<Action>()->AllActionClear();
								Number->GetComponent<Action>()->AllActionClear();
								Door->GetComponent<Action>()->AddMoveBy(0.3f, Vec3(380.0f, 0, 0));
								Number->GetComponent<Action>()->AddMoveBy(0.3f, Vec3(380.0f, 0, 0));
								Door->GetComponent<Action>()->Run();
								Number->GetComponent<Action>()->Run();
								if(i== m_StageNumber-1){
									Door->SetScaleChangeFlag(true);
									//Number->SetScaleChangeFlag(true);
								}
								else {
									Door->SetScaleChangeFlag(false);
									Number->SetScaleChangeFlag(false);
								}
							}
							m_StageNumber -= 1;


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
							
						}
					}
				}
				else if (CntlVec[0].fThumbLX > 0.5) {
					if (onectrl == false)
					{
						if (!(m_StageNumber == m_MaxStageNumber-1)) {
							for (int i = 1; i < m_MaxStageNumber; i++) {
								auto Door = GetSharedGameObject<ScaleChangeSprite>(L"Door" + Util::IntToWStr(i));
								auto Number = GetSharedGameObject<ScoreSprite>(L"ScoreSprite" + Util::IntToWStr(i));
								Door->GetComponent<Action>()->AllActionClear();
								Number->GetComponent<Action>()->AllActionClear();
								Door->GetComponent<Action>()->AddMoveBy(0.3f, Vec3(-380.0f, 0, 0));
								Number->GetComponent<Action>()->AddMoveBy(0.3f, Vec3(-380.0f, 0, 0));
								Door->GetComponent<Action>()->Run();
								Number->GetComponent<Action>()->Run();
								if (i == m_StageNumber+1) {
									Door->SetScaleChangeFlag(true);
									//Number->SetScaleChangeFlag(true);
								}
								else {
									Door->SetScaleChangeFlag(false);
									Number->SetScaleChangeFlag(false);
								}
							}

							m_StageNumber += 1;

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
						}
					}
				}
				/*else
				{
					onectrl = false;
				}*/

				/*if (m_StageNumber < 0) {
					m_StageNumber = 0;
				}
				else if (m_StageNumber > m_MaxStageNumber) {
					m_StageNumber = m_MaxStageNumber;
				}*/
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
		ScenePtr->SetStageNumber(m_StageNumber);
	}
}
