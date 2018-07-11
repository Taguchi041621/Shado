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
		PtrCamera->SetEye(Vec3(0.0f, 0.0f, -10.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void StageSelect::CreateTitleSprite() {
		////描画コンポーネントテクスチャの設定
		AddGameObject<Sprite>(L"STAGESELECT_BG_TX", false,
			Vec2(1280.0f, 800.0f), Vec3(0, 0.0f, 0.2f));

		AddGameObject<Sprite>(L"SELECT_TEXT_TX", true,
			Vec2(960, 200 / 2), Vec3(0, 330, 0.1f));
		//画面端の影
		AddGameObject<Sprite>(L"TITLE_SHADOW_TX", true,
			Vec2(1280.0f*1.2, 800.0f*1.2), Vec3(0, 0, 0.1f));
	}

	void StageSelect::CreateFadeOutSprite() {
		auto Fade = AddGameObject<SpriteFadeOut>(L"Shadow_TX", true,
			Vec2(12500, 7500), Vec3(0.0f, 0.0f, 0.0f));
		SetSharedGameObject(L"FadeOut", Fade);
	}

	void StageSelect::CreateFadeSprite(){
		auto Fade = AddGameObject<SpriteFade>(L"Shadow_TX", true,
			Vec2(840, 600), Vec3(900.0f, 0.0f, 0.0f));
			SetSharedGameObject(L"FadeIn", Fade);
	}
	//ドアを作る
	void StageSelect::CreateDoor() {
		float interval = 0;
		float hight = 0.88f;
		for (int i = 1; i <= m_MaxStageNumber; i++) {
			//ドア
			auto Door = AddGameObject<StageSelectDoor>(
				DataDir + L"StageSelectDoor\\",
				Vec3(0.4f, 0.4f, 0.1f),
				Vec3(-5.5f + interval, hight, 0),
				Vec3(0),
				Util::IntToWStr(i)
				);
			interval += 2.2f;
			SetSharedGameObject(L"Door" + Util::IntToWStr(i), Door);
			if (i % (m_MaxStageNumber / 2) == 0) {
				interval = 0;
				hight = -2.72f;
			}
		}
	}
	void StageSelect::StageNumberSprite() {
		float intervalNum = 0;
		float Paragraph = 140.0f;
		shared_ptr<ScoreSprite> Number;
		for (int i = 1; i <= 12; i++) {
			//数字
			if (i < 10) {
				Number = AddGameObject<ScoreSprite>(1,
					L"NUMBER_TX",
					true,
					Vec2(50.0f, 50.0f),
					Vec3(-512.0f + intervalNum, Paragraph, 0.0f),
					i,
					false, 0.3f);
			}
			else {
				Number = AddGameObject<ScoreSprite>(2,
					L"NUMBER_TX",
					true,
					Vec2(50.0f, 50.0f),
					Vec3(-512.0f + intervalNum, -210.0f, 0.0f),
					i,
					false, 0.3f);
			}
			SetSharedGameObject(L"ScoreSprite" + Util::IntToWStr(i), Number);
			if (i % 6 == 0) {
				Paragraph = -210.0f;
				intervalNum = 0;
			}
			intervalNum += 210;
		}
	}
	void StageSelect::CreateFrame() {
		auto frame = AddGameObject<ScaleChangeSprite>(L"pane_TX", true,
			Vec2(150.0f, 280.0f), Vec3(-512.0f, 100.0f, 0.0f), 1.0f, true);
		SetSharedGameObject(L"frame", frame);
	}

	void StageSelect::OnCreate()
	{
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		m_MaxStageNumber = 12;
		m_SelectFlag = true;
		m_StageNumber = ScenePtr->GetStageNumber();
		m_CoolTime = 0;
		//ディレクトリ取得
		App::GetApp()->GetDataDirectory(DataDir);
		//音
		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		CreateViewLight();
		//スプライトの作成
		CreateTitleSprite();
		CreateDoor();
		//StageNumberSprite();
		//CreateFrame();
		CreateFadeOutSprite();
		CreateFadeSprite();
	}

	//更新
	void StageSelect::OnUpdate() {
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		shared_ptr<StageSelectDoor> Door;
		if (onectrl) {
			m_CoolTime += App::GetApp()->GetElapsedTime();
			if (m_CoolTime >= 0.2f) {
				onectrl = false;
				m_CoolTime = 0;
			}
		}
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if ((CntlVec[0].wButtons&XINPUT_GAMEPAD_START) && (CntlVec[0].wButtons&XINPUT_GAMEPAD_BACK)) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleStage");
		}
		if (m_SelectFlag) {
			if (CntlVec[0].bConnected) {
				//左スティック左方向
				if (CntlVec[0].fThumbLX < -0.5) {
					if (onectrl == false) {
						if (!(m_StageNumber == 1)) {
							m_StageNumber -= 1;

							if (m_StopNowMusic != L"") {
								m_AudioObjectPtr->Stop(m_StopNowMusic);
							}
							m_AudioObjectPtr->AddAudioResource(L"se2");
							m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.45f);
							SetNowMusic(L"se2");
						//1回だけ動くフラグ
							onectrl = true;
						}
					}
				}
				//左スティック右方向
				else if (CntlVec[0].fThumbLX > 0.5) {
					if (onectrl == false) {
						if (!(m_StageNumber == m_MaxStageNumber)) {

							m_StageNumber += 1;

							if (m_StopNowMusic != L"") {
								m_AudioObjectPtr->Stop(m_StopNowMusic);
							}
							m_AudioObjectPtr->AddAudioResource(L"se2");
							m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.45f);
							SetNowMusic(L"se2");
							//1回だけ動くフラグ
							onectrl = true;
						}
					}
				}
				//左スティック下方向
				if (CntlVec[0].fThumbLY < -0.5) {
					if (onectrl == false) {
						//上の段から下の段へ行く
						if (m_StageNumber <= (m_MaxStageNumber / 2)) {
							m_StageNumber += (m_MaxStageNumber / 2);

							if (m_StopNowMusic != L"") {
								m_AudioObjectPtr->Stop(m_StopNowMusic);
							}
							m_AudioObjectPtr->AddAudioResource(L"se2");
							m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.45f);
							SetNowMusic(L"se2");
							//1回だけ動く
							onectrl = true;
						}
						//下の段から上に行く
						else if (m_StageNumber > (m_MaxStageNumber / 2)) {
							m_StageNumber -= (m_MaxStageNumber / 2);

							if (m_StopNowMusic != L"") {
								m_AudioObjectPtr->Stop(m_StopNowMusic);
							}
							m_AudioObjectPtr->AddAudioResource(L"se2");
							m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.45f);
							SetNowMusic(L"se2");

							onectrl = true;
						}

					}
				}
				//左スティック上方向
				if (CntlVec[0].fThumbLY > 0.5) {
					if (onectrl == false) {
						if (m_StageNumber <= (m_MaxStageNumber / 2)) {
							m_StageNumber += (m_MaxStageNumber / 2);

							if (m_StopNowMusic != L"") {
								m_AudioObjectPtr->Stop(m_StopNowMusic);
							}
							m_AudioObjectPtr->AddAudioResource(L"se2");
							m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.45f);
							SetNowMusic(L"se2");

							onectrl = true;
						}
						else if (m_StageNumber > (m_MaxStageNumber / 2)) {
							m_StageNumber -= (m_MaxStageNumber / 2);

							if (m_StopNowMusic != L"") {
								m_AudioObjectPtr->Stop(m_StopNowMusic);
							}
							m_AudioObjectPtr->AddAudioResource(L"se2");
							m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.45f);
							SetNowMusic(L"se2");

							onectrl = true;
						}
					}
				}

				//Aボタン
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
					if (m_StopNowMusic != L"") {
						m_AudioObjectPtr->Stop(m_StopNowMusic);
					}
					m_AudioObjectPtr->AddAudioResource(L"opendoor");
					m_AudioObjectPtr->Start(L"opendoor", XAUDIO2_NO_LOOP_REGION, 0.45f);
					SetNowMusic(L"opendoor");

					m_SelectFlag = false;
					ScenePtr->SetRespawnFlag(false);
					for (int i = 1; i <= m_MaxStageNumber; i++) {
						Door = GetSharedGameObject<StageSelectDoor>(L"Door" + Util::IntToWStr(i));
						//選んでるステージは
						if (i == m_StageNumber) {
							//開くアニメーションを流す
							Door->Open();
							//ドアが開いてからシーン移行するための2.8秒
							PostEvent(2.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
						}
						Door->SetRemoveFlag(true);
					}
				}
				for (int i = 1; i <= m_MaxStageNumber; i++) {
					Door = GetSharedGameObject<StageSelectDoor>(L"Door" + Util::IntToWStr(i));
					if (i == m_StageNumber) {
						Door->SetSelectFlag(true);
					}
					else {
						Door->SetSelectFlag(false);
					}
					Door->StyleChange();
				}
				//今のステージをシーンに持たせる
				ScenePtr->SetStageNumber(m_StageNumber);
			}
		}
	}

	//--------------------------------------------------------------------------------------
	//Door
	//--------------------------------------------------------------------------------------
	StageSelectDoor::StageSelectDoor(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
		const Vec3& Scale, const Vec3& Position, const Vec3& Rotation, const wstring& DoorNum)
		: SS5ssae(StagePtr, BaseDir, L"StageSelectDoor.ssae", L"SELECT_" + DoorNum),
		m_Scale(Scale), m_Position(Position), m_Rotation(Rotation), m_ScaleZ(0.05f), m_SelectFlag(false), m_DoorNum(DoorNum){
		m_ToAnimeMatrix.affineTransformation(
			Vec3(0.2f, 0.2f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.0f, 0.0f, 0.0f)
			);
	}

	StageSelectDoor::~StageSelectDoor() {}
	//初期化
	void StageSelectDoor::OnCreate() {

		//スケールのZを固定の大きさに
		m_Scale.z = m_ScaleZ;
		auto PtrTransform = GetComponent<Transform>();
		//影のスケール,角度,ポジションの設定
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(m_Position);

		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(30);
		//アニメーションのループ設定
		SetLooped(false);
		//アニメーションにかけるメトリックスの設定
		SetToAnimeMatrix(m_ToAnimeMatrix);
		UpdateAnimeTime(0);
		SetSpriteDraw(true);
	}

	//変化
	void StageSelectDoor::OnUpdate() {
		float ElapsedTime = 0;
		//カーソルが自分のドアにある時
		if (m_SelectFlag && !m_OpenFlag) {
			ElapsedTime += App::GetApp()->GetElapsedTime();
			auto pos = GetComponent<Transform>()->GetWorldPosition();
			auto sca = GetComponent<Transform>()->GetScale();
			if (sca.x >= 0.5f) {
				deflection = -0.001f;
			}
			if(sca.x < 0.4) {
				deflection = 0.001f;
			}
			//ドアの大きさを増減して、それに合わせて高さを変える
			pos.y += deflection*3.0f;
			sca.x += deflection;
			sca.y += deflection;
			//適応
			GetComponent<Transform>()->SetWorldPosition(pos);
			GetComponent<Transform>()->SetScale(sca);
		}
		//開いたとき
		if (m_OpenFlag) {
			ElapsedTime += App::GetApp()->GetElapsedTime();
			//開くアニメーションが終わったら
			if (IsAnimeEnd()) {
				//フェードを入れる
				auto FadeIn = GetStage()->GetSharedGameObject<SpriteFade>(L"FadeIn");
				FadeIn->SetActionflag(true);
			}
		}
		if (m_RemoveFlag) {
			m_RemoveTime += App::GetApp()->GetElapsedTime();
			if (m_RemoveTime >= 2.0f) {
				GetStage()->RemoveGameObject<StageSelectDoor>(GetThis<StageSelectDoor>());
			}
		}
		//アニメーションの更新
		UpdateAnimeTime(ElapsedTime);
	}

	void StageSelectDoor::OnUpdate2() {
	}

	void StageSelectDoor::Open() {
		m_OpenFlag = true;
		ChangeAnimation(L"OPEN_" + m_DoorNum);
		SetLooped(false);
	}
	void StageSelectDoor::StyleChange(){
		if (m_OpenFlag) {
			//初期位置、初期サイズに戻す
			GetComponent<Transform>()->SetWorldPosition(m_Position);
			GetComponent<Transform>()->SetScale(m_Scale);
		}
		else if (m_SelectFlag) {
			ChangeAnimation(L"SELECT_" + m_DoorNum);
			SetLooped(true);
		}
		//選択されていない、開かれていない時
		else {
			//初期位置、初期サイズに戻す
			GetComponent<Transform>()->SetWorldPosition(m_Position);
			GetComponent<Transform>()->SetScale(m_Scale);
			//赤枠をなくすための"OPEN"アニメ、
			//アニメーションの更新を行わないため閉じた状態のまま
			ChangeAnimation(L"OPEN_" + m_DoorNum);
		}
	}
}
