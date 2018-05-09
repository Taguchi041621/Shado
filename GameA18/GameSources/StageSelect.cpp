#include "stdafx.h"
#include "Project.h"

namespace basecross
{

void StageSelect::CreateViewLight()
{
	auto PtrView = CreateView<SingleView>();
	//�r���[�̃J�����̐ݒ�
	auto PtrCamera = ObjectFactory::Create<Camera>();
	PtrView->SetCamera(PtrCamera);
	PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
	PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
	//�}���`���C�g�̍쐬
	auto PtrMultiLight = CreateLight<MultiLight>();
	//�f�t�H���g�̃��C�e�B���O���w��
	PtrMultiLight->SetDefaultLighting();

}

void StageSelect::CreateTitleSprite()
{
	//�X�e�[�W�ւ̃Q�[���I�u�W�F�N�g�̒ǉ�
	auto Ptr = AddGameObject<GameObject>();
	auto PtrTrans = Ptr->GetComponent<Transform>();
	Quat Qt;
	Qt.rotationRollPitchYawFromVector(Vec3(0.60, 0, 0));
	PtrTrans->SetScale(5.0f, 4.0f, 1.0f);
	PtrTrans->SetQuaternion(Qt);
	PtrTrans->SetPosition(0.0f, -0.5f, 0.0f);

	auto ColPtr = Ptr->AddComponent<CollisionRect>();
	//�`��R���|�[�l���g�̒ǉ�
	auto DrawComp = Ptr->AddComponent<BcPNTStaticDraw>();
	//�`��R���|�[�l���g�Ɍ`��i���b�V���j��ݒ�
	DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
	DrawComp->SetFogEnabled(true);
	//�����ɉe���f�肱�ނ悤�ɂ���
	DrawComp->SetOwnShadowActive(true);

	//�`��R���|�[�l���g�e�N�X�`���̐ݒ�
	DrawComp->SetTextureResource(L"SELECT_TX");

}

void StageSelect::OnCreate()
{
	CreateViewLight();
	//�X�v���C�g�̍쐬
	CreateTitleSprite();

}

//�X�V
void StageSelect::OnUpdate() {
	//�R���g���[���̎擾
	auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
	if (CntlVec[0].bConnected) {
		//A�{�^��
		if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
		}
	}

}

}