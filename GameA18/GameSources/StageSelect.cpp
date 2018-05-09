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
	auto PtrMultiLight = CreateLight<MultiLight>();
	//デフォルトのライティングを指定
	PtrMultiLight->SetDefaultLighting();

}

void StageSelect::CreateTitleSprite()
{
	//ステージへのゲームオブジェクトの追加
	auto Ptr = AddGameObject<GameObject>();
	auto PtrTrans = Ptr->GetComponent<Transform>();
	Quat Qt;
	Qt.rotationRollPitchYawFromVector(Vec3(0.60, 0, 0));
	PtrTrans->SetScale(5.0f, 4.0f, 1.0f);
	PtrTrans->SetQuaternion(Qt);
	PtrTrans->SetPosition(0.0f, -0.5f, 0.0f);

	auto ColPtr = Ptr->AddComponent<CollisionRect>();
	//描画コンポーネントの追加
	auto DrawComp = Ptr->AddComponent<BcPNTStaticDraw>();
	//描画コンポーネントに形状（メッシュ）を設定
	DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
	DrawComp->SetFogEnabled(true);
	//自分に影が映りこむようにする
	DrawComp->SetOwnShadowActive(true);

	//描画コンポーネントテクスチャの設定
	DrawComp->SetTextureResource(L"SELECT_TX");

}

void StageSelect::OnCreate()
{
	CreateViewLight();
	//スプライトの作成
	CreateTitleSprite();

}

//更新
void StageSelect::OnUpdate() {
	//コントローラの取得
	auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
	if (CntlVec[0].bConnected) {
		//Aボタン
		if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
		}
	}

}

}