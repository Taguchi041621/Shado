#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void ClearStage::CreateViewLight()
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

	void ClearStage::CreateTitleSprite()
	{
		////ステージへのゲームオブジェクトの追加
		//auto Ptr = AddGameObject<GameObject>();
		//auto PtrTrans = Ptr->GetComponent<Transform>();
		//Quat Qt;
		//Qt.rotationRollPitchYawFromVector(Vec3(0.65, 0, 0));
		//PtrTrans->SetScale(6.0f, 5.0f, 1.0f);
		//PtrTrans->SetQuaternion(Qt);
		//PtrTrans->SetPosition(0.0f, 0.0f, 0.0f);

		//auto ColPtr = Ptr->AddComponent<CollisionRect>();
		////描画コンポーネントの追加
		//auto DrawComp = Ptr->AddComponent<BcPNTStaticDraw>();
		////描画コンポーネントに形状（メッシュ）を設定
		//DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		//DrawComp->SetFogEnabled(true);
		////自分に影が映りこむようにする
		//DrawComp->SetOwnShadowActive(true);

		////描画コンポーネントテクスチャの設定
		//DrawComp->SetTextureResource(L"CLEAR_TX");

		AddGameObject<Sprite>(L"CLEAR_ColorNoText_TX", true,
			Vec2(1280.0f, 800.0f), Vec3(0.0f, 0.0f, 0.1f));
		AddGameObject<Sprite>(L"CLEAR_STAGECLEAR_TX", true,
			Vec2(1280.0f, 800.0f), Vec3(200.0f, 300.0f, 0.0f));
		auto nextStage = AddGameObject<ScaleChangeSprite>(L"CLEAR_NEXTSTAGE_TX", true,
			Vec2(1600.0f, 1000.0f), Vec3(150.0f, 100.0f, 0.0f),3,true);
		SetSharedGameObject(L"NextStage", nextStage);
		auto retry = AddGameObject<ScaleChangeSprite>(L"CLEAR_RETRY_TX", true,
			Vec2(1600.0f, 1000.0f), Vec3(225.0f, -50.0f, 0.0f),3,false);
		SetSharedGameObject(L"Retry", retry);
		auto StageSelect = AddGameObject<ScaleChangeSprite>(L"CLEAR_STAGESELECT_TX", true,
			Vec2(1600.0f, 1000.0f), Vec3(300.0f, -250.0f, 0.0f),3,false);
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

		//スプライトの作成
		CreateTitleSprite();
		CreateUI();
		CreateFadeOutSprite();
		CreateFadeSprite();

	}

	//更新
	void ClearStage::OnUpdate() {
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		auto WLight = GetSharedGameObject<ScaleChangeSprite>(L"WLight");
		auto NextStage = GetSharedGameObject<ScaleChangeSprite>(L"NextStage");
		auto Retry = GetSharedGameObject<ScaleChangeSprite>(L"Retry");
		auto StageSelect = GetSharedGameObject<ScaleChangeSprite>(L"StageSelect");
		auto Time = App::GetApp()->GetElapsedTime();
		ThumbTimer += Time;
		m_ScaleTimer += Time;
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
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
				//WLight->GetComponent<Action>()->Stop();
				//	WLight->GetComponent<Action>()->AllActionClear();
				//	WLight->GetComponent<Action>()->
				//		AddMoveTo(0.2f, Vec3(150.0, 60, 0.0f));
				//	WLight->GetComponent<Action>()->Run();
				NextStage->SetScaleChangeFlag(true);
				Retry->SetScaleChangeFlag(false);
				StageSelect->SetScaleChangeFlag(false);
				break;
			case 1:
				//WLight->GetComponent<Action>()->Stop();
				//	WLight->GetComponent<Action>()->AllActionClear();
				//	WLight->GetComponent<Action>()->
				//		AddMoveTo(0.2f, Vec3(-100.0, -230, 0.0f));
				//	WLight->GetComponent<Action>()->Run();
					NextStage->SetScaleChangeFlag(false);
					Retry->SetScaleChangeFlag(true);
					StageSelect->SetScaleChangeFlag(false);
				break;
			case 2:
				//WLight->GetComponent<Action>()->Stop();
				//	WLight->GetComponent<Action>()->AllActionClear();
				//	WLight->GetComponent<Action>()->
				//		AddMoveTo(0.2f, Vec3(420.0, -230, 0.0f));
				//	WLight->GetComponent<Action>()->Run();
				NextStage->SetScaleChangeFlag(false);
				Retry->SetScaleChangeFlag(false);
				StageSelect->SetScaleChangeFlag(true);
				break;
			}

			//Aボタン
			auto Number = ScenePtr->GetStageNumber();
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
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
}
