#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void TitleStage::CreateViewLight()
	{
		auto PtrView = CreateView<SingleView>();
		//シャドウマップは使用しない
		SetShadowmapDraw(false);
	}

	void TitleStage::CreateTitleSprite()
	{
		AddGameObject<Sprite>(L"TITLE_TX", false,
			Vec2(1280.0f*1.8, 800.0f*1.8), Vec3(0, 50.0f, 0.1f));
		AddGameObject<ScaleChangeSprite>(L"TITLE_TEXT_TX", true,
			Vec2(960 * 0.8, 200 * 0.8), Vec3(0, -300, 0.1f), 0.5f, true);
		AddGameObject<Sprite>(L"TITLE_SHADOW_TX", true,
			Vec2(1280.0f*1.1, 800.0f*1.1), Vec3(0,0, 0.1f));
	}

	void TitleStage::CreateFadeSprite()
	{
		auto Fade = AddGameObject<SpriteFade>(L"Shadow_TX", true,
			Vec2(840, 600), Vec3(900.0f, 0.0f, 0.1f));
		SetSharedGameObject(L"Shadow_TX", Fade);

	}

	void TitleStage::CreateFadeOutSprite()
	{
		auto Fade = AddGameObject<SpriteFadeOut>(L"Shadow_TX", true,
			Vec2(50000 / 4, 30000 / 4), Vec3(0.0f, 0.0f, 0.0f));
		SetSharedGameObject(L"FadeOut", Fade);

	}

	void TitleStage::OnCreate()
	{
		m_SelectFlag = false;

		CreateViewLight();
		//スプライトの作成
		CreateTitleSprite();
		CreateFadeSprite();
		CreateFadeOutSprite();
	}

	//更新
	void TitleStage::OnUpdate() {
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			//Aボタン
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A&&!m_SelectFlag) {
				if (m_StopNowMusic != L""){
					m_AudioObjectPtr->Stop(m_StopNowMusic);
				}

				m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
				m_AudioObjectPtr->AddAudioResource(L"se");
				m_AudioObjectPtr->Start(L"se", XAUDIO2_NO_LOOP_REGION, 0.1f);
			    SetNowMusic(L"se");
				

				auto Fade = GetSharedGameObject<SpriteFade>(L"Shadow_TX");
				Fade->SetActionflag(true);
				PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStageSelect");
				m_SelectFlag = true;
			}
		}
	}

}