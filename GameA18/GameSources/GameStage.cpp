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

	//CSV,ステージの作成
	void GameStage::Csv()
	{
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		// CSVファイルの決定,
		//-------------------------------------------------
		//ディレクトリパス
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);

		//ファイル名の設定
		//wstring Map = Path + L"Stage_" + Util::IntToWStr(ScenePtr->GetStageNumber()) + L".csv";
		wstring Map = DataDir + L"Stage_0.csv";

		//ファイルの指定
		m_Csv.SetFileName(Map);

		if (!m_Csv.ReadCsv()){
			//ファイルが存在しなかったとき
			throw BaseException(
				L"ファイルが見つかりませんでした",
				Map,
				L"パスが間違っているorファイルが存在しない\nさっさと確認してやり直せ"
			);
		}
		else {
			//CSVファイルが存在したときにフラグをtrueにする
			dataIdFlag = true;
		}

		//Csvを読み込んでくる----------
		int RowNum = 1;//行番号
					   //行を記憶させるための配列
		vector<wstring>MapVec;
		//最初の行を配列へ保存
		m_Csv.GetRowVec(RowNum, MapVec);

		//角度のラジアン変換用
		//float DegToRad = 3.14159265f / 180.0f;

		int Wcount = 0;
		//最後まで読み込む
		while (MapVec[0] != L"end"){
			//文字列があったかを判断
			bool stringflag = false;
			//ポジション、ローテーション、スケール
			//オブジェクトをそれぞれ生成する
			//TransformのCsvファイル列番号対応
			//--------------------
			//1:PosX 2:PosY 3:PosZ
			//4:RotX 5:RotY 6:RotZ 
			//7:SclX 8:SclY 9:SclZ
			//--------------------
			//_wtof(文字列を数値として読み取る)
			//ポジションを格納
			Vec3 Pos = Vec3((float)_wtof(MapVec[1].c_str()), (float)_wtof(MapVec[2].c_str()), (float)_wtof(MapVec[3].c_str())-1.0f);
			//ローテーションを格納(この時にラジアンに変換)
			Vec3 Rot = Vec3((float)_wtof(MapVec[4].c_str()), (float)_wtof(MapVec[5].c_str()), (float)_wtof(MapVec[6].c_str()))*DegToRad;
			//スケールを格納
			Vec3 Scl = Vec3((float)_wtof(MapVec[7].c_str()), (float)_wtof(MapVec[8].c_str()), (float)_wtof(MapVec[9].c_str()));
			//auto UpGroup = GetSharedObjectGroup(L"UpdateObjectGroup");

			if (MapVec[0] == L"Cube"){
				//FixedBox(const Vector3& Scale,const Vector3& Rotation,const Vector3& Position
				//それぞれの値を入れる
				//固定する値を設定
				stringflag = true;
				//Scl = Vector3(1, 1, 1);
				//Rot = Vector3(0, 0, 0);
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				auto PtrCube = AddGameObject<WhiteCube>(Scl, Qt, Pos);
			}

			if (MapVec[0] == L"Player"){
				stringflag = true;
				wstring DataDir;
				App::GetApp()->GetDataDirectory(DataDir);
				//プレーヤーの作成
				auto PlayerPtr = AddGameObject<Player>(DataDir + L"Idea\\");
				//シェア配列にプレイヤーを追加
				SetSharedGameObject(L"Player", PlayerPtr);
				Pos.z = 0.0f;
				PlayerPtr->GetComponent<Transform>()->SetPosition(Pos);
			}

			if (MapVec[0] == L"Goal"){
				stringflag = true;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				auto CubePtr = AddGameObject<Goal>(
					Vec3(0.25f, 0.5f, 0.25f),//スケール
					Qt,					//角度
					Pos					//ポジション
					);
			}
			if (MapVec[0] == L"Key"){
				stringflag = true;
				Pos.z = 0.0f;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				AddGameObject<KeyItem>(Pos);
			}
			if (!stringflag){
				throw BaseException(
					Util::IntToWStr(RowNum + 1) + L"行目",
					MapVec[0].c_str(),
					L"使用不可のオブジェクトです"
				);
			}
			//行データ更新
			RowNum++;
			m_Csv.GetRowVec(RowNum, MapVec);

		}

	}


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
		//ライトの処理をするオブジェ
		auto ptrMyLight = AddGameObject<LightController>();
		SetSharedGameObject(L"LightController", ptrMyLight);
	}

	void GameStage::CreateWall() {
		//ステージへのゲームオブジェクトの追加
		auto Ptr = AddGameObject<GameObject>();
		auto PtrTrans = Ptr->GetComponent<Transform>();
		Quat Qt;
		Qt.rotationRollPitchYawFromVector(Vec3(0, 0, XM_PIDIV2));
		PtrTrans->SetScale(80.0f, 80.0f, 1.0f);
		PtrTrans->SetQuaternion(Qt);
		PtrTrans->SetPosition(0.0f, 0.0f, 0.0f);

		
		//auto ColPtr = Ptr->AddComponent<CollisionRect>();
		//描画コンポーネントの追加
		auto DrawComp = Ptr->AddComponent<BcPNTStaticDraw>();
		//描画コンポーネントに形状（メッシュ）を設定
		DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		DrawComp->SetFogEnabled(true);
		//自分に影が映りこむようにする
		DrawComp->SetOwnShadowActive(true);
		DrawComp->SetTextureResource(L"WallTexture_TX");
		

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

	void GameStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			//壁
			CreateWall();
			//プレーヤーの作成
			//CreatePlayer();
			////白いブロックの作成
			//CreateWhiteCube();
			////ゴールブロック
			//CreateGoal();
			CreateSharedObjectGroup(L"KeyGroup");

			Csv();
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