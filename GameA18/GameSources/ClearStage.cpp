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

		//AddGameObject<TitleSprite>(L"TITLE_TX", false,
		//	Vec2(1000.0f, 600.0f), Vec2(0.0f, 0.0f));
		AddGameObject<Sprite>(L"CLEAR_TX", false,
			Vec2(1280.0f, 800.0f), Vec3(0, 0.0f, 0.1f));
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
			Vec2(960, 600), Vec3(150.0, 60, 0.0f),3.0f);
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
				if (CntlVec[0].fThumbLX < -0.5f) {
					if (ThumbFlag) {
						NowSelect -= 1;//選択状態を右へ
						ThumbTimer = 0.0f;
						ThumbFlag = false;
					}
				}
				else if (CntlVec[0].fThumbLX > 0.5f) {
					if (ThumbFlag) {
						NowSelect += 1;//選択状態を左へ
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
				WLight->GetComponent<Action>()->Stop();
					WLight->GetComponent<Action>()->AllActionClear();
					WLight->GetComponent<Action>()->
						AddMoveTo(0.2f, Vec3(150.0, 60, 0.0f));
					WLight->GetComponent<Action>()->Run();
				break;
			case 1:
				WLight->GetComponent<Action>()->Stop();
					WLight->GetComponent<Action>()->AllActionClear();
					WLight->GetComponent<Action>()->
						AddMoveTo(0.2f, Vec3(-100.0, -230, 0.0f));
					WLight->GetComponent<Action>()->Run();
				break;
			case 2:
				WLight->GetComponent<Action>()->Stop();
					WLight->GetComponent<Action>()->AllActionClear();
					WLight->GetComponent<Action>()->
						AddMoveTo(0.2f, Vec3(420.0, -230, 0.0f));
					WLight->GetComponent<Action>()->Run();
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
