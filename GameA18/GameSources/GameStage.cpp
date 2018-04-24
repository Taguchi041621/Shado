/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------

	//ビューとライトの作成
	void GameStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrLookAtCamera = ObjectFactory::Create<MyCamera>(GetThis<GameStage>());
		PtrView->SetCamera(PtrLookAtCamera);
		PtrLookAtCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		PtrLookAtCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
		auto meinLight = PtrMultiLight->GetMainIndex();
		//影を出すライトの初期角度を設定
		PtrMultiLight->GetLight(meinLight).SetPositionToDirectional(0.00f, 0.00f, -0.1f);
	}


	//プレートの作成
	void GameStage::CreatePlate() {
		//ステージへのゲームオブジェクトの追加
		auto Ptr = AddGameObject<GameObject>();
		auto PtrTrans = Ptr->GetComponent<Transform>();
		Quat Qt;
		Qt.rotationRollPitchYawFromVector(Vec3(XM_PIDIV2, 0, 0));
		PtrTrans->SetScale(50.0f, 50.0f, 0.1f);
		PtrTrans->SetQuaternion(Qt);
		PtrTrans->SetPosition(0.0f, 0.0f, 0.0f);

		auto ColPtr = Ptr->AddComponent<CollisionRect>();
		//描画コンポーネントの追加
		auto DrawComp = Ptr->AddComponent<BcPNTStaticDraw>();
		//描画コンポーネントに形状（メッシュ）を設定
		DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		DrawComp->SetFogEnabled(true);
		//自分に影が映りこむようにする
		DrawComp->SetOwnShadowActive(true);

		//描画コンポーネントテクスチャの設定
		DrawComp->SetTextureResource(L"SKY_TX");
	}
	void GameStage::CreateWall() {
		//ステージへのゲームオブジェクトの追加
		auto Ptr = AddGameObject<GameObject>();
		auto PtrTrans = Ptr->GetComponent<Transform>();
		Quat Qt;
		Qt.rotationRollPitchYawFromVector(Vec3(0, 0, XM_PIDIV2));
		PtrTrans->SetScale(50.0f, 50.0f, 1.0f);
		PtrTrans->SetQuaternion(Qt);
		PtrTrans->SetPosition(0.0f, 0.0f, 0.0f);

		auto ColPtr = Ptr->AddComponent<CollisionRect>();
		//描画コンポーネントの追加
		auto DrawComp = Ptr->AddComponent<BcPNTStaticDraw>();
		//描画コンポーネントに形状（メッシュ）を設定
		DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		DrawComp->SetFogEnabled(true);
		//自分に影が映りこむようにする
		DrawComp->SetOwnShadowActive(true);

		Flt4 Color(1.0f, 1.0f, 1.0f, 0.7f);
		DrawComp->SetColorAndAlpha(Color);
	}

	//プレイヤーの作成
	void GameStage::CreatePlayer() {
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		//プレーヤーの作成
		auto PlayerPtr = AddGameObject<Player>(DataDir+L"Idea\\");
		//シェア配列にプレイヤーを追加
		SetSharedGameObject(L"Player", PlayerPtr);
	}

	void GameStage::CreateWhiteCube() {
		Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
		auto CubePtr = AddGameObject<WhiteCube>(
			Vec3(3.0f, 1.0f, 1.0f),
			Qt,
			Vec3(-7.0f, 4.0f, -10.0f)
			);
		CubePtr = AddGameObject<WhiteCube>(
			Vec3(2.0f, 1.0f, 1.0f),
			Qt,
			Vec3(-2.0f, 3.0f, -6.0f)
			);
		CubePtr = AddGameObject<WhiteCube>(
			Vec3(3.0f, 1.0f, 1.0f),
			Qt,
			Vec3(3.0f, 2.0f, -8.0f)
			);

		//SetSharedGameObject(L"WhiteCube", CubePtr);
	}

	void GameStage::CreateGoal() {
		Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
		auto CubePtr = AddGameObject<Goal>(
			Vec3(0.25f, 0.5f, 0.25f),		//スケール
			Qt,							//角度
			Vec3(5.0f, 2.8f, -0.25f)		//ポジション
			);
	}

	void GameStage::CreateKeyItem()
	{
		auto KeyPtr = AddGameObject<KeyItem>(Vec3(1.0f, 4.0f, -0.25f));
	}
	//ステージをスイッチ文で切り替える
	void GameStage::CreateStage(int num) {
		Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
		switch (num){
		case 1:
			//実体ブロック
			AddGameObject<WhiteCube>(
				Vec3(3.0f, 1.0f, 1.0f),Qt,
				Vec3(-7.0f, 4.0f, -10.0f)
				);
			AddGameObject<WhiteCube>(
				Vec3(2.0f, 1.0f, 1.0f),Qt,
				Vec3(-2.0f, 3.0f, -6.0f)
				);
			AddGameObject<WhiteCube>(
				Vec3(3.0f, 1.0f, 1.0f),Qt,
				Vec3(3.0f, 2.0f, -8.0f)
				);

			//ゴール
			AddGameObject<Goal>(
				Vec3(0.25f, 0.5f, 0.25f),		//スケール
				Qt,							//角度
				Vec3(5.0f, 2.8f, -0.25f)		//ポジション
				);
			//キー
			AddGameObject<KeyItem>(Vec3(1.0f, 4.0f, -0.25f));
			//三角
			AddGameObject<Triangle>(
				Vec3(1.0f, 1.0f, 1.0f), Qt,
				Vec3(3.0f, 4.0f, -6.0f)
				);
			break;
		default:
			break;
		}
	}

	void GameStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			//プレートの作成
			//CreatePlate();
			//壁
			CreateWall();
			//プレーヤーの作成
			CreatePlayer();
			////白いブロックの作成
			//CreateWhiteCube();
			////ゴールブロック
			//CreateGoal();
			////鍵
			//CreateKeyItem();
			CreateStage(1);
		}
		catch (...) {
			throw;
		}
	}
	//更新
	void GameStage::OnUpdate() {
		////コントローラの取得
		//auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//if (CntlVec[0].bConnected) {
		//	//Aボタン
		//	if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
		//		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
		//	}
		//}
	}
	//end basecross
}