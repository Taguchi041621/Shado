
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
		wstring strTexture = DataDir + L"Title.jpg";
		App::GetApp()->RegisterTexture(L"TITLE_TX", strTexture);
		/*strTexture = DataDir + L"Select.png";
		App::GetApp()->RegisterTexture(L"SELECT_TX", strTexture);*/

		//�N���A���
		strTexture = DataDir + L"Clear_Sample_image.png";
		App::GetApp()->RegisterTexture(L"CLEAR_NoText_TX", strTexture);
		strTexture = DataDir + L"Clear.png";
		App::GetApp()->RegisterTexture(L"CLEAR_TX", strTexture);
		strTexture = DataDir + L"GAMECLEAR_NoText.png";
		App::GetApp()->RegisterTexture(L"CLEAR_ColorNoText_TX", strTexture);
		strTexture = DataDir + L"GAMECLEAR.png";
		App::GetApp()->RegisterTexture(L"CLEAR_Color_TX", strTexture);
		strTexture = DataDir + L"STAGESELECT.png";
		App::GetApp()->RegisterTexture(L"CLEAR_STAGESELECT_TX", strTexture);
		strTexture = DataDir + L"NEXTSTAGE.png";
		App::GetApp()->RegisterTexture(L"CLEAR_NEXTSTAGE_TX", strTexture);
		strTexture = DataDir + L"RETRY.png";
		App::GetApp()->RegisterTexture(L"CLEAR_RETRY_TX", strTexture);
		strTexture = DataDir + L"STAGECLEAR.png";
		App::GetApp()->RegisterTexture(L"CLEAR_STAGECLEAR_TX", strTexture);

		//�Q�[���I�[�o�[���
		strTexture = DataDir + L"GameOver1.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_TX", strTexture);
		strTexture = DataDir + L"GameOverMoji.png";
		App::GetApp()->RegisterTexture(L"GameOverMoji_TX", strTexture);
		//��
		strTexture = DataDir + L"WallTexture.png";
		App::GetApp()->RegisterTexture(L"WallTexture_TX", strTexture);
		strTexture = DataDir + L"Red.tga";
		App::GetApp()->RegisterTexture(L"Red_TX", strTexture);
		strTexture = DataDir + L"Blue.tga";
		App::GetApp()->RegisterTexture(L"Blue_TX", strTexture);
		strTexture = DataDir + L"yellow.tga";
		App::GetApp()->RegisterTexture(L"Yellow_TX", strTexture);
		strTexture = DataDir + L"shadow.png";
		App::GetApp()->RegisterTexture(L"Shadow_TX", strTexture);
		strTexture = DataDir + L"Key.png";
		App::GetApp()->RegisterTexture(L"Key_TX", strTexture);
		strTexture = DataDir + L"Shadow_Blur4.png";
		App::GetApp()->RegisterTexture(L"Shadow_Blur_TX", strTexture);
		strTexture = DataDir + L"LIGHT2.png";
		App::GetApp()->RegisterTexture(L"GameOver_WhiteLight_TX", strTexture);
		strTexture = DataDir + L"RETRY_OFF.png";
		App::GetApp()->RegisterTexture(L"RETRY_OFF_TX", strTexture);
		strTexture = DataDir + L"STAGE_SELECT_OFF.png";
		App::GetApp()->RegisterTexture(L"STAGE_SELECT_OFF_TX", strTexture);
		strTexture = DataDir + L"pane.png";//�g
		App::GetApp()->RegisterTexture(L"pane_TX", strTexture);
		strTexture = DataDir + L"ball_yellow.png";//���F����
		App::GetApp()->RegisterTexture(L"ball_yellow_TX", strTexture); 
		strTexture = DataDir + L"PressAStart_0424.png";
		App::GetApp()->RegisterTexture(L"TITLE_TEXT_TX", strTexture);
		strTexture = DataDir + L"StageSlect.png";
		App::GetApp()->RegisterTexture(L"SELECT_TEXT_TX", strTexture); 

			strTexture = DataDir + L"StageSlect.png";
		App::GetApp()->RegisterTexture(L"SELECT_TEXT_TX", strTexture);

		strTexture = DataDir + L"Background2.png";
		App::GetApp()->RegisterTexture(L"STAGESELECT_BG_TX", strTexture);
		strTexture = DataDir + L"Arrow.png";
		App::GetApp()->RegisterTexture(L"ARROW_TX", strTexture);
		
		strTexture = DataDir + L"Bullet.png";
		App::GetApp()->RegisterTexture(L"BULLET_TX", strTexture);
		strTexture = DataDir + L"ring.png"; 
		App::GetApp()->RegisterTexture(L"Ring_TX", strTexture);

		strTexture = DataDir + L"Pause.png";
		App::GetApp()->RegisterTexture(L"PAUSE_TX", strTexture);


		//����UI
		strTexture = DataDir + L"UI_Key.png";//���h��
		App::GetApp()->RegisterTexture(L"UI_Key_TX", strTexture);
		strTexture = DataDir + L"UI_Key_NoneBigLine.png";//�ӂ���������
		App::GetApp()->RegisterTexture(L"UI_Key_None_TX", strTexture);

		strTexture = DataDir + L"Door.png";
		App::GetApp()->RegisterTexture(L"Door_TX", strTexture);
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

		strTexture = DataDir + L"Number2.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);

		strTexture = DataDir + L"TiteleShadow.png";
		App::GetApp()->RegisterTexture(L"TITLE_SHADOW_TX", strTexture);

		//���C�g�̃��f��
		auto StaticModelMesh = MeshResource::CreateStaticModelMesh(DataDir + L"Light\\", L"LIGHT1.bmf");
		App::GetApp()->RegisterResource(L"LIGHT_MESH", StaticModelMesh);
		//���C�g�̃C���X�g
		strTexture = DataDir + L"Light\\LIGHT_Illust.png";
		App::GetApp()->RegisterTexture(L"LIGHT_Illust_TX", strTexture);


		//Tutorial�@
		strTexture = DataDir + L"Tutorial_cameraMove.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_CAMERA_MOVE_TX", strTexture);
		strTexture = DataDir + L"Tutorial_CharaMove.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_CHARA_MOVE_TX", strTexture);
		strTexture = DataDir + L"Tutorial_LjghtMove.png";
		App::GetApp()->RegisterTexture(L"TUTORIAL_LIGHT_MOVE_TX", strTexture);

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
			m_AudioObjectPtr->Start(L"titel", XAUDIO2_LOOP_INFINITE, 0.62f);
			m_StopNowMusic = L"titel";

		}
		//------------------------------------------------------
		else if (event->m_MsgStr == L"ToStageSelect") {
			if (m_StopNowMusic == L"gameover", L"clear")
			{
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
			if (m_StopNowMusic != L"")
			{
				m_AudioObjectPtr->Stop(m_StopNowMusic);
			}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
			ResetActiveStage<GameStage>();

			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"gamestage");
			m_AudioObjectPtr->Start(L"gamestage", XAUDIO2_LOOP_INFINITE, 0.6f);
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
			m_AudioObjectPtr->Start(L"gameover", XAUDIO2_LOOP_INFINITE, 0.62f);
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
			m_AudioObjectPtr->Start(L"clear", XAUDIO2_LOOP_INFINITE, 0.62f);
			m_StopNowMusic = L"clear";
			

		}
	}


}
//end basecross
