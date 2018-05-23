
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::CreateResourses() {
		wstring DataDir;
		//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
		//App::GetApp()->GetAssetsDirectory(DataDir);
		//�e�Q�[���͈ȉ��̂悤�Ƀf�[�^�f�B���N�g�����擾���ׂ�
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
		//����UI��⁫
		strTexture = DataDir + L"UI_Key.png";//���h��
		App::GetApp()->RegisterTexture(L"UI_Key_TX", strTexture);
		//strTexture = DataDir + L"UI_Key_None.png";//�ӂ��ג�����
		//App::GetApp()->RegisterTexture(L"UI_Key_None_TX", strTexture);
		strTexture = DataDir + L"UI_Key_NoneBigLine.png";//�ӂ���������
		App::GetApp()->RegisterTexture(L"UI_Key_None_TX", strTexture);
		//strTexture = DataDir + L"UI_Key_NoneWhite.png";//���h
		//App::GetApp()->RegisterTexture(L"UI_Key_None_TX", strTexture);
		strTexture = DataDir + L"Key_0522.png";
		App::GetApp()->RegisterTexture(L"Key_0522_TX", strTexture);
		strTexture = DataDir + L"Key_None_0522.png";
		App::GetApp()->RegisterTexture(L"Key_None_0522_TX", strTexture);
		//����UI��⁪
		strTexture = DataDir + L"Shadow_Blur.png";
		App::GetApp()->RegisterTexture(L"Shadow_Blur_TX", strTexture);

		//����
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

		/*BGM�ESE�֘A*/
		//�Q�[���I�[�o�[BGM
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

	}

	void Scene::OnCreate() {
		try {
			//���\�[�X�쐬
			CreateResourses();
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");
		}
		catch (...) {
			throw;
		}
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		//------------------------------------------------------
		if (event->m_MsgStr == L"ToTitleStage") {

			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
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
			ResetActiveStage<ClearStage>();
		}
	}


}
//end basecross
