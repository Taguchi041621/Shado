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
		wstring Map = DataDir + L"CSV\\" + L"Stage_" + Util::IntToWStr(ScenePtr->GetStageNumber()) + L".csv";

		//ファイルの指定
		m_Csv.SetFileName(Map);

		if (!m_Csv.ReadCsv()) {
			//ファイルが存在しなかったとき
			throw BaseException(
				L"ファイルが見つかりませんでした",
				Map,
				L"パスが間違っているorファイルが存在しない\n"
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
		while (MapVec[0] != L"end") {
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
			Vec3 Pos = Vec3((float)_wtof(MapVec[1].c_str()), (float)_wtof(MapVec[2].c_str()), (float)_wtof(MapVec[3].c_str()) - 1.0f);
			//ローテーションを格納(この時にラジアンに変換)
			Vec3 Rot = Vec3((float)_wtof(MapVec[4].c_str()), (float)_wtof(MapVec[5].c_str()), (float)_wtof(MapVec[6].c_str()))*DegToRad;
			//スケールを格納
			Vec3 Scl = Vec3((float)_wtof(MapVec[7].c_str()), (float)_wtof(MapVec[8].c_str()), (float)_wtof(MapVec[9].c_str()));
			//auto UpGroup = GetSharedObjectGroup(L"UpdateObjectGroup");

			if (MapVec[0] == L"Cube") {
				//FixedBox(const Vector3& Scale,const Vector3& Rotation,const Vector3& Position
				//それぞれの値を入れる
				//固定する値を設定
				stringflag = true;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				auto PtrCube = AddGameObject<RedCube>(Scl, Qt, Pos,Vec3(0,0,0),false);
			}

			if (MapVec[0] == L"MoveCube") {
				//FixedBox(const Vector3& Scale,const Vector3& Rotation,const Vector3& Position
				//それぞれの値を入れる
				//固定する値を設定
				stringflag = true;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				auto PtrCube = AddGameObject<BlueCube>(Scl, Qt, Pos, Vec3(1,0,0), true);
			}
			if (MapVec[0] == L"CustomMoveCube") {
				//それぞれの値を入れる
				stringflag = true;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				//移動幅を取ってくる
				float MoveX = (float)_wtof(MapVec[10].c_str());
				auto PtrCube = AddGameObject<BlueCube>(Scl, Qt, Pos, Vec3(MoveX, 0, 0), true);
			}
			if (MapVec[0] == L"VMoveCube") {
				//FixedBox(const Vector3& Scale,const Vector3& Rotation,const Vector3& Position
				//それぞれの値を入れる
				//固定する値を設定
				stringflag = true;
				//Scl = Vector3(1, 1, 1);
				//Rot = Vector3(0, 0, 0);
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				auto PtrCube = AddGameObject<YellowCube>(Scl, Qt, Pos, Vec3(0, 1, 0), true);
			}
			if (MapVec[0] == L"CustomVMoveCube") {
				//それぞれの値を入れる
				stringflag = true;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				//移動幅を取ってくる
				float MoveY = (float)_wtof(MapVec[10].c_str());
				auto PtrCube = AddGameObject<YellowCube>(Scl, Qt, Pos, Vec3(0,MoveY, 0), true);
			}
			if (MapVec[0] == L"Player") {
				stringflag = true;
				//z位置を固定
				Pos.z = -0.1f;
				//メディア呼び出し
				wstring DataDir;
				App::GetApp()->GetDataDirectory(DataDir);
				//プレーヤーの作成
				auto PlayerPtr = AddGameObject<Player>(DataDir + L"Idea\\",Pos);
				//シェア配列にプレイヤーを追加
				SetSharedGameObject(L"Player", PlayerPtr);

			}

			if (MapVec[0] == L"Tutorial") {
				stringflag = true;
				wstring DataDir;
				App::GetApp()->GetDataDirectory(DataDir);
				if (ScenePtr->GetStageNumber() == 1) {
					AddGameObject<Tutorial>(
						DataDir + L"Tutorial\\",
						Vec3(1),
						Vec3(0),
						Vec3(Pos + Vec3(3, 3,1.5)),
						L"R_stick"
						);

					AddGameObject<Sprite3D>(
						Vec3(10, 5, 0),
						Vec3(0),
						Vec3(Pos + Vec3(3, 5.3, 1.5)),
						L"TUTORIAL_LIGHT_MOVE_TX"
						);

					AddGameObject<Tutorial>(
						DataDir + L"Tutorial\\",
						Vec3(1),
						Vec3(0),
						Vec3(Pos + Vec3(-3, 3,1.5)),
						L"L_stick"
						);
					AddGameObject<Sprite3D>(
						Vec3(10, 5, 0),
						Vec3(0),
						Vec3(Pos + Vec3(-3, 5.3, 1.5)),
						L"TUTORIAL_CHARA_MOVE_TX"
						);
				}

				if (ScenePtr->GetStageNumber() == 2) {
					AddGameObject<Tutorial>(
						DataDir + L"Tutorial\\",
						Vec3(1),
						Vec3(0),
						Vec3(Pos + Vec3(3, 3, 1.5)),
						L"L_R"
						);

					AddGameObject<Sprite3D>(
						Vec3(10, 5, 0),
						Vec3(0),
						Vec3(Pos + Vec3(3, 5.3, 1.5)),
						L"TUTORIAL_LIGHT_MOVE_TX"
						);
				}
			}

			if (MapVec[0] == L"Goal") {
				stringflag = true;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				auto CubePtr = AddGameObject<Goal>(Vec3(0.25f, 0.5f, 0.25f),Qt,Pos);
			}
			if (MapVec[0] == L"Key") {
				stringflag = true;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				AddGameObject<KeyItem>(Pos);
			}

			if (MapVec[0] == L"Cannon") {
				//それぞれの値を入れる
				//固定する値を設定
				stringflag = true;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				AddGameObject<CannonBase>(Scl, Qt, Pos,CannonBase::CanonDirection::LEFT);
			}
			if (MapVec[0] == L"CannonR") {
				//それぞれの値を入れる
				//固定する値を設定
				stringflag = true;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				AddGameObject<CannonBase>(Scl, Qt, Pos,CannonBase::CanonDirection::RIGTH);
			}

			if (!stringflag) {
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

	void GameStage::CreateFadeOutSprite()
	{
		auto Fade = AddGameObject<SpriteFadeOut>(L"Shadow_TX", true,
			Vec2(50000 / 4, 30000 / 4), Vec3(0.0f, 0.0f, 0.1f));
		SetSharedGameObject(L"FadeOut", Fade);
	}

	void GameStage::CreateFadeSprite()
	{
		auto Fade = AddGameObject<SpriteFade>(L"Shadow_TX", true,
			Vec2(840, 600), Vec3(900.0f, 0.0f, 0.1f));
		SetSharedGameObject(L"FadeIn", Fade);
	}

	void GameStage::CreatePause() {
		auto Pause = AddGameObject<Sprite>(L"PAUSE_TX", true,
			Vec2(800 * 2, 450 * 2), Vec3(0, -50.0f, 0.2f));
		SetSharedGameObject(L"Pause", Pause);
		Pause->SetDrawActive(false);
		auto WLight = AddGameObject<ScaleChangeSprite>(L"GameOver_WhiteLight_TX", true,
			Vec2(1000, 600), Vec3(-20, 130, 0.1f), 0.3f,true);
		WLight->SetDrawActive(false);

		//白い光のアニメーション
		WLight->AddComponent<Action>();
		WLight->GetComponent<Action>()->AllActionClear();
		SetSharedGameObject(L"WLight", WLight);
	}

	//ビューとライトの作成
	void GameStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrLookAtCamera = ObjectFactory::Create<MyCamera>(GetThis<GameStage>());
		PtrView->SetCamera(PtrLookAtCamera);
		//PtrLookAtCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
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
		//壁、影があるほう
		auto Ptr = AddGameObject<GameObject>();
		auto PtrTrans = Ptr->GetComponent<Transform>();
		Quat Qt;
		Qt.rotationRollPitchYawFromVector(Vec3(0, 0, XM_PIDIV2));
		PtrTrans->SetScale(100.0f, 100.0f, 1.0f);
		PtrTrans->SetQuaternion(Qt);
		PtrTrans->SetWorldPosition(Vec3(0.0f, 0.0f, 0.5f));

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

	//画面内を動き回っているライトイラスト
	void GameStage::CreateLightSign() {
		AddGameObject<LightSign>();
	}
	//画面端のやつ
	void GameStage::CreateMoveEnd() {
		auto frame = AddGameObject<Sprite>(L"Shadowframe_TX", true, Vec2(1330.0f, 870.0f), Vec3(0.3f, 0.0f, 0));
		frame->GetComponent<Action>()->AllActionClear();
		frame->SetActionflag(true);
	}
	
	//ライト代わりのオブジェクト
	void GameStage::CreateLightObject() {
		auto PtrLight = AddGameObject<StageLight>(
			Vec3(0.0f, 0.0, -35.0f),
			Vec3(1.5f, 0.0f, 0.0f),
			Vec3(5.0f, 1.0f, 5.0f));
	}

	void GameStage::OnCreate() {
		m_ClearFlag = false;
		NowSelect = 0;
		try {
			//ビューとライトの作成
			CreateViewLight();
			//壁
			CreateWall();
			//クリエイトした鍵のグループ
			CreateSharedObjectGroup(L"KeyGroup");
			//ライトの位置を知らせる演出
			CreateLightSign();
			//ライトの駆動限界を教える
			CreateMoveEnd();
			//ライト代わりのオブジェクト
			CreateLightObject();
			Csv();
			CreatePause();
			//フェード
			CreateFadeOutSprite();
			CreateFadeSprite();
			auto Target = AddGameObject<TargetObjectToStart>();
			dynamic_pointer_cast<MyCamera>(GetView()->GetTargetCamera())->SetTargetObject(Target);
		}
		catch (...) {
			throw;
		}
	}
	//更新
	void GameStage::OnUpdate() {
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		auto Fade = GetSharedGameObject<SpriteFade>(L"FadeIn");
		auto PtrPlayer = GetSharedGameObject<Player>(L"Player");

		auto Pause = GetSharedGameObject<Sprite>(L"Pause");
		auto WLight = GetSharedGameObject<ScaleChangeSprite>(L"WLight");

		auto Time = App::GetApp()->GetElapsedTime();
		ThumbTimer += Time;
		m_ScaleTimer += Time;
		//死んだとき
		if (PtrPlayer->GetGameOverFlag() && PtrPlayer->GetFadeFlag() && !m_ClearFlag) {
			Fade->SetActionflag(true);
			//リスポーン
			ScenePtr->SetRespawnFlag(true);
			PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
			m_ClearFlag = true;
		}
		//クリアしたとき
		if (PtrPlayer->GetGameClearFlag() && PtrPlayer->GetFadeFlag() && !m_ClearFlag) {
			Fade->SetActionflag(true);
			PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
			m_ClearFlag = true;
		}

		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if ((CntlVec[0].wButtons&XINPUT_GAMEPAD_START) && (CntlVec[0].wButtons&XINPUT_GAMEPAD_BACK)) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleStage");
		}
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START && !ScenePtr->GetPauseFlag() && !PtrPlayer->GetGameClearFlag() && ScenePtr->GetStartFlag()) {
				PtrPlayer->SetUpdateActive(false);
				ScenePtr->SetPauseFlag(true);
				Pause->SetDrawActive(true);
				WLight->SetDrawActive(true);
			}
			else	if ((CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
				&& ScenePtr->GetPauseFlag()) {
				PtrPlayer->SetUpdateActive(true);
				ScenePtr->SetPauseFlag(false);

				Pause->SetDrawActive(false);
				WLight->SetDrawActive(false);
			}
		}


		if (ScenePtr->GetPauseFlag()) {
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
						NowSelect -= 1;
						ThumbTimer = 0.0f;
						ThumbFlag = false;
					}
				}
				//上下端を超えたら反対側の端に行く
				if (NowSelect < 0) {
					NowSelect = 2;
				}
				if (NowSelect > 2) {
					NowSelect = 0;
				}
			}

			switch (NowSelect) {//現在選択中の状態によって処理を分岐
			case 0:
				WLight->GetComponent<Action>()->Stop();
				WLight->GetComponent<Action>()->AllActionClear();
				WLight->GetComponent<Action>()->
					AddMoveTo(0.2f, Vec3(-20, 130, 0.1f));
				WLight->GetComponent<Action>()->Run();
				break;
			case 1:
				WLight->GetComponent<Action>()->Stop();
				WLight->GetComponent<Action>()->AllActionClear();
				WLight->GetComponent<Action>()->
					AddMoveTo(0.2f, Vec3(-20, -30, 0.1f));
				WLight->GetComponent<Action>()->Run();
				break;
			case 2:
				WLight->GetComponent<Action>()->Stop();
				WLight->GetComponent<Action>()->AllActionClear();
				WLight->GetComponent<Action>()->
					AddMoveTo(0.2f, Vec3(-20, -170, 0.1f));
				WLight->GetComponent<Action>()->Run();
				break;
			}

			//Aボタン
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A && !SelectFlag) {
				SelectFlag = true;
				switch (NowSelect) {//現在選択中の状態によって処理を分岐
				case 0:
					PtrPlayer->SetUpdateActive(true);
					ScenePtr->SetPauseFlag(false);
					Pause->SetDrawActive(false);
					WLight->SetDrawActive(false);
					SelectFlag = false;
					break;
				case 1:
					ScenePtr->SetRespawnFlag(true);
					ScenePtr->SetPauseFlag(false);
					Fade->SetActionflag(true);
					PostEvent(0.8f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameStage");
					break;
				case 2:
					ScenePtr->SetPauseFlag(false);
					Fade->SetActionflag(true);
					PostEvent(0.8f, GetThis<ObjectInterface>(), ScenePtr, L"ToStageSelect");
					break;
				}
			}
		}
	}
	//end basecross
}
	

		