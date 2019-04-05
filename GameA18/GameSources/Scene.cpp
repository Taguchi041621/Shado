
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::CreateResourses() {
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture;

		//キー名,ファイル名を持った構造体
		struct TexPair {
			std::wstring key;
			std::wstring filename;
		};
		//キー名,ファイル名を入れる
		TexPair pairs[] = { 
			{L"TITLE_TX",L"Title.png"},
			{L"CLEAR_NoText_TX",		L"Clear_Image.png"},
			{L"CLEAR_ColorNoText_TX",	L"GAMECLEAR_NoText.png"},
			{L"CLEAR_Color_TX",			L"GAMECLEAR.png"},
			{L"CLEAR_STAGESELECT_TX",	L"STAGESELECT.png"},
			{L"CLEAR_NEXTSTAGE_TX",		L"NEXTSTAGE.png"},
			{L"CLEAR_RETRY_TX",			L"RETRY.png"},
			{L"CLEAR_STAGECLEAR_TX",	L"STAGECLEAR.png"},
			{L"WallTexture_TX",		L"WallTexture.png"},
			{L"Red_TX",		L"Red.tga"},
			{L"Blue_TX",	L"Blue.tga"},
			{L"Yellow_TX",	L"yellow.tga"},
			{L"shadow_frame_TX",	L"shadow_frame.png"},
			{L"Shadow_Blur_TX",		L"Shadow_Blur.png"},
			{L"RETRY_OFF_TX",		L"RETRY_OFF.png"},
			{L"STAGE_SELECT_OFF_TX",	L"STAGE_SELECT_OFF.png"},
			{L"TITLE_TEXT_TX",		L"PressAStart.png"},
			{L"SELECT_TEXT_TX",		L"StageSlect.png"},
			{L"STAGESELECT_BG_TX",		L"Background2.png"},
			{L"Shadow_TX",		L"shadow.png"},
			{L"BULLET_TX",		L"Bullet.png"},
			{L"Smoke_Black_TX",		L"smoke_Black.png"},
			{L"Ring_TX",		L"ring.png"},
			{L"splashLogo_TX",		L"splash512Logo.png"},
			{L"Credit_Link_TX",		L"Credit_Link.png"},
			{L"PAUSE_TX",		L"Pause.png"},
			{L"TITLE_SHADOW_TX",		L"TiteleShadow.png"},
			{L"GameOver_WhiteLight_TX",	L"LIGHT2.png"},
			{L"TUTORIAL_LIGHT_MOVE_TX",	L"Tutorial_LightMove_Mono.png"},
			{L"TUTORIAL_CHARA_MOVE_TX",	L"Tutorial_CharaMove_Mono.png"},
			{L"TUTORIAL_CAMERA_MOVE_TX",	L"Tutorial_cameraMove_Mono.png"},
			{L"LIGHT_Illust_TX",L"Light\\LIGHT_Illust.png"}
		};
		//読み込む
		for (auto& pair : pairs) {
			strTexture = DataDir + pair.filename;
			App::GetApp()->RegisterTexture(pair.key, strTexture);
		}
		//ライトのモデル
		auto StaticModelMesh = MeshResource::CreateStaticModelMesh(DataDir + L"Light\\", L"LIGHT1.bmf");
		App::GetApp()->RegisterResource(L"LIGHT_MESH", StaticModelMesh);

		/*BGM・SE関連*/
		//ゲームオーバーBGM
		wstring GameOver = DataDir + L"BGMSE\\GameOver.wav";
		App::GetApp()->RegisterWav(L"gameover", GameOver);
		wstring GameStage = DataDir + L"BGMSE\\gamestage.WAV";
		App::GetApp()->RegisterWav(L"gamestage", GameStage);
		wstring walk = DataDir + L"BGMSE\\walk.wav";
		App::GetApp()->RegisterWav(L"walk", walk);
		wstring Dead = DataDir + L"BGMSE\\Dead.wav";
		App::GetApp()->RegisterWav(L"dead", Dead);
		wstring Titel = DataDir + L"BGMSE\\Titel.wav";
		App::GetApp()->RegisterWav(L"titel", Titel);
		wstring SE = DataDir + L"BGMSE\\SE.wav";
		App::GetApp()->RegisterWav(L"se", SE);
		wstring SE2 = DataDir + L"BGMSE\\SE2.wav";
		App::GetApp()->RegisterWav(L"se2", SE2);
		wstring SE3 = DataDir + L"BGMSE\\bon.wav";
		App::GetApp()->RegisterWav(L"se3", SE3);
		wstring SE4 = DataDir + L"BGMSE\\bomb.wav";
		App::GetApp()->RegisterWav(L"se4", SE4);
		wstring SE5 = DataDir + L"BGMSE\\chakuchi.wav";
		App::GetApp()->RegisterWav(L"se5", SE5);
		wstring SE6 = DataDir + L"BGMSE\\Collapse.wav";
		App::GetApp()->RegisterWav(L"se6", SE6);
		wstring opendoor = DataDir + L"BGMSE\\opendoor.wav";
		App::GetApp()->RegisterWav(L"opendoor", opendoor);
		wstring Clear = DataDir + L"BGMSE\\yakusoku.wav";
		App::GetApp()->RegisterWav(L"clear", Clear);
		wstring KeySound = DataDir + L"BGMSE\\Getkey.wav";
		App::GetApp()->RegisterWav(L"KeySound", KeySound);
	}

	void Scene::OnCreate() {
		try {
			//リソース作成
			CreateResourses();
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToBannerStage");
		}
		catch (...) {
			throw;
		}
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (m_StopNowMusic != L"") {
			m_AudioObjectPtr->Stop(m_StopNowMusic);
		}

		//------------------------------------------------------
		if (event->m_MsgStr == L"ToTitleStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<TitleStage>();
			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"titel");
			m_AudioObjectPtr->Start(L"titel", XAUDIO2_LOOP_INFINITE, 0.62f);
			m_StopNowMusic = L"titel";
		}
		//------------------------------------------------------
		else if (event->m_MsgStr == L"ToStageSelect") {
			if (m_StopNowMusic == L"gameover", L"clear") {
				m_AudioObjectPtr->Stop(m_StopNowMusic);
				m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
				m_AudioObjectPtr->AddAudioResource(L"titel");
				m_AudioObjectPtr->Start(L"titel", XAUDIO2_NO_LOOP_REGION, 0.6f);
				m_StopNowMusic = L"titel";
			}

            ResetActiveStage<StageSelect>();
		}
		//------------------------------------------------------
		else if (event->m_MsgStr == L"ToGameStage") {
			ResetActiveStage<GameStage>();

			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"gamestage");
			m_AudioObjectPtr->Start(L"gamestage", XAUDIO2_LOOP_INFINITE, 0.6f);
			m_StopNowMusic = L"gamestage";
		}
		//------------------------------------------------------
		else if (event->m_MsgStr == L"ToClearStage") {
			ResetActiveStage<ClearStage>();
			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"clear");
			m_AudioObjectPtr->Start(L"clear", XAUDIO2_LOOP_INFINITE, 0.62f);
			m_StopNowMusic = L"clear";
		}
		//------------------------------------------------------
		else if (event->m_MsgStr == L"ToBannerStage") {
			ResetActiveStage<BannerStage>();
		}
	}
}
//end basecross
