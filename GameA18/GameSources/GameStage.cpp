/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------

	//CSV,�X�e�[�W�̍쐬
	void GameStage::Csv()
	{
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		// CSV�t�@�C���̌���,
		//-------------------------------------------------
		//�f�B���N�g���p�X
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);

		//�t�@�C�����̐ݒ�
		//wstring Map = Path + L"Stage_" + Util::IntToWStr(ScenePtr->GetStageNumber()) + L".csv";
		wstring Map = DataDir + L"Stage_" + Util::IntToWStr(ScenePtr->GetStageNumber()) + L".csv";

		//�t�@�C���̎w��
		m_Csv.SetFileName(Map);

		if (!m_Csv.ReadCsv()){
			//�t�@�C�������݂��Ȃ������Ƃ�
			throw BaseException(
				L"�t�@�C����������܂���ł���",
				Map,
				L"�p�X���Ԉ���Ă���or�t�@�C�������݂��Ȃ�\n"
			);
		}
		else {
			//CSV�t�@�C�������݂����Ƃ��Ƀt���O��true�ɂ���
			dataIdFlag = true;
		}

		//Csv��ǂݍ���ł���----------
		int RowNum = 1;//�s�ԍ�
					   //�s���L�������邽�߂̔z��
		vector<wstring>MapVec;
		//�ŏ��̍s��z��֕ۑ�
		m_Csv.GetRowVec(RowNum, MapVec);

		//�p�x�̃��W�A���ϊ��p
		//float DegToRad = 3.14159265f / 180.0f;

		int Wcount = 0;
		//�Ō�܂œǂݍ���
		while (MapVec[0] != L"end"){
			//�����񂪂��������𔻒f
			bool stringflag = false;
			//�|�W�V�����A���[�e�[�V�����A�X�P�[��
			//�I�u�W�F�N�g�����ꂼ�ꐶ������
			//Transform��Csv�t�@�C����ԍ��Ή�
			//--------------------
			//1:PosX 2:PosY 3:PosZ
			//4:RotX 5:RotY 6:RotZ 
			//7:SclX 8:SclY 9:SclZ
			//--------------------
			//_wtof(������𐔒l�Ƃ��ēǂݎ��)
			//�|�W�V�������i�[
			Vec3 Pos = Vec3((float)_wtof(MapVec[1].c_str()), (float)_wtof(MapVec[2].c_str()), (float)_wtof(MapVec[3].c_str())-1.0f);
			//���[�e�[�V�������i�[(���̎��Ƀ��W�A���ɕϊ�)
			Vec3 Rot = Vec3((float)_wtof(MapVec[4].c_str()), (float)_wtof(MapVec[5].c_str()), (float)_wtof(MapVec[6].c_str()))*DegToRad;
			//�X�P�[�����i�[
			Vec3 Scl = Vec3((float)_wtof(MapVec[7].c_str()), (float)_wtof(MapVec[8].c_str()), (float)_wtof(MapVec[9].c_str()));
			//auto UpGroup = GetSharedObjectGroup(L"UpdateObjectGroup");

			if (MapVec[0] == L"Cube"){
				//FixedBox(const Vector3& Scale,const Vector3& Rotation,const Vector3& Position
				//���ꂼ��̒l������
				//�Œ肷��l��ݒ�
				stringflag = true;
				//Scl = Vector3(1, 1, 1);
				//Rot = Vector3(0, 0, 0);
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				auto PtrCube = AddGameObject<WhiteCube>(Scl, Qt, Pos);
			}

			if (MapVec[0] == L"Player"){
				stringflag = true;
				wstring DataDir;
				App::GetApp()->GetDataDirectory(DataDir);
				//�v���[���[�̍쐬
				auto PlayerPtr = AddGameObject<Player>(DataDir + L"Idea\\");
				//�V�F�A�z��Ƀv���C���[��ǉ�
				SetSharedGameObject(L"Player", PlayerPtr);
				Pos.z = 0.0f;
				PlayerPtr->GetComponent<Transform>()->SetPosition(Pos);
				//�J�����̃^�[�Q�b�g�ɐݒ�
				dynamic_pointer_cast<MyCamera>(GetView()->GetTargetCamera())->SetTargetObject(PlayerPtr);
			}

			if (MapVec[0] == L"Goal"){
				stringflag = true;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				auto CubePtr = AddGameObject<Goal>(
					Vec3(0.25f, 0.5f, 0.25f),//�X�P�[��
					Qt,					//�p�x
					Pos					//�|�W�V����
					);
			}
			if (MapVec[0] == L"Key"){
				stringflag = true;
				//Pos.z = -15.0f;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				AddGameObject<KeyItem>(Pos);
			}
			if (!stringflag){
				throw BaseException(
					Util::IntToWStr(RowNum + 1) + L"�s��",
					MapVec[0].c_str(),
					L"�g�p�s�̃I�u�W�F�N�g�ł�"
				);
			}
			//�s�f�[�^�X�V
			RowNum++;
			m_Csv.GetRowVec(RowNum, MapVec);

		}

	}

	void GameStage::CreateFadeOutSprite()
	{
		auto Fade = AddGameObject<SpriteFadeOut>(L"Shadow_TX", true,
			Vec2(50000 / 4, 30000 / 4), Vec3(0.0f, 0.0f, 0.1f));
		SetSharedGameObject(L"FadeOut", Fade);

	}

	void GameStage::CreateFadeSprite()
	{
		auto Fade = AddGameObject<SpriteFade>(L"Shadow_TX", true,
			Vec2(840, 600), Vec3(900.0f, 0.0f, 0.1f));
		SetSharedGameObject(L"FadeIn", Fade);

	}


	//�r���[�ƃ��C�g�̍쐬
	void GameStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrLookAtCamera = ObjectFactory::Create<MyCamera>(GetThis<GameStage>());
		PtrView->SetCamera(PtrLookAtCamera);
		//PtrLookAtCamera->SetEye(Vec3(0.0f, 5.0f, -5.0f));
		PtrLookAtCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
		auto meinLight = PtrMultiLight->GetMainIndex();
		//�e���o�����C�g�̏����p�x��ݒ�
		PtrMultiLight->GetLight(meinLight).SetPositionToDirectional(0.00f, 0.00f, -0.1f);
		//���C�g�̏���������I�u�W�F
		auto ptrMyLight = AddGameObject<LightController>();
		SetSharedGameObject(L"LightController", ptrMyLight);
	}

	void GameStage::CreateWall() {
		//�X�e�[�W�ւ̃Q�[���I�u�W�F�N�g�̒ǉ�
		auto Ptr = AddGameObject<GameObject>();
		auto PtrTrans = Ptr->GetComponent<Transform>();
		Quat Qt;
		Qt.rotationRollPitchYawFromVector(Vec3(0, 0, XM_PIDIV2));
		PtrTrans->SetScale(80.0f, 80.0f, 1.0f);
		PtrTrans->SetQuaternion(Qt);
		PtrTrans->SetPosition(0.0f, 0.0f, 0.5f);

		
		//auto ColPtr = Ptr->AddComponent<CollisionRect>();
		//�`��R���|�[�l���g�̒ǉ�
		auto DrawComp = Ptr->AddComponent<BcPNTStaticDraw>();
		//�`��R���|�[�l���g�Ɍ`��i���b�V���j��ݒ�
		DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		DrawComp->SetFogEnabled(true);
		//�����ɉe���f�肱�ނ悤�ɂ���
		DrawComp->SetOwnShadowActive(true);
		DrawComp->SetTextureResource(L"WallTexture_TX");
		

		Flt4 Color(1.0f, 1.0f, 1.0f, 0.7f);
		DrawComp->SetColorAndAlpha(Color);
	}
	void GameStage::CreateHaveKeys() {
		auto group = GetSharedObjectGroup(L"KeyGroup");
		for (int i = 0; i < group->size(); i++) {
			//���̃O���[�v�ɓ����Ă鐔�A�\������
			auto key = AddGameObject<HaveKeys>((wstring)L"UI_Key_None_TX",i);
			if (i == 0) {
				SetSharedGameObject(L"HaveKey", key);
			}
		}
	}
	void GameStage::CreateEnemy() 
	{
		//�X�e�[�W�ւ̃Q�[���I�u�W�F�N�g�̒ǉ�
		auto Ptr = AddGameObject<GameObject>();
		auto PtrTrans = Ptr->GetComponent<Transform>();
		Quat Qt;
		Qt.rotationRollPitchYawFromVector(Vec3(0, 0, 0));
		PtrTrans->SetScale(1.0f, 1.0f, 2.0f);
		PtrTrans->SetQuaternion(Qt);
		PtrTrans->SetPosition(0.0f, 5.0f, 0.5f);

		//�`��R���|�[�l���g�̒ǉ�
		auto DrawComp = Ptr->AddComponent<BcPNTStaticDraw>();
		//�`��R���|�[�l���g�Ɍ`��i���b�V���j��ݒ�
		DrawComp->SetMeshResource(L"DEFAULT_CUBE");
		DrawComp->SetFogEnabled(true);

	}
	void GameStage::OnCreate() {
		m_ClearFlag = false;
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//��
			CreateWall();
			//�N���G�C�g�������̃O���[�v
			CreateSharedObjectGroup(L"KeyGroup");
			//
			CreateSharedObjectGroup(L"HaveKeysGroup");
			//�G
			CreateEnemy();
			Csv();
			//���̐��ɉ����č�邽�߁A�����ł��Ă���Ăяo��
			CreateHaveKeys();

			//�t�F�[�h
			CreateFadeOutSprite();
			CreateFadeSprite();
		}
		catch (...) {
			throw;
		}
	}
	//�X�V
	void GameStage::OnUpdate() {
		auto Fade = GetSharedGameObject<SpriteFade>(L"FadeIn");
		auto PtrPlayer = GetSharedGameObject<Player>(L"Player");
		if (PtrPlayer->GetGameOverFlag() && PtrPlayer->GetFadeFlag() && !m_ClearFlag) {
			Fade->SetActionflag(true);
			PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOver");
			m_ClearFlag = true;
		}
		if (PtrPlayer->GetGameClearFlag() && PtrPlayer->GetFadeFlag() && !m_ClearFlag) {
			Fade->SetActionflag(true);
			PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
			m_ClearFlag = true;
		}
		////�R���g���[���̎擾
		//auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//if (CntlVec[0].bConnected) {
		//	//A�{�^��
		//	if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
		//		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
		//	}
		//}
	}
	//end basecross
}