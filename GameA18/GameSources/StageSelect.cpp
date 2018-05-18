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
}

void StageSelect::CreateFadeOutSprite()
{
	auto Fade = AddGameObject<SpriteFadeOut>(L"Shadow_TX", true,
		Vec2(50000/4, 30000/4), Vec3(0.0f, 0.0f, 0.1f));
	SetSharedGameObject(L"FadeOut", Fade);

}

void StageSelect::CreateFadeSprite()
{
	auto Fade = AddGameObject<SpriteFade>(L"Shadow_TX", true,
		Vec2(840, 600), Vec3(900.0f, 0.0f, 0.1f));
	SetSharedGameObject(L"FadeIn", Fade);

}
void StageSelect::StageNumberSprite()
{
	auto Zero = AddGameObject<Sprite>(L"0_TX", false,
		Vec2(200.0f, 200.0f), Vec3(-500, 0.0f, 0.1f));
	SetSharedGameObject(L"0", Zero);
	auto One = AddGameObject<Sprite>(L"1_TX", false,
		Vec2(200.0f, 200.0f), Vec3(-200, 0.0f, 0.1f));
	SetSharedGameObject(L"1", One);
	auto Two = AddGameObject<Sprite>(L"2_TX", false,
		Vec2(200.0f, 200.0f), Vec3(100, 0.0f, 0.1f));
	SetSharedGameObject(L"2", Two);
	auto Three = AddGameObject<Sprite>(L"3_TX", false,
		Vec2(200.0f, 200.0f), Vec3(400, 0.0f, 0.1f));
	SetSharedGameObject(L"3", Three);
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
	//コントローラの取得
	auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
	if(m_SelectFlag){
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].fThumbLX < -0.5) {
				if (onectrl == false)
				{
					onectrl = true;
					m_StageNumber += -1;
				}
			}
			else if (CntlVec[0].fThumbLX > 0.5) {
				if (onectrl == false)
				{
					onectrl = true;
					m_StageNumber += 1;
				}
			}
			else
			{
				onectrl = false;
			}

			if (m_StageNumber < 0) {
				m_StageNumber = 3;
			}
			else if (m_StageNumber > 3) {
				m_StageNumber = 0;
			}
			//Aボタン
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				auto FadeIn = GetSharedGameObject<SpriteFade>(L"FadeIn");
				FadeIn->SetActionflag(true);
				m_SelectFlag = false;
				PostEvent(2.4f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
			}
		}
	}

	auto Zero = GetSharedGameObject<Sprite>(L"0");
	auto One = GetSharedGameObject<Sprite>(L"1");
	auto Two = GetSharedGameObject<Sprite>(L"2");
	auto Three = GetSharedGameObject<Sprite>(L"3");
	auto ScenePtr = App::GetApp()->GetScene<Scene>();
	switch (m_StageNumber) {
		
	case 0:
		Zero->SetActionflag(true);
		One->SetActionflag(false);
		Two->SetActionflag(false);
		Three->SetActionflag(false);
		ScenePtr->SetStageNumber(m_StageNumber);
		break;
	case 1:
		Zero->SetActionflag(false);
		One->SetActionflag(true);
		Two->SetActionflag(false);
		Three->SetActionflag(false);
		ScenePtr->SetStageNumber(m_StageNumber);
		break;
	case 2:
		Zero->SetActionflag(false);
		One->SetActionflag(false);
		Two->SetActionflag(true);
		Three->SetActionflag(false);
		ScenePtr->SetStageNumber(m_StageNumber);
		break;
	case 3:
		Zero->SetActionflag(false);
		One->SetActionflag(false);
		Two->SetActionflag(false);
		Three->SetActionflag(true);
		ScenePtr->SetStageNumber(m_StageNumber);
		break;
	}
	

}

}