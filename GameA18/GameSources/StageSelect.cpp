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
		PtrCamera->SetEye(Vec3(0.0f, 0.0f, -10.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
		//auto PtrView = CreateView<SingleView>();
		////�V���h�E�}�b�v�͎g�p���Ȃ�
		//SetShadowmapDraw(false);

	}

	void StageSelect::CreateTitleSprite()
	{
		////�X�e�[�W�ւ̃Q�[���I�u�W�F�N�g�̒ǉ�
		//auto Ptr = AddGameObject<GameObject>();
		//auto PtrTrans = Ptr->GetComponent<Transform>();
		//Quat Qt;
		//Qt.rotationRollPitchYawFromVector(Vec3(0.60, 0, 0));
		//PtrTrans->SetScale(5.0f, 4.0f, 1.0f);
		//PtrTrans->SetQuaternion(Qt);
		//PtrTrans->SetPosition(0.0f, -0.5f, 0.0f);

		//auto ColPtr = Ptr->AddComponent<CollisionRect>();
		////�`��R���|�[�l���g�̒ǉ�
		//auto DrawComp = Ptr->AddComponent<BcPNTStaticDraw>();
		////�`��R���|�[�l���g�Ɍ`��i���b�V���j��ݒ�
		//DrawComp->SetMeshResource(L"DEFAULT_SQUARE");
		//DrawComp->SetFogEnabled(true);
		////�����ɉe���f�肱�ނ悤�ɂ���
		//DrawComp->SetOwnShadowActive(true);

		////�`��R���|�[�l���g�e�N�X�`���̐ݒ�
		//DrawComp->SetTextureResource(L"SELECT_TX");
		float a = 0;
		for (int i = 1; i <= 2; i++) {
			auto BG = AddGameObject<Sprite>(L"STAGESELECT_BG_TX", false,
				Vec2(1280.0f, 800.0f), Vec3(0 +a, 0.0f, 0.2f));
			a += 1280;
			BG->AddComponent<Action>();
			SetSharedGameObject(L"BG" + Util::IntToWStr(i), BG);
		}
		AddGameObject<Sprite>(L"SELECT_TEXT_TX", true,
			Vec2(960, 200/2), Vec3(0, 330, 0.1f));
		AddGameObject<Sprite>(L"TITLE_SHADOW_TX", true,
			Vec2(1280.0f*1.2, 800.0f*1.2), Vec3(0, 0, 0.1f));
	}

	void StageSelect::CreateFadeOutSprite()
	{
		auto Fade = AddGameObject<SpriteFadeOut>(L"Shadow_TX", true,
			Vec2(50000 / 4, 30000 / 4), Vec3(0.0f, 0.0f, 0.0f));
		SetSharedGameObject(L"FadeOut", Fade);

	}

	void StageSelect::CreateFadeSprite()
	{
		auto Fade = AddGameObject<SpriteFade>(L"Shadow_TX", true,
			Vec2(840, 600), Vec3(900.0f, 0.0f, 0.0f));
		SetSharedGameObject(L"FadeIn", Fade);
	}
	//�h�A�����
	void StageSelect::CreateDoor() {
		float interval = 0;
		float hight = 0.88f;
		for (int i = 1; i <= m_MaxStageNumber; i++){
			//�h�A
			wstring DataDir;
			App::GetApp()->GetDataDirectory(DataDir);
			auto Door = AddGameObject<StageSelectDoor>(
				DataDir + L"StageSelectDoor\\",
				Vec3(0.4f, 0.4f, 0.1f),
				Vec3(-5.5f + interval, hight, 0),
				Vec3(0),
				Util::IntToWStr(i)
				);
			interval += 2.2f;
			SetSharedGameObject(L"Door" + Util::IntToWStr(i), Door);
			if (i % (m_MaxStageNumber / 2) == 0) {
				interval = 0;
				hight = -2.72f;
			}
		}
		//��ʉ��́�
		//AddGameObject<ScaleChangeSprite>(L"ARROW_TX", true,
		//	Vec2(1000.0f, 1000), Vec3(500, -90.0f, 0.0f), 1.0f, true);

	}
	void StageSelect::StageNumberSprite(){
		float intervalNum = 0;
		float Paragraph = 140.0f;
		shared_ptr<ScoreSprite> Number;
		for (int i = 1; i <= 12; i++) {
			//����
			if (i < 10) {
				Number = AddGameObject<ScoreSprite>(1,
					L"NUMBER_TX",
					true,
					Vec2(50.0f, 50.0f),
					Vec3(-512.0f + intervalNum, Paragraph, 0.0f),
					i,
					false, 0.3f);
			}
			else {
				Number = AddGameObject<ScoreSprite>(2,
					L"NUMBER_TX",
					true,
					Vec2(50.0f, 50.0f),
					Vec3(-512.0f + intervalNum, -210.0f, 0.0f),
					i,
					false, 0.3f);
			}
			SetSharedGameObject(L"ScoreSprite" + Util::IntToWStr(i), Number);
			if (i % 6 == 0) {
				Paragraph = -210.0f;
				intervalNum = 0;
			}
			intervalNum += 210;
		}

		//����
		//for (int i = 1; i <= m_MaxStageNumber; i++) {
		//	intervalNum = 200 * (i-1);
		//	if (i < 10) {
		//		Number = AddGameObject<ScoreSprite>(1,
		//			L"NUMBER_TX",
		//			true,
		//			Vec2(50.0f, 50.0f),
		//			Vec3(-530.0f + intervalNum, 120.0f, -5.0f),
		//			i,
		//			false, 0.3f);
		//	}
		//	else {
		//		Number = AddGameObject<ScoreSprite>(2,
		//			L"NUMBER_TX",
		//			true,
		//			Vec2(100.0f, 100.0f),
		//			Vec3(-10.0f + intervalNum, -40.0f, 0.0f),
		//			i,
		//			false, 0.3f);
		//	}
		//	SetSharedGameObject(L"ScoreSprite" + Util::IntToWStr(i), Number);
			//	Number->AddComponent<Action>();
			//	if (i == m_StageNumber)
			//	{
			//		//Number->SetScaleChangeFlag(true);
			//	}
		//}

	}
	void StageSelect::CreateFrame() {
		auto frame = AddGameObject<ScaleChangeSprite>(L"pane_TX",true,
			Vec2(150.0f,280.0f),Vec3(-512.0f, 100.0f, 0.0f),1.0f,true);
		SetSharedGameObject(L"frame",frame);
	}

	void StageSelect::OnCreate()
	{
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		m_MaxStageNumber = 12;
		m_SelectFlag = true;
		m_StageNumber = ScenePtr->GetStageNumber();
		m_CoolTime = 0;
		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateTitleSprite();
		CreateDoor();
		//StageNumberSprite();
		//CreateFrame();
		CreateFadeOutSprite();
		CreateFadeSprite();
	}

	//�X�V
	void StageSelect::OnUpdate() {
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		auto Time = App::GetApp()->GetElapsedTime();
		if (onectrl)
		{
			m_CoolTime += Time;
			if (m_CoolTime >= 0.2f){
				onectrl = false;
				m_CoolTime = 0;
			}
		}
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (m_SelectFlag) {
			if (CntlVec[0].bConnected) {
				//���X�e�B�b�N������
				if (CntlVec[0].fThumbLX < -0.5) {
					if (onectrl == false){
						if (!(m_StageNumber == 1)) {
							//for (int i = 1; i <= m_MaxStageNumber; i++) {
							//	auto Door = GetSharedGameObject<ScaleChangeSprite>(L"Door" + Util::IntToWStr(i));
							//	auto Number = GetSharedGameObject<ScoreSprite>(L"ScoreSprite" + Util::IntToWStr(i));
							//	Door->GetComponent<Action>()->AllActionClear();
							//	Number->GetComponent<Action>()->AllActionClear();
							//	Door->GetComponent<Action>()->AddMoveBy(0.3f, Vec3(380.0f, 0, 0));
							//	Number->GetComponent<Action>()->AddMoveBy(0.3f, Vec3(380.0f, 0, 0));
							//	Door->GetComponent<Action>()->Run();
							//	Number->GetComponent<Action>()->Run();
							//	if (i == m_StageNumber - 1) {
							//		Door->SetScaleChangeFlag(true);
							//		//Number->SetScaleChangeFlag(true);
							//	}
							//	else {
							//		Door->SetScaleChangeFlag(false);
							//		Number->SetScaleChangeFlag(false);
							//	}
							//}
							m_StageNumber -= 1;

							if (m_StopNowMusic != L""){
								m_AudioObjectPtr->Stop(m_StopNowMusic);
							}
							wstring DataDir;
							App::GetApp()->GetDataDirectory(DataDir);

							m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
							m_AudioObjectPtr->AddAudioResource(L"se2");
							m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.45f);
							SetNowMusic(L"se2");
							/*for (int i = 1; i <= 10; i++) {
							auto BG = GetSharedGameObject<Sprite>(L"BG" + Util::IntToWStr(i));
							BG->GetComponent<Action>()->AllActionClear();
							BG->GetComponent<Action>()->AddMoveBy(0.3f, Vec3(380.0f, 0, 0));
							BG->GetComponent<Action>()->Run();
						}*/
							//1�񂾂������t���O
							onectrl = true;
						}
					}
				}
				//���X�e�B�b�N�E����
				else if (CntlVec[0].fThumbLX > 0.5) {
					if (onectrl == false){
						if (!(m_StageNumber == m_MaxStageNumber)) {
							//for (int i = 1; i <= m_MaxStageNumber; i++) {
							//	auto Door = GetSharedGameObject<ScaleChangeSprite>(L"Door" + Util::IntToWStr(i));
							//	auto Number = GetSharedGameObject<ScoreSprite>(L"ScoreSprite" + Util::IntToWStr(i));
							//	Door->GetComponent<Action>()->AllActionClear();
							//	Number->GetComponent<Action>()->AllActionClear();
							//	Door->GetComponent<Action>()->AddMoveBy(0.3f, Vec3(-380.0f, 0, 0));
							//	Number->GetComponent<Action>()->AddMoveBy(0.3f, Vec3(-380.0f, 0, 0));
							//	Door->GetComponent<Action>()->Run();
							//	Number->GetComponent<Action>()->Run();
							//	if (i == m_StageNumber + 1) {
							//		Door->SetScaleChangeFlag(true);
							//		//Number->SetScaleChangeFlag(true);
							//	}
							//	else {
							//		Door->SetScaleChangeFlag(false);
							//		Number->SetScaleChangeFlag(false);
							//	}
							//}

							m_StageNumber += 1;

							if (m_StopNowMusic != L""){
								m_AudioObjectPtr->Stop(m_StopNowMusic);
							}
							wstring DataDir;
							App::GetApp()->GetDataDirectory(DataDir);

							m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
							m_AudioObjectPtr->AddAudioResource(L"se2");
							m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.45f);
							SetNowMusic(L"se2");
							/*	for (int i = 1; i <= 10; i++) {
								auto BG = GetSharedGameObject<Sprite>(L"BG" + Util::IntToWStr(i));
								BG->GetComponent<Action>()->AllActionClear();
								BG->GetComponent<Action>()->AddMoveBy(0.3f, Vec3(-380.0f, 0, 0));
								BG->GetComponent<Action>()->Run();
							}*/
							//1�񂾂������t���O
							onectrl = true;
						}

					}
				}

				/*else
				{
					onectrl = false;
				}*/
				//���X�e�B�b�N������
				if (CntlVec[0].fThumbLY < -0.5) {
					if (onectrl == false){
						//��̒i���牺�̒i�֍s��
						if (m_StageNumber <= (m_MaxStageNumber/2)) {
							m_StageNumber += (m_MaxStageNumber/2);

							if (m_StopNowMusic != L""){
								m_AudioObjectPtr->Stop(m_StopNowMusic);
							}
							wstring DataDir;
							App::GetApp()->GetDataDirectory(DataDir);

							m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
							m_AudioObjectPtr->AddAudioResource(L"se2");
							m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.45f);
							SetNowMusic(L"se2");
							//1�񂾂�����
							onectrl = true;
						}
						else if (m_StageNumber > (m_MaxStageNumber / 2)) {
							m_StageNumber -= (m_MaxStageNumber / 2);

							if (m_StopNowMusic != L""){
								m_AudioObjectPtr->Stop(m_StopNowMusic);
							}
							wstring DataDir;
							App::GetApp()->GetDataDirectory(DataDir);

							m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
							m_AudioObjectPtr->AddAudioResource(L"se2");
							m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.45f);
							SetNowMusic(L"se2");

							onectrl = true;
						}

					}
				}
				//���X�e�B�b�N�����
				if (CntlVec[0].fThumbLY > 0.5) {
					if (onectrl == false){
						if (m_StageNumber <= (m_MaxStageNumber/2)) {
							m_StageNumber += (m_MaxStageNumber/2);


							if (m_StopNowMusic != L""){
								m_AudioObjectPtr->Stop(m_StopNowMusic);
							}
							wstring DataDir;
							App::GetApp()->GetDataDirectory(DataDir);

							m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
							m_AudioObjectPtr->AddAudioResource(L"se2");
							m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.45f);
							SetNowMusic(L"se2");

							onectrl = true;
						}
						else if (m_StageNumber > (m_MaxStageNumber / 2)) {
							m_StageNumber -= (m_MaxStageNumber / 2);


							if (m_StopNowMusic != L""){
								m_AudioObjectPtr->Stop(m_StopNowMusic);
							}
							wstring DataDir;
							App::GetApp()->GetDataDirectory(DataDir);

							m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
							m_AudioObjectPtr->AddAudioResource(L"se2");
							m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.45f);
							SetNowMusic(L"se2");

							onectrl = true;
						}

					}
				}

				/*if (m_StageNumber < 0) {
					m_StageNumber = m_MaxStageNumber;
				}
				else if (m_StageNumber > m_MaxStageNumber) {
					m_StageNumber = 0;
				}*/
				//A�{�^��
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
					if (m_StopNowMusic != L""){
						m_AudioObjectPtr->Stop(m_StopNowMusic);
					}
					wstring DataDir;
					App::GetApp()->GetDataDirectory(DataDir);

					m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
					m_AudioObjectPtr->AddAudioResource(L"opendoor");
					m_AudioObjectPtr->Start(L"opendoor", XAUDIO2_NO_LOOP_REGION, 0.45f);
					SetNowMusic(L"opendoor");

					m_SelectFlag = false;
					ScenePtr->SetRespawnFlag(false);
					for (int i = 1; i <= m_MaxStageNumber; i++) {
						//auto num = GetSharedGameObject<ScoreSprite>(L"ScoreSprite" + Util::IntToWStr(i));
						//RemoveGameObject<ScoreSprite>(num);
						auto Door = GetSharedGameObject<StageSelectDoor>(L"Door" + Util::IntToWStr(i));
						//�I��ł�X�e�[�W��
						if (i == m_StageNumber) {
							//�J���A�j���[�V�����𗬂�
							Door->Open();
							//�h�A���J���Ă���V�[���ڍs���邽�߂�2.8�b
							PostEvent(2.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
						}
					}
				}
			}
			ScenePtr->SetStageNumber(m_StageNumber);
			for (int i = 1; i <= m_MaxStageNumber; i++) {
				auto Door = GetSharedGameObject<StageSelectDoor>(L"Door" + Util::IntToWStr(i));
				if (i == m_StageNumber) {
					Door->SetSelectFlag(true);
				}
				else
				{
					Door->SetSelectFlag(false);
				}
//<<<<<<< HEAD
//=======
//				wstring DataDir;
//				//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
//				//App::GetApp()->GetAssetsDirectory(DataDir);
//				//�e�Q�[���͈ȉ��̂悤�Ƀf�[�^�f�B���N�g�����擾���ׂ�
//				App::GetApp()->GetDataDirectory(DataDir);
//
//				m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
//				m_AudioObjectPtr->AddAudioResource(L"opendoor");
//				m_AudioObjectPtr->Start(L"opendoor", XAUDIO2_NO_LOOP_REGION, 0.1f);
//				SetNowMusic(L"opendoor");
//
//				auto FadeIn = GetSharedGameObject<SpriteFade>(L"FadeIn");
//				FadeIn->SetActionflag(true);
//				m_SelectFlag = false;
//				ScenePtr->SetRespawnFlag(false);
//				PostEvent(0.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
//>>>>>>> 461c6d109ef9a2ea6a24272b2be17499d07851d5
			}
		}
	}

	//--------------------------------------------------------------------------------------
	//Door
	//--------------------------------------------------------------------------------------
	StageSelectDoor::StageSelectDoor(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
		const Vec3& Scale, const Vec3& Position, const Vec3& Rotation)
		: SS5ssae(StagePtr, BaseDir, L"StageSelectDoor.ssae", L"SELECT"),
		m_Scale(Scale), m_Position(Position), m_Rotation(Rotation), m_ScaleZ(0.05f), m_SelectFlag(false)
	{
		m_ToAnimeMatrix.affineTransformation(
			Vec3(0.2f, 0.2f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.0f, 0.0f, 0.0f)
		);
	}
	StageSelectDoor::StageSelectDoor(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
		const Vec3& Scale, const Vec3& Position, const Vec3& Rotation,const wstring DoorNum)
		: SS5ssae(StagePtr, BaseDir, L"StageSelectDoor.ssae", L"SELECT_" + DoorNum),
		m_Scale(Scale), m_Position(Position), m_Rotation(Rotation), m_ScaleZ(0.05f), m_SelectFlag(false),m_DoorNum(DoorNum)
	{
		m_ToAnimeMatrix.affineTransformation(
			Vec3(0.2f, 0.2f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.0f, 0.0f, 0.0f)
			);
	}

	StageSelectDoor::~StageSelectDoor() {}
	//������
	void StageSelectDoor::OnCreate() {

		//�X�P�[����Z���Œ�̑傫����
		m_Scale.z = m_ScaleZ;
		auto PtrTransform = GetComponent<Transform>();
		//�e�̃X�P�[��,�p�x,�|�W�V�����̐ݒ�
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(m_Position);

		//�e�N���X�̃N���G�C�g���Ă�
		SS5ssae::OnCreate();
		//�l�͕b������̃t���[����
		SetFps(30);
		//�A�j���[�V�����̃��[�v�ݒ�
		SetLooped(false);
		//�A�j���[�V�����ɂ����郁�g���b�N�X�̐ݒ�
		SetToAnimeMatrix(m_ToAnimeMatrix);
		//SetAlphaActive(true);
		//auto PtrCol = AddComponent<CollisionObb>();
		//PtrCol->SetDrawActive(true);
		UpdateAnimeTime(0);
		SetSpriteDraw(true);
	}

	//�ω�
	void StageSelectDoor::OnUpdate() {
		float ElapsedTime = 0;
		if (m_OpenFlag) {
			ElapsedTime = App::GetApp()->GetElapsedTime();
			if (IsAnimeEnd()) {
				auto FadeIn = GetStage()->GetSharedGameObject<SpriteFade>(L"FadeIn");
				FadeIn->SetActionflag(true);
			}
		}
		else if (m_SelectFlag) {
			ElapsedTime = App::GetApp()->GetElapsedTime();
			ChangeAnimation(L"SELECT_" + m_DoorNum);
			SetLooped(true);
		}
		else{
			ElapsedTime = 0;
			ChangeAnimation(L"OPEN_"+ m_DoorNum);
		}
		UpdateAnimeTime(ElapsedTime);
	}

	void StageSelectDoor::OnUpdate2() {
	}

	void StageSelectDoor::Open() {
		m_OpenFlag = true;
		ChangeAnimation(L"OPEN_" + m_DoorNum);
		SetLooped(false);
	}
}
