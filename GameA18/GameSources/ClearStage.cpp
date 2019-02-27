#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void ClearStage::CreateViewLight()
	{
		auto PtrView = CreateView<SingleView>();
		//シャドウマップは使用しない
		SetShadowmapDraw(false);

	}

	//画像の配置
	void ClearStage::CreateTitleSprite(){
		AddGameObject<Sprite>(L"CLEAR_NoText_TX", true,
			Vec2(1280.0f, 800.0f), Vec3(0.0f, 0.0f, 0.1f));
		AddGameObject<Sprite>(L"CLEAR_STAGECLEAR_TX", true,
			Vec2(1280.0f, 800.0f), Vec3(200.0f, 300.0f, 0.0f));
		auto nextStage = AddGameObject<ScaleChangeSprite>(L"CLEAR_NEXTSTAGE_TX", true,
			Vec2(1600.0f, 1000.0f), Vec3(130.0f, 100.0f, 0.0f),3.0f,true);
		SetSharedGameObject(L"NextStage", nextStage);
		auto retry = AddGameObject<ScaleChangeSprite>(L"CLEAR_RETRY_TX", true,
			Vec2(1600.0f, 1000.0f), Vec3(40.0f, -70.0f, 0.0f),6.0f,false);
		SetSharedGameObject(L"Retry", retry);
		auto StageSelect = AddGameObject<ScaleChangeSprite>(L"CLEAR_STAGESELECT_TX", true,
			Vec2(1600.0f, 1000.0f), Vec3(210.0f, -250.0f, 0.0f),3.0f,false);
		SetSharedGameObject(L"StageSelect", StageSelect);
	}
	void ClearStage::CreateFadeOutSprite()
	{
		auto Fade = AddGameObject<SpriteFadeOut>(L"Shadow_TX", true,
			Vec2(50000 / 4, 30000 / 4), Vec3(0.0f, 600.0f, -0.0f));
		SetSharedGameObject(L"FadeOut", Fade);
	}

	void ClearStage::CreateFadeSprite()
	{
		auto Fade = AddGameObject<SpriteFade>(L"Shadow_TX", true,
			Vec2(840, 600), Vec3(900.0f, 0.0f, -0.0f));
		SetSharedGameObject(L"FadeIn", Fade);
	}

	void ClearStage::CreateUI() {
		//白い光
		auto WLight = AddGameObject<ScaleChangeSprite>(L"GameOver_WhiteLight_TX", true,
			Vec2(960, 600), Vec3(150.0, 60, 0.0f),3.0f,true);
		//白い光のアニメーション
		WLight->AddComponent<Action>();
		WLight->GetComponent<Action>()->AllActionClear();
		SetSharedGameObject(L"WLight", WLight);
	}

	void ClearStage::OnCreate()
	{
		NowSelect = 0;
		m_ScaleTimer = 0;
		m_ScaleFlag = true;

		ThumbFlag = true;
		CreateViewLight();

		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		//クリアしたステージを入れる
		Number = ScenePtr->GetStageNumber();

		if (Number == 12) {
			AddGameObject<Sprite>(L"CLEAR_Color_TX", true,
				Vec2(1280.0f, 800.0f), Vec3(0.0f, 0.0f, 0.1f));
		}
		else {
			//スプライトの作成
			CreateTitleSprite();
		}
		//CreateUI();
		CreateFadeOutSprite();
		CreateFadeSprite();
	}
	void ClearStage::Select() {
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		auto NextStage = GetSharedGameObject<ScaleChangeSprite>(L"NextStage");
		auto Retry = GetSharedGameObject<ScaleChangeSprite>(L"Retry");
		auto StageSelect = GetSharedGameObject<ScaleChangeSprite>(L"StageSelect");
		auto Time = App::GetApp()->GetElapsedTime();
		ThumbTimer += Time;
		m_ScaleTimer += Time;
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if ((CntlVec[0].wButtons&XINPUT_GAMEPAD_START) && (CntlVec[0].wButtons&XINPUT_GAMEPAD_BACK)) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleStage");
		}
		if (CntlVec[0].bConnected) {
			if (ThumbTimer > 0.5f) {
				ThumbFlag = true;
			}
			if (!SelectFlag) {//コントローラーの処理
				if (CntlVec[0].fThumbLY < -0.5f) {
					if (ThumbFlag) {
						NowSelect += 1;
						ThumbTimer = 0.0f;
						ThumbFlag = false;
					}
				}
				else if (CntlVec[0].fThumbLY > 0.5f) {
					if (ThumbFlag) {
						NowSelect += -1;
						ThumbTimer = 0.0f;
						ThumbFlag = false;
					}
				}
			}

			if (NowSelect < 0) {
				NowSelect = 2;
			}
			if (NowSelect > 2) {
				NowSelect = 0;
			}

			switch (NowSelect) {//現在選択中の状態によって処理を分岐
			case 0:
				NextStage->SetScaleChangeFlag(true);
				Retry->SetScaleChangeFlag(false);
				StageSelect->SetScaleChangeFlag(false);
				break;
			case 1:
				NextStage->SetScaleChangeFlag(false);
				Retry->SetScaleChangeFlag(true);
				StageSelect->SetScaleChangeFlag(false);
				break;
			case 2:
				NextStage->SetScaleChangeFlag(false);
				Retry->SetScaleChangeFlag(false);
				StageSelect->SetScaleChangeFlag(true);
				break;
			}

			//Aボタン
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A && !SelectFlag) {
				auto FadeIn = GetSharedGameObject<SpriteFade>(L"FadeIn");
				FadeIn->SetActionflag(true);
				SelectFlag = true;
				switch (NowSelect) {//現在選択中の状態によって処理を分岐
				case 0:
					ScenePtr->SetStageNumber(Number + 1);
					ScenePtr->SetRespawnFlag(false);
					PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
					break;
				case 1:
					ScenePtr->SetRespawnFlag(false);
					PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
					break;
				case 2:
					PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStageSelect");
					break;
				}
			}
		}
	}

	//更新
	void ClearStage::OnUpdate() {
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		if (Number == 12) {
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if ((CntlVec[0].wButtons&XINPUT_GAMEPAD_START) && (CntlVec[0].wButtons&XINPUT_GAMEPAD_BACK)) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleStage");
			}
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A && !SelectFlag) {
				auto FadeIn = GetSharedGameObject<SpriteFade>(L"FadeIn");
				FadeIn->SetActionflag(true);
				SelectFlag = true;
				ScenePtr->SetRespawnFlag(false);
				PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStageSelect");
			}
		}
		else {
			Select();
		}
	}
}
