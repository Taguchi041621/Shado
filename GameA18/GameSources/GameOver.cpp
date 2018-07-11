#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void GameOverStage::CreateViewLight()
	{
		auto PtrView = CreateView<SingleView>();
		//シャドウマップは使用しない
		SetShadowmapDraw(false);
	}

	void GameOverStage::CreateTitleSprite()
	{
		AddGameObject<Sprite>(L"GameOverMoji_TX", true,
			Vec2(1280.0f, 800.0f), Vec3(0.0f, 200.0f,0.1f));
		AddGameObject<Sprite>(L"GAMEOVER_TX", false,
			Vec2(1280.0f, 800.0f), Vec3(0.0f, 0.0f, 0.2f));
	}
	void GameOverStage::CreateFadeOutSprite()
	{
		auto Fade = AddGameObject<SpriteFadeOut>(L"Shadow_TX", true,
			Vec2(50000 / 4, 30000 / 4), Vec3(0.0f, 600.0f, 0.0f));
		SetSharedGameObject(L"FadeOut", Fade);

	}

	void GameOverStage::CreateFadeSprite()
	{
		auto Fade = AddGameObject<SpriteFade>(L"Shadow_TX", true,
			Vec2(840, 600), Vec3(900.0f, 0.0f, 0.0f));
		SetSharedGameObject(L"FadeIn", Fade);
	}
	//下のリトライとステージセレクトの文字、白い光の作成
	void GameOverStage::CreateUI() {
		//リトライ
		AddGameObject<Sprite>(L"RETRY_OFF_TX",true,
			Vec2(640,400),Vec3(-360,-300,0.2f));
		//ステージセレクト
		AddGameObject<Sprite>(L"STAGE_SELECT_OFF_TX", true,
			Vec2(640, 400), Vec3(270, -300, 0.2f));
		//白い光
		auto WLight = AddGameObject<ScaleChangeSprite>(L"GameOver_WhiteLight_TX",true,
			Vec2(960, 600), Vec3(-370.0, -300, 0.1f),3.0f,true);
		//白い光のアニメーション
		WLight->AddComponent<Action>();
		WLight->GetComponent<Action>()->AllActionClear();
		SetSharedGameObject(L"WLight", WLight);
	}

	void GameOverStage::OnCreate(){
		m_SelectFlag = false;
		m_SelectScene = -1.0f;
		CreateViewLight();
		//スプライトの作成
		CreateTitleSprite();
		CreateFadeOutSprite();
		CreateFadeSprite();
		CreateUI();
	}

	//更新
	void GameOverStage::OnUpdate() {
		auto WLight = GetSharedGameObject<ScaleChangeSprite>(L"WLight");
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			//左,リトライ
			if (CntlVec[0].fThumbLX <= -0.3f) {
				if (onectrl == false) {
					m_SelectScene = -1.0f;
					WLight->GetComponent<Action>()->AllActionClear();
					WLight->GetComponent<Action>()->
						AddMoveTo(0.3f, Vec3(-370.0f, -300.0f, 0.0f));
					onectrl = true;
				}
			}//右,ステージセレクト
			else if (CntlVec[0].fThumbLX >= 0.3f) {
				if (onectrl == false) {
					m_SelectScene = 1.0f;
					WLight->GetComponent<Action>()->AllActionClear();
					WLight->GetComponent<Action>()->
						AddMoveTo(0.3f, Vec3(270.0f, -300.0f, 0.0f));
					onectrl = true;
				}
			}
			else {
				if((m_SelectScene == -1.0f && WLight->GetComponent<Transform>()->GetPosition().x <= -100.0f)||
					(m_SelectScene == 1.0f && WLight->GetComponent<Transform>()->GetPosition().x >= 100.0f))
				onectrl = false;
			}

			WLight->GetComponent<Action>()->Run();

			//Aボタン
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A && !m_SelectFlag) {
				if (m_StopNowMusic != L""){
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
				if (m_SelectScene == -1.0f) {
					PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
				}
				if (m_SelectScene == 1.0f) {
					PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStageSelect");
				}
			}
		}
	}
}