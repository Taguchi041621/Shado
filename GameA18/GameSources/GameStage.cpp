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
		wstring Map = DataDir + L"CSV\\" + L"Stage_" + Util::IntToWStr(ScenePtr->GetStageNumber()) + L".csv";

		//�t�@�C���̎w��
		m_Csv.SetFileName(Map);

		if (!m_Csv.ReadCsv()) {
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
		while (MapVec[0] != L"end") {
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
			Vec3 Pos = Vec3((float)_wtof(MapVec[1].c_str()), (float)_wtof(MapVec[2].c_str()), (float)_wtof(MapVec[3].c_str()) - 1.0f);
			//���[�e�[�V�������i�[(���̎��Ƀ��W�A���ɕϊ�)
			Vec3 Rot = Vec3((float)_wtof(MapVec[4].c_str()), (float)_wtof(MapVec[5].c_str()), (float)_wtof(MapVec[6].c_str()))*DegToRad;
			//�X�P�[�����i�[
			Vec3 Scl = Vec3((float)_wtof(MapVec[7].c_str()), (float)_wtof(MapVec[8].c_str()), (float)_wtof(MapVec[9].c_str()));
			//auto UpGroup = GetSharedObjectGroup(L"UpdateObjectGroup");

			if (MapVec[0] == L"Cube") {
				//FixedBox(const Vector3& Scale,const Vector3& Rotation,const Vector3& Position
				//���ꂼ��̒l������
				//�Œ肷��l��ݒ�
				stringflag = true;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				auto PtrCube = AddGameObject<RedCube>(Scl, Qt, Pos,Vec3(0,0,0),false);
			}

			if (MapVec[0] == L"MoveCube") {
				//FixedBox(const Vector3& Scale,const Vector3& Rotation,const Vector3& Position
				//���ꂼ��̒l������
				//�Œ肷��l��ݒ�
				stringflag = true;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				auto PtrCube = AddGameObject<BlueCube>(Scl, Qt, Pos, Vec3(1,0,0), true);
			}
			if (MapVec[0] == L"CustomMoveCube") {
				//���ꂼ��̒l������
				stringflag = true;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				//�ړ���������Ă���
				float MoveX = (float)_wtof(MapVec[10].c_str());
				auto PtrCube = AddGameObject<BlueCube>(Scl, Qt, Pos, Vec3(MoveX, 0, 0), true);
			}
			if (MapVec[0] == L"VMoveCube") {
				//FixedBox(const Vector3& Scale,const Vector3& Rotation,const Vector3& Position
				//���ꂼ��̒l������
				//�Œ肷��l��ݒ�
				stringflag = true;
				//Scl = Vector3(1, 1, 1);
				//Rot = Vector3(0, 0, 0);
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				auto PtrCube = AddGameObject<YellowCube>(Scl, Qt, Pos, Vec3(0, 1, 0), true);
			}
			if (MapVec[0] == L"CustomVMoveCube") {
				//���ꂼ��̒l������
				stringflag = true;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				//�ړ���������Ă���
				float MoveY = (float)_wtof(MapVec[10].c_str());
				auto PtrCube = AddGameObject<YellowCube>(Scl, Qt, Pos, Vec3(0,MoveY, 0), true);
			}
			if (MapVec[0] == L"Player") {
				stringflag = true;
				//z�ʒu���Œ�
				Pos.z = -0.1f;
				//���f�B�A�Ăяo��
				wstring DataDir;
				App::GetApp()->GetDataDirectory(DataDir);
				//�v���[���[�̍쐬
				auto PlayerPtr = AddGameObject<Player>(DataDir + L"Idea\\",Pos);
				//�V�F�A�z��Ƀv���C���[��ǉ�
				SetSharedGameObject(L"Player", PlayerPtr);

			}

			if (MapVec[0] == L"Tutorial") {
				stringflag = true;
				wstring DataDir;
				App::GetApp()->GetDataDirectory(DataDir);
				if (ScenePtr->GetStageNumber() == 1) {
					AddGameObject<Tutorial>(
						DataDir + L"Tutorial\\",
						Vec3(1),
						Vec3(0),
						Vec3(Pos + Vec3(3, 3,1.5)),
						L"R_stick"
						);

					AddGameObject<Sprite3D>(
						Vec3(10, 5, 0),
						Vec3(0),
						Vec3(Pos + Vec3(3, 5.3, 1.5)),
						L"TUTORIAL_LIGHT_MOVE_TX"
						);

					AddGameObject<Tutorial>(
						DataDir + L"Tutorial\\",
						Vec3(1),
						Vec3(0),
						Vec3(Pos + Vec3(-3, 3,1.5)),
						L"L_stick"
						);
					AddGameObject<Sprite3D>(
						Vec3(10, 5, 0),
						Vec3(0),
						Vec3(Pos + Vec3(-3, 5.3, 1.5)),
						L"TUTORIAL_CHARA_MOVE_TX"
						);
				}

				if (ScenePtr->GetStageNumber() == 2) {
					AddGameObject<Tutorial>(
						DataDir + L"Tutorial\\",
						Vec3(1),
						Vec3(0),
						Vec3(Pos + Vec3(3, 3, 1.5)),
						L"L_R"
						);

					AddGameObject<Sprite3D>(
						Vec3(10, 5, 0),
						Vec3(0),
						Vec3(Pos + Vec3(3, 5.3, 1.5)),
						L"TUTORIAL_LIGHT_MOVE_TX"
						);
				}
			}

			if (MapVec[0] == L"Goal") {
				stringflag = true;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				auto CubePtr = AddGameObject<Goal>(Vec3(0.25f, 0.5f, 0.25f),Qt,Pos);
			}
			if (MapVec[0] == L"Key") {
				stringflag = true;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				AddGameObject<KeyItem>(Pos);
			}

			if (MapVec[0] == L"Cannon") {
				//���ꂼ��̒l������
				//�Œ肷��l��ݒ�
				stringflag = true;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				AddGameObject<CannonBase>(Scl, Qt, Pos,CannonBase::CanonDirection::LEFT);
			}
			if (MapVec[0] == L"CannonR") {
				//���ꂼ��̒l������
				//�Œ肷��l��ݒ�
				stringflag = true;
				Quat Qt(Vec3(0.0f, 1.0, 1.0), 0);
				AddGameObject<CannonBase>(Scl, Qt, Pos,CannonBase::CanonDirection::RIGTH);
			}

			if (!stringflag) {
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

	void GameStage::CreatePause() {
		auto Pause = AddGameObject<Sprite>(L"PAUSE_TX", true,
			Vec2(800 * 2, 450 * 2), Vec3(0, -50.0f, 0.2f));
		SetSharedGameObject(L"Pause", Pause);
		Pause->SetDrawActive(false);
		auto WLight = AddGameObject<ScaleChangeSprite>(L"GameOver_WhiteLight_TX", true,
			Vec2(1000, 600), Vec3(-20, 130, 0.1f), 0.3f,true);
		WLight->SetDrawActive(false);

		//�������̃A�j���[�V����
		WLight->AddComponent<Action>();
		WLight->GetComponent<Action>()->AllActionClear();
		SetSharedGameObject(L"WLight", WLight);
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
		//�ǁA�e������ق�
		auto Ptr = AddGameObject<GameObject>();
		auto PtrTrans = Ptr->GetComponent<Transform>();
		Quat Qt;
		Qt.rotationRollPitchYawFromVector(Vec3(0, 0, XM_PIDIV2));
		PtrTrans->SetScale(100.0f, 100.0f, 1.0f);
		PtrTrans->SetQuaternion(Qt);
		PtrTrans->SetWorldPosition(Vec3(0.0f, 0.0f, 0.5f));

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

	//��ʓ��𓮂�����Ă��郉�C�g�C���X�g
	void GameStage::CreateLightSign() {
		AddGameObject<LightSign>();
	}
	//��ʒ[�̂��
	void GameStage::CreateMoveEnd() {
		auto frame = AddGameObject<Sprite>(L"Shadowframe_TX", true, Vec2(1330.0f, 870.0f), Vec3(0.3f, 0.0f, 0));
		frame->GetComponent<Action>()->AllActionClear();
		frame->SetActionflag(true);
	}
	
	//���C�g����̃I�u�W�F�N�g
	void GameStage::CreateLightObject() {
		auto PtrLight = AddGameObject<StageLight>(
			Vec3(0.0f, 0.0, -35.0f),
			Vec3(1.5f, 0.0f, 0.0f),
			Vec3(5.0f, 1.0f, 5.0f));
	}

	void GameStage::OnCreate() {
		m_ClearFlag = false;
		NowSelect = 0;
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//��
			CreateWall();
			//�N���G�C�g�������̃O���[�v
			CreateSharedObjectGroup(L"KeyGroup");
			//���C�g�̈ʒu��m�点�鉉�o
			CreateLightSign();
			//���C�g�̋쓮���E��������
			CreateMoveEnd();
			//���C�g����̃I�u�W�F�N�g
			CreateLightObject();
			Csv();
			CreatePause();
			//�t�F�[�h
			CreateFadeOutSprite();
			CreateFadeSprite();
			auto Target = AddGameObject<TargetObjectToStart>();
			dynamic_pointer_cast<MyCamera>(GetView()->GetTargetCamera())->SetTargetObject(Target);
		}
		catch (...) {
			throw;
		}
	}
	//�X�V
	void GameStage::OnUpdate() {
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		auto Fade = GetSharedGameObject<SpriteFade>(L"FadeIn");
		auto PtrPlayer = GetSharedGameObject<Player>(L"Player");

		auto Pause = GetSharedGameObject<Sprite>(L"Pause");
		auto WLight = GetSharedGameObject<ScaleChangeSprite>(L"WLight");

		auto Time = App::GetApp()->GetElapsedTime();
		ThumbTimer += Time;
		m_ScaleTimer += Time;
		//���񂾂Ƃ�
		if (PtrPlayer->GetGameOverFlag() && PtrPlayer->GetFadeFlag() && !m_ClearFlag) {
			Fade->SetActionflag(true);
			//���X�|�[��
			ScenePtr->SetRespawnFlag(true);
			PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
			m_ClearFlag = true;
		}
		//�N���A�����Ƃ�
		if (PtrPlayer->GetGameClearFlag() && PtrPlayer->GetFadeFlag() && !m_ClearFlag) {
			Fade->SetActionflag(true);
			PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
			m_ClearFlag = true;
		}

		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if ((CntlVec[0].wButtons&XINPUT_GAMEPAD_START) && (CntlVec[0].wButtons&XINPUT_GAMEPAD_BACK)) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleStage");
		}
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START && !ScenePtr->GetPauseFlag() && !PtrPlayer->GetGameClearFlag() && ScenePtr->GetStartFlag()) {
				PtrPlayer->SetUpdateActive(false);
				ScenePtr->SetPauseFlag(true);
				Pause->SetDrawActive(true);
				WLight->SetDrawActive(true);
			}
			else	if ((CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START || CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
				&& ScenePtr->GetPauseFlag()) {
				PtrPlayer->SetUpdateActive(true);
				ScenePtr->SetPauseFlag(false);

				Pause->SetDrawActive(false);
				WLight->SetDrawActive(false);
			}
		}


		if (ScenePtr->GetPauseFlag()) {
			if (ThumbTimer > 0.5f) {
				ThumbFlag = true;
			}
			if (!SelectFlag) {//�R���g���[���[�̏���
				if (CntlVec[0].fThumbLY < -0.5f) {
					if (ThumbFlag) {
						NowSelect += 1;
						ThumbTimer = 0.0f;
						ThumbFlag = false;
					}
				}
				else if (CntlVec[0].fThumbLY > 0.5f) {
					if (ThumbFlag) {
						NowSelect -= 1;
						ThumbTimer = 0.0f;
						ThumbFlag = false;
					}
				}
				//�㉺�[�𒴂����甽�Α��̒[�ɍs��
				if (NowSelect < 0) {
					NowSelect = 2;
				}
				if (NowSelect > 2) {
					NowSelect = 0;
				}
			}

			switch (NowSelect) {//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
			case 0:
				WLight->GetComponent<Action>()->Stop();
				WLight->GetComponent<Action>()->AllActionClear();
				WLight->GetComponent<Action>()->
					AddMoveTo(0.2f, Vec3(-20, 130, 0.1f));
				WLight->GetComponent<Action>()->Run();
				break;
			case 1:
				WLight->GetComponent<Action>()->Stop();
				WLight->GetComponent<Action>()->AllActionClear();
				WLight->GetComponent<Action>()->
					AddMoveTo(0.2f, Vec3(-20, -30, 0.1f));
				WLight->GetComponent<Action>()->Run();
				break;
			case 2:
				WLight->GetComponent<Action>()->Stop();
				WLight->GetComponent<Action>()->AllActionClear();
				WLight->GetComponent<Action>()->
					AddMoveTo(0.2f, Vec3(-20, -170, 0.1f));
				WLight->GetComponent<Action>()->Run();
				break;
			}

			//A�{�^��
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A && !SelectFlag) {
				SelectFlag = true;
				switch (NowSelect) {//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
				case 0:
					PtrPlayer->SetUpdateActive(true);
					ScenePtr->SetPauseFlag(false);
					Pause->SetDrawActive(false);
					WLight->SetDrawActive(false);
					SelectFlag = false;
					break;
				case 1:
					ScenePtr->SetRespawnFlag(true);
					ScenePtr->SetPauseFlag(false);
					Fade->SetActionflag(true);
					PostEvent(0.8f, GetThis<ObjectInterface>(), ScenePtr, L"ToGameStage");
					break;
				case 2:
					ScenePtr->SetPauseFlag(false);
					Fade->SetActionflag(true);
					PostEvent(0.8f, GetThis<ObjectInterface>(), ScenePtr, L"ToStageSelect");
					break;
				}
			}
		}
	}
	//end basecross
}
	

		