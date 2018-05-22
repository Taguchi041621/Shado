#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void TitleStage::CreateViewLight()
	{
		//auto PtrView = CreateView<SingleView>();
		////�r���[�̃J�����̐ݒ�
		//auto PtrCamera = ObjectFactory::Create<Camera>();
		//PtrView->SetCamera(PtrCamera);
		//PtrCamera->SetEye(Vec3(0.0f, 2.0f, -4.0f));
		//PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		////�}���`���C�g�̍쐬
		//auto PtrMultiLight = CreateLight<MultiLight>();
		////�f�t�H���g�̃��C�e�B���O���w��
		//PtrMultiLight->SetDefaultLighting();
		auto PtrView = CreateView<SingleView>();
		//�V���h�E�}�b�v�͎g�p���Ȃ�
		SetShadowmapDraw(false);
	}

	void TitleStage::CreateTitleSprite()
	{
		////�X�e�[�W�ւ̃Q�[���I�u�W�F�N�g�̒ǉ�
		//auto Ptr = AddGameObject<GameObject>();
		//auto PtrTrans = Ptr->GetComponent<Transform>();
		//Quat Qt;
		//Qt.rotationRollPitchYawFromVector(Vec3(0.75, 0, 0));
		//PtrTrans->SetScale(7.0f, 6.0f, 1.0f);
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
		//DrawComp->SetTextureResource(L"TITLE_TX");

		//AddGameObject<TitleSprite>(L"TITLE_TX", false,
		//	Vec2(1000.0f, 600.0f), Vec2(0.0f, 0.0f));
		AddGameObject<Sprite>(L"TITLE_TX", false,
			Vec2(1280.0f, 800.0f), Vec3(0, 0.0f, 0.1f));
	}

	void TitleStage::CreateFadeSprite()
	{
		auto Fade = AddGameObject<SpriteFade>(L"Shadow_TX", true,
			Vec2(840, 600), Vec3(900.0f, 0.0f, 0.1f));
		SetSharedGameObject(L"Shadow_TX", Fade);

	}

	void TitleStage::OnCreate()
	{
		m_SelectFlag = false;
		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateTitleSprite();
		CreateFadeSprite();

	}

	//�X�V
	void TitleStage::OnUpdate() {
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			//A�{�^��
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A&&!m_SelectFlag) {
				auto Fade = GetSharedGameObject<SpriteFade>(L"Shadow_TX");
				Fade->SetActionflag(true);
				PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStageSelect");
				m_SelectFlag = true;
			}
		}
	}

}