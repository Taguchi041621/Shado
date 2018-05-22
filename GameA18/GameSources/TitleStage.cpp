#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void TitleStage::CreateViewLight()
	{
		//auto PtrView = CreateView<SingleView>();
		////ビューのカメラの設定
		//auto PtrCamera = ObjectFactory::Create<Camera>();
		//PtrView->SetCamera(PtrCamera);
		//PtrCamera->SetEye(Vec3(0.0f, 2.0f, -4.0f));
		//PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		////マルチライトの作成
		//auto PtrMultiLight = CreateLight<MultiLight>();
		////デフォルトのライティングを指定
		//PtrMultiLight->SetDefaultLighting();
		auto PtrView = CreateView<SingleView>();
		//シャドウマップは使用しない
		SetShadowmapDraw(false);
	}

	void TitleStage::CreateTitleSprite()
	{
		////ステージへのゲームオブジェクトの追加
		//auto Ptr = AddGameObject<GameObject>();
		//auto PtrTrans = Ptr->GetComponent<Transform>();
		//Quat Qt;
		//Qt.rotationRollPitchYawFromVector(Vec3(0.75, 0, 0));
		//PtrTrans->SetScale(7.0f, 6.0f, 1.0f);
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
		//DrawComp->SetTextureResource(L"TITLE_TX");

		//AddGameObject<TitleSprite>(L"TITLE_TX", false,
		//	Vec2(1000.0f, 600.0f), Vec2(0.0f, 0.0f));
		AddGameObject<Sprite>(L"TITLE_TX", false,
			Vec2(1280.0f, 800.0f), Vec3(0, 0.0f, 0.1f));
	}

	void TitleStage::CreateFadeSprite()
	{
		auto Fade = AddGameObject<SpriteFade>(L"Shadow_TX", true,
			Vec2(840, 600), Vec3(900.0f, 0.0f, 0.1f));
		SetSharedGameObject(L"Shadow_TX", Fade);

	}

	void TitleStage::OnCreate()
	{
		m_SelectFlag = false;
		CreateViewLight();
		//スプライトの作成
		CreateTitleSprite();
		CreateFadeSprite();

	}

	//更新
	void TitleStage::OnUpdate() {
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			//Aボタン
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A&&!m_SelectFlag) {
				auto Fade = GetSharedGameObject<SpriteFade>(L"Shadow_TX");
				Fade->SetActionflag(true);
				PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStageSelect");
				m_SelectFlag = true;
			}
		}
	}

}