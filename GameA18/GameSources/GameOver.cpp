#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void GameOverStage::CreateViewLight()
	{
		//auto PtrView = CreateView<SingleView>();
		////�r���[�̃J�����̐ݒ�
		//auto PtrCamera = ObjectFactory::Create<Camera>();
		//PtrView->SetCamera(PtrCamera);
		//PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		//PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		////�}���`���C�g�̍쐬
		//auto PtrMultiLight = CreateLight<MultiLight>();
		////�f�t�H���g�̃��C�e�B���O���w��
		//PtrMultiLight->SetDefaultLighting();
		auto PtrView = CreateView<SingleView>();
		//�V���h�E�}�b�v�͎g�p���Ȃ�
		SetShadowmapDraw(false);
	}

	void GameOverStage::CreateTitleSprite()
	{
		////�X�e�[�W�ւ̃Q�[���I�u�W�F�N�g�̒ǉ�
		//auto Ptr = AddGameObject<GameObject>();
		//auto PtrTrans = Ptr->GetComponent<Transform>();
		//Quat Qt;
		//Qt.rotationRollPitchYawFromVector(Vec3(1.0, 0, 0));
		//PtrTrans->SetScale(5.5f, 4.0f, 1.0f);
		//PtrTrans->SetQuaternion(Qt);
		//PtrTrans->SetPosition(0.0f, 0.5f, 0.0f);

		//auto ColPtr = Ptr->AddComponent<CollisionRect>();
		////�`��R���|�[�l���g�̒ǉ�
		//auto DrawComp = Ptr->AddComponent<BcPNTStaticDraw>();
		////�`��R���|�[�l���g�Ɍ`��i���b�V���j��ݒ�
		//DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		//DrawComp->SetFogEnabled(true);
		////�����ɉe���f�肱�ނ悤�ɂ���
		//DrawComp->SetOwnShadowActive(true);

		////�`��R���|�[�l���g�e�N�X�`���̐ݒ�
		//DrawComp->SetTextureResource(L"GAMEOVER_TX");

		//AddGameObject<TitleSprite>(L"TITLE_TX", false,
		//	Vec2(1000.0f, 600.0f), Vec2(0.0f, 0.0f));
		AddGameObject<Sprite>(L"GAMEOVER_TX", false,
			Vec2(1280.0f, 800.0f), Vec3(0, 0.0f, 0.1f));
	}
	void GameOverStage::CreateFadeOutSprite()
	{
		auto Fade = AddGameObject<SpriteFadeOut>(L"Shadow_TX", true,
			Vec2(50000 / 4, 30000 / 4), Vec3(0.0f, 600.0f, 0.1f));
		SetSharedGameObject(L"FadeOut", Fade);

	}

	void GameOverStage::CreateFadeSprite()
	{
		auto Fade = AddGameObject<SpriteFade>(L"Shadow_TX", true,
			Vec2(840, 600), Vec3(900.0f, 0.0f, 0.1f));
		SetSharedGameObject(L"FadeIn", Fade);

	}

	void GameOverStage::OnCreate()
	{
		m_SelectFlag = false;
		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateTitleSprite();
		CreateFadeOutSprite();
		CreateFadeSprite();
	}

	//�X�V
	void GameOverStage::OnUpdate() {
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {

			//A�{�^��
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A && !m_SelectFlag) {
				if (m_StopNowMusic != L"")
				{
					m_AudioObjectPtr->Stop(m_StopNowMusic);
				}
				wstring DataDir;
				//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
				//App::GetApp()->GetAssetsDirectory(DataDir);
				//�e�Q�[���͈ȉ��̂悤�Ƀf�[�^�f�B���N�g�����擾���ׂ�
				App::GetApp()->GetDataDirectory(DataDir);

				m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
				m_AudioObjectPtr->AddAudioResource(L"se");
				m_AudioObjectPtr->Start(L"se", XAUDIO2_NO_LOOP_REGION, 0.1f);
				SetNowMusic(L"se");

				auto FadeIn = GetSharedGameObject<SpriteFade>(L"FadeIn");
				FadeIn->SetActionflag(true);
				m_SelectFlag = true;
				PostEvent(2.4f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStageSelect");
			}
		}
	}
}