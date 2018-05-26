#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void ClearStage::CreateViewLight()
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

	void ClearStage::CreateTitleSprite()
	{
		////�X�e�[�W�ւ̃Q�[���I�u�W�F�N�g�̒ǉ�
		//auto Ptr = AddGameObject<GameObject>();
		//auto PtrTrans = Ptr->GetComponent<Transform>();
		//Quat Qt;
		//Qt.rotationRollPitchYawFromVector(Vec3(0.65, 0, 0));
		//PtrTrans->SetScale(6.0f, 5.0f, 1.0f);
		//PtrTrans->SetQuaternion(Qt);
		//PtrTrans->SetPosition(0.0f, 0.0f, 0.0f);

		//auto ColPtr = Ptr->AddComponent<CollisionRect>();
		////�`��R���|�[�l���g�̒ǉ�
		//auto DrawComp = Ptr->AddComponent<BcPNTStaticDraw>();
		////�`��R���|�[�l���g�Ɍ`��i���b�V���j��ݒ�
		//DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		//DrawComp->SetFogEnabled(true);
		////�����ɉe���f�肱�ނ悤�ɂ���
		//DrawComp->SetOwnShadowActive(true);

		////�`��R���|�[�l���g�e�N�X�`���̐ݒ�
		//DrawComp->SetTextureResource(L"CLEAR_TX");

		//AddGameObject<TitleSprite>(L"TITLE_TX", false,
		//	Vec2(1000.0f, 600.0f), Vec2(0.0f, 0.0f));
		AddGameObject<Sprite>(L"CLEAR_TX", false,
			Vec2(1280.0f, 800.0f), Vec3(0, 0.0f, 0.1f));
	}
	void ClearStage::CreateFadeOutSprite()
	{
		auto Fade = AddGameObject<SpriteFadeOut>(L"Shadow_TX", true,
			Vec2(50000 / 4, 30000 / 4), Vec3(0.0f, 600.0f, -0.0f));
		SetSharedGameObject(L"FadeOut", Fade);
	}

	void ClearStage::CreateFadeSprite()
	{
		auto Fade = AddGameObject<SpriteFade>(L"Shadow_TX", true,
			Vec2(840, 600), Vec3(900.0f, 0.0f, -0.0f));
		SetSharedGameObject(L"FadeIn", Fade);
	}

	void ClearStage::CreateUI() {
		//������
		auto WLight = AddGameObject<ScaleChangeSprite>(L"GameOver_WhiteLight_TX", true,
			Vec2(960, 600), Vec3(150.0, 60, 0.0f),3.0f);
		//�������̃A�j���[�V����
		WLight->AddComponent<Action>();
		WLight->GetComponent<Action>()->AllActionClear();
		SetSharedGameObject(L"WLight", WLight);
	}

	void ClearStage::OnCreate()
	{
		NowSelect = 0;
		m_ScaleTimer = 0;
		m_ScaleFlag = true;

		ThumbFlag = true;
		CreateViewLight();

		//�X�v���C�g�̍쐬
		CreateTitleSprite();
		CreateUI();
		CreateFadeOutSprite();
		CreateFadeSprite();

	}

	//�X�V
	void ClearStage::OnUpdate() {
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		auto WLight = GetSharedGameObject<ScaleChangeSprite>(L"WLight");
		auto Time = App::GetApp()->GetElapsedTime();
		ThumbTimer += Time;
		m_ScaleTimer += Time;
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (ThumbTimer > 0.5f) {
				ThumbFlag = true;
			}
			if (!SelectFlag) {//�R���g���[���[�̏���
				if (CntlVec[0].fThumbLX < -0.5f) {
					if (ThumbFlag) {
						NowSelect -= 1;//�I����Ԃ��E��
						ThumbTimer = 0.0f;
						ThumbFlag = false;
					}
				}
				else if (CntlVec[0].fThumbLX > 0.5f) {
					if (ThumbFlag) {
						NowSelect += 1;//�I����Ԃ�����
						ThumbTimer = 0.0f;
						ThumbFlag = false;
					}
				}
			}

			if (NowSelect < 0) {
				NowSelect = 2;
			}

			if (NowSelect > 2) {
				NowSelect = 0;
			}


			switch (NowSelect) {//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
			case 0:
				WLight->GetComponent<Action>()->Stop();
					WLight->GetComponent<Action>()->AllActionClear();
					WLight->GetComponent<Action>()->
						AddMoveTo(0.2f, Vec3(150.0, 60, 0.0f));
					WLight->GetComponent<Action>()->Run();
				break;
			case 1:
				WLight->GetComponent<Action>()->Stop();
					WLight->GetComponent<Action>()->AllActionClear();
					WLight->GetComponent<Action>()->
						AddMoveTo(0.2f, Vec3(-100.0, -230, 0.0f));
					WLight->GetComponent<Action>()->Run();
				break;
			case 2:
				WLight->GetComponent<Action>()->Stop();
					WLight->GetComponent<Action>()->AllActionClear();
					WLight->GetComponent<Action>()->
						AddMoveTo(0.2f, Vec3(420.0, -230, 0.0f));
					WLight->GetComponent<Action>()->Run();
				break;
			}

			//A�{�^��
			auto Number = ScenePtr->GetStageNumber();
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				auto FadeIn = GetSharedGameObject<SpriteFade>(L"FadeIn");
				FadeIn->SetActionflag(true);
				SelectFlag = true;
				switch (NowSelect) {//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
				case 0:
					ScenePtr->SetStageNumber(Number + 1);
					ScenePtr->SetRespawnFlag(false);
					PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
					break;
				case 1:
					ScenePtr->SetRespawnFlag(false);
					PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
					break;
				case 2:
					PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStageSelect");
					break;
				}
			}
		}
	}
}
