
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
		//サンプルのためアセットディレクトリを取得
		//App::GetApp()->GetAssetsDirectory(DataDir);
		//各ゲームは以下のようにデータディレクトリを取得すべき
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"Title.jpg";
		App::GetApp()->RegisterTexture(L"TITLE_TX", strTexture);
		strTexture = DataDir + L"Select.png";
		App::GetApp()->RegisterTexture(L"SELECT_TX", strTexture);
		strTexture = DataDir + L"Clear.png";
		App::GetApp()->RegisterTexture(L"CLEAR_TX", strTexture);
		//GameOver = 文字あり、GameOver1 = 文字なし
		strTexture = DataDir + L"GameOver1.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_TX", strTexture);
		strTexture = DataDir + L"GameOverMoji.png";
		App::GetApp()->RegisterTexture(L"GameOverMoji_TX", strTexture);
		strTexture = DataDir + L"WallTexture.png";
		App::GetApp()->RegisterTexture(L"WallTexture_TX", strTexture);
		strTexture = DataDir + L"Red.tga";
		App::GetApp()->RegisterTexture(L"Red_TX", strTexture);
		strTexture = DataDir + L"shadow.png";
		App::GetApp()->RegisterTexture(L"Shadow_TX", strTexture);
		strTexture = DataDir + L"Key.png";
		App::GetApp()->RegisterTexture(L"Key_TX", strTexture);
		strTexture = DataDir + L"Shadow_Blur.png";
		App::GetApp()->RegisterTexture(L"Shadow_Blur_TX", strTexture);
		strTexture = DataDir + L"LIGHT2.png";
		App::GetApp()->RegisterTexture(L"GameOver_WhiteLight_TX", strTexture);
		strTexture = DataDir + L"RETRY_OFF.png";
		App::GetApp()->RegisterTexture(L"RETRY_OFF_TX", strTexture);
		strTexture = DataDir + L"STAGE_SELECT_OFF.png";
		App::GetApp()->RegisterTexture(L"STAGE_SELECT_OFF_TX", strTexture);
		strTexture = DataDir + L"pane.png";//枠
		App::GetApp()->RegisterTexture(L"pane_TX", strTexture);
		strTexture = DataDir + L"ball_yellow.png";//黄色い丸
		App::GetApp()->RegisterTexture(L"ball_yellow_TX", strTexture); 
		strTexture = DataDir + L"PressAStart_0424.png";
		App::GetApp()->RegisterTexture(L"TITLE_TEXT_TX", strTexture);
		strTexture = DataDir + L"StageSlect.png";
		App::GetApp()->RegisterTexture(L"SELECT_TEXT_TX", strTexture);

		strTexture = DataDir + L"Pause.png";
		App::GetApp()->RegisterTexture(L"PAUSE_TX", strTexture);


		//鍵のUI候補↓
		strTexture = DataDir + L"UI_Key.png";//黒塗り
		App::GetApp()->RegisterTexture(L"UI_Key_TX", strTexture);
		//strTexture = DataDir + L"UI_Key_None.png";//ふち細中抜き
		//App::GetApp()->RegisterTexture(L"UI_Key_None_TX", strTexture);
		strTexture = DataDir + L"UI_Key_NoneBigLine.png";//ふち太中抜き
		App::GetApp()->RegisterTexture(L"UI_Key_None_TX", strTexture);
		//strTexture = DataDir + L"UI_Key_NoneWhite.png";//白塗
		//App::GetApp()->RegisterTexture(L"UI_Key_None_TX", strTexture);
		//鍵のUI候補↑

		strTexture = DataDir + L"Door.png";
		App::GetApp()->RegisterTexture(L"Door_TX", strTexture);
		//数字
		strTexture = DataDir + L"number_0.png";
		App::GetApp()->RegisterTexture(L"0_TX", strTexture);
		strTexture = DataDir + L"number_1.png";
		App::GetApp()->RegisterTexture(L"1_TX", strTexture);
		strTexture = DataDir + L"number_2.png";
		App::GetApp()->RegisterTexture(L"2_TX", strTexture);
		strTexture = DataDir + L"number_3.png";
		App::GetApp()->RegisterTexture(L"3_TX", strTexture);
		strTexture = DataDir + L"number_4.png";
		App::GetApp()->RegisterTexture(L"4_TX", strTexture);
		strTexture = DataDir + L"number_5.png";
		App::GetApp()->RegisterTexture(L"5_TX", strTexture);
		strTexture = DataDir + L"number_6.png";
		App::GetApp()->RegisterTexture(L"6_TX", strTexture);
		strTexture = DataDir + L"number_7.png";
		App::GetApp()->RegisterTexture(L"7_TX", strTexture);
		strTexture = DataDir + L"number_8.png";
		App::GetApp()->RegisterTexture(L"8_TX", strTexture);
		strTexture = DataDir + L"number_9.png";
		App::GetApp()->RegisterTexture(L"9_TX", strTexture);

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
		wstring Clear = DataDir + L"BGMSE\\kuria.wav";
		App::GetApp()->RegisterWav(L"clear", Clear);
	}

	void Scene::OnCreate() {
		try {
			//リソース作成
			CreateResourses();
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");
		}
		catch (...) {
			throw;
		}
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		//------------------------------------------------------
		if (event->m_MsgStr == L"ToTitleStage") {

			//最初のアクティブステージの設定
			ResetActiveStage<TitleStage>();
			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"titel");
			m_AudioObjectPtr->Start(L"titel", XAUDIO2_LOOP_INFINITE, 0.1f);
			m_StopNowMusic = L"titel";

		}
		//------------------------------------------------------
		else if (event->m_MsgStr == L"ToStageSelect") {
			if (m_StopNowMusic == L"gameover")
			{
			m_AudioObjectPtr->Stop(m_StopNowMusic);	
			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"titel");
			m_AudioObjectPtr->Start(L"titel", XAUDIO2_NO_LOOP_REGION, 0.1f);
			m_StopNowMusic = L"titel";
			}

            ResetActiveStage<StageSelect>();
		}
		//------------------------------------------------------
		else if (event->m_MsgStr == L"ToGameStage") {
			if (m_StopNowMusic != L"")
			{
				m_AudioObjectPtr->Stop(m_StopNowMusic);
			}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
			ResetActiveStage<GameStage>();

			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"gamestage");
			m_AudioObjectPtr->Start(L"gamestage", XAUDIO2_LOOP_INFINITE, 0.1f);
			m_StopNowMusic = L"gamestage";
		}
		//------------------------------------------------------
		else if (event->m_MsgStr == L"ToGameOver") {
			if (m_StopNowMusic != L"")
			{
				m_AudioObjectPtr->Stop(m_StopNowMusic);
			}
			ResetActiveStage<GameOverStage>();
			
			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"gameover");
			m_AudioObjectPtr->Start(L"gameover", XAUDIO2_LOOP_INFINITE, 0.1f);
			m_StopNowMusic = L"gameover";
			
		}
		//------------------------------------------------------
		else if (event->m_MsgStr == L"ToClearStage") {
			if (m_StopNowMusic != L"")
			{
				m_AudioObjectPtr->Stop(m_StopNowMusic);
			}
			ResetActiveStage<ClearStage>();
			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"clear");
			m_AudioObjectPtr->Start(L"clear", XAUDIO2_NO_LOOP_REGION, 0.1f);
			m_StopNowMusic = L"clear";

		}
	}


}
//end basecross
