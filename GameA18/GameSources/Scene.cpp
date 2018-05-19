
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
		wstring strTexture = DataDir + L"sky.jpg";
		App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);
		strTexture = DataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		strTexture = DataDir + L"Oreng.png";
		App::GetApp()->RegisterTexture(L"Oreng_TX", strTexture);
		strTexture = DataDir + L"Title.jpg";
		App::GetApp()->RegisterTexture(L"TITLE_TX", strTexture);
		strTexture = DataDir + L"Select.png";
		App::GetApp()->RegisterTexture(L"SELECT_TX", strTexture);
		strTexture = DataDir + L"Clear.png";
		App::GetApp()->RegisterTexture(L"CLEAR_TX", strTexture);
		strTexture = DataDir + L"GameOver.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_TX", strTexture);
		strTexture = DataDir + L"WallTexture.png";
		App::GetApp()->RegisterTexture(L"WallTexture_TX", strTexture);
		strTexture = DataDir + L"Red.tga";
		App::GetApp()->RegisterTexture(L"Red_TX", strTexture);
		strTexture = DataDir + L"shadow.png";
		App::GetApp()->RegisterTexture(L"Shadow_TX", strTexture);
		strTexture = DataDir + L"Key.png";
		App::GetApp()->RegisterTexture(L"Key_TX", strTexture);
		strTexture = DataDir + L"UI_Key.png";
		App::GetApp()->RegisterTexture(L"UI_Key_TX", strTexture);
		strTexture = DataDir + L"UI_Key_None.png";
		App::GetApp()->RegisterTexture(L"UI_Key_None_TX", strTexture);

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
		if (event->m_MsgStr == L"ToTitleStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<TitleStage>();
		}
		else if (event->m_MsgStr == L"ToStageSelect") {
			ResetActiveStage<StageSelect>();
		}
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
			ResetActiveStage<ClearStage>();
		}
	}


}
//end basecross
