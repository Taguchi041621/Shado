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
	}

	void StageSelect::CreateTitleSprite() {
		////�`��R���|�[�l���g�e�N�X�`���̐ݒ�
		AddGameObject<Sprite>(L"STAGESELECT_BG_TX", false,
			Vec2(1280.0f, 800.0f), Vec3(0, 0.0f, 0.2f));

		AddGameObject<Sprite>(L"SELECT_TEXT_TX", true,
			Vec2(960, 200 / 2), Vec3(0, 330, 0.1f));
		//��ʒ[�̉e
		AddGameObject<Sprite>(L"TITLE_SHADOW_TX", true,
			Vec2(1280.0f*1.2, 800.0f*1.2), Vec3(0, 0, 0.1f));
	}

	void StageSelect::CreateFadeOutSprite() {
		auto Fade = AddGameObject<SpriteFadeOut>(L"Shadow_TX", true,
			Vec2(12500, 7500), Vec3(0.0f, 0.0f, 0.0f));
		SetSharedGameObject(L"FadeOut", Fade);
	}

	void StageSelect::CreateFadeSprite(){
		auto Fade = AddGameObject<SpriteFade>(L"Shadow_TX", true,
			Vec2(840, 600), Vec3(900.0f, 0.0f, 0.0f));
			SetSharedGameObject(L"FadeIn", Fade);
	}
	//�h�A�����
	void StageSelect::CreateDoor() {
		float interval = 0;
		float hight = 0.88f;
		for (int i = 1; i <= m_MaxStageNumber; i++) {
			//�h�A
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
	}
	void StageSelect::StageNumberSprite() {
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
	}
	void StageSelect::CreateFrame() {
		auto frame = AddGameObject<ScaleChangeSprite>(L"pane_TX", true,
			Vec2(150.0f, 280.0f), Vec3(-512.0f, 100.0f, 0.0f), 1.0f, true);
		SetSharedGameObject(L"frame", frame);
	}

	void StageSelect::OnCreate()
	{
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		m_MaxStageNumber = 12;
		m_SelectFlag = true;
		m_StageNumber = ScenePtr->GetStageNumber();
		m_CoolTime = 0;
		//�f�B���N�g���擾
		App::GetApp()->GetDataDirectory(DataDir);
		//��
		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
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
		shared_ptr<StageSelectDoor> Door;
		if (onectrl) {
			m_CoolTime += App::GetApp()->GetElapsedTime();
			if (m_CoolTime >= 0.2f) {
				onectrl = false;
				m_CoolTime = 0;
			}
		}
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if ((CntlVec[0].wButtons&XINPUT_GAMEPAD_START) && (CntlVec[0].wButtons&XINPUT_GAMEPAD_BACK)) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), ScenePtr, L"ToTitleStage");
		}
		if (m_SelectFlag) {
			if (CntlVec[0].bConnected) {
				//���X�e�B�b�N������
				if (CntlVec[0].fThumbLX < -0.5) {
					if (onectrl == false) {
						if (!(m_StageNumber == 1)) {
							m_StageNumber -= 1;

							if (m_StopNowMusic != L"") {
								m_AudioObjectPtr->Stop(m_StopNowMusic);
							}
							m_AudioObjectPtr->AddAudioResource(L"se2");
							m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.45f);
							SetNowMusic(L"se2");
						//1�񂾂������t���O
							onectrl = true;
						}
					}
				}
				//���X�e�B�b�N�E����
				else if (CntlVec[0].fThumbLX > 0.5) {
					if (onectrl == false) {
						if (!(m_StageNumber == m_MaxStageNumber)) {

							m_StageNumber += 1;

							if (m_StopNowMusic != L"") {
								m_AudioObjectPtr->Stop(m_StopNowMusic);
							}
							m_AudioObjectPtr->AddAudioResource(L"se2");
							m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.45f);
							SetNowMusic(L"se2");
							//1�񂾂������t���O
							onectrl = true;
						}
					}
				}
				//���X�e�B�b�N������
				if (CntlVec[0].fThumbLY < -0.5) {
					if (onectrl == false) {
						//��̒i���牺�̒i�֍s��
						if (m_StageNumber <= (m_MaxStageNumber / 2)) {
							m_StageNumber += (m_MaxStageNumber / 2);

							if (m_StopNowMusic != L"") {
								m_AudioObjectPtr->Stop(m_StopNowMusic);
							}
							m_AudioObjectPtr->AddAudioResource(L"se2");
							m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.45f);
							SetNowMusic(L"se2");
							//1�񂾂�����
							onectrl = true;
						}
						//���̒i�����ɍs��
						else if (m_StageNumber > (m_MaxStageNumber / 2)) {
							m_StageNumber -= (m_MaxStageNumber / 2);

							if (m_StopNowMusic != L"") {
								m_AudioObjectPtr->Stop(m_StopNowMusic);
							}
							m_AudioObjectPtr->AddAudioResource(L"se2");
							m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.45f);
							SetNowMusic(L"se2");

							onectrl = true;
						}

					}
				}
				//���X�e�B�b�N�����
				if (CntlVec[0].fThumbLY > 0.5) {
					if (onectrl == false) {
						if (m_StageNumber <= (m_MaxStageNumber / 2)) {
							m_StageNumber += (m_MaxStageNumber / 2);

							if (m_StopNowMusic != L"") {
								m_AudioObjectPtr->Stop(m_StopNowMusic);
							}
							m_AudioObjectPtr->AddAudioResource(L"se2");
							m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.45f);
							SetNowMusic(L"se2");

							onectrl = true;
						}
						else if (m_StageNumber > (m_MaxStageNumber / 2)) {
							m_StageNumber -= (m_MaxStageNumber / 2);

							if (m_StopNowMusic != L"") {
								m_AudioObjectPtr->Stop(m_StopNowMusic);
							}
							m_AudioObjectPtr->AddAudioResource(L"se2");
							m_AudioObjectPtr->Start(L"se2", XAUDIO2_NO_LOOP_REGION, 0.45f);
							SetNowMusic(L"se2");

							onectrl = true;
						}
					}
				}

				//A�{�^��
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
					if (m_StopNowMusic != L"") {
						m_AudioObjectPtr->Stop(m_StopNowMusic);
					}
					m_AudioObjectPtr->AddAudioResource(L"opendoor");
					m_AudioObjectPtr->Start(L"opendoor", XAUDIO2_NO_LOOP_REGION, 0.45f);
					SetNowMusic(L"opendoor");

					m_SelectFlag = false;
					ScenePtr->SetRespawnFlag(false);
					for (int i = 1; i <= m_MaxStageNumber; i++) {
						Door = GetSharedGameObject<StageSelectDoor>(L"Door" + Util::IntToWStr(i));
						//�I��ł�X�e�[�W��
						if (i == m_StageNumber) {
							//�J���A�j���[�V�����𗬂�
							Door->Open();
							//�h�A���J���Ă���V�[���ڍs���邽�߂�2.8�b
							PostEvent(2.8f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
						}
						Door->SetRemoveFlag(true);
					}
				}
				for (int i = 1; i <= m_MaxStageNumber; i++) {
					Door = GetSharedGameObject<StageSelectDoor>(L"Door" + Util::IntToWStr(i));
					if (i == m_StageNumber) {
						Door->SetSelectFlag(true);
					}
					else {
						Door->SetSelectFlag(false);
					}
					Door->StyleChange();
				}
				//���̃X�e�[�W���V�[���Ɏ�������
				ScenePtr->SetStageNumber(m_StageNumber);
			}
		}
	}

	//--------------------------------------------------------------------------------------
	//Door
	//--------------------------------------------------------------------------------------
	StageSelectDoor::StageSelectDoor(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
		const Vec3& Scale, const Vec3& Position, const Vec3& Rotation, const wstring& DoorNum)
		: SS5ssae(StagePtr, BaseDir, L"StageSelectDoor.ssae", L"SELECT_" + DoorNum),
		m_Scale(Scale), m_Position(Position), m_Rotation(Rotation), m_ScaleZ(0.05f), m_SelectFlag(false), m_DoorNum(DoorNum){
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
		UpdateAnimeTime(0);
		SetSpriteDraw(true);
	}

	//�ω�
	void StageSelectDoor::OnUpdate() {
		float ElapsedTime = 0;
		//�J�[�\���������̃h�A�ɂ��鎞
		if (m_SelectFlag && !m_OpenFlag) {
			ElapsedTime += App::GetApp()->GetElapsedTime();
			auto pos = GetComponent<Transform>()->GetWorldPosition();
			auto sca = GetComponent<Transform>()->GetScale();
			if (sca.x >= 0.5f) {
				deflection = -0.001f;
			}
			if(sca.x < 0.4) {
				deflection = 0.001f;
			}
			//�h�A�̑傫���𑝌����āA����ɍ��킹�č�����ς���
			pos.y += deflection*3.0f;
			sca.x += deflection;
			sca.y += deflection;
			//�K��
			GetComponent<Transform>()->SetWorldPosition(pos);
			GetComponent<Transform>()->SetScale(sca);
		}
		//�J�����Ƃ�
		if (m_OpenFlag) {
			ElapsedTime += App::GetApp()->GetElapsedTime();
			//�J���A�j���[�V�������I�������
			if (IsAnimeEnd()) {
				//�t�F�[�h������
				auto FadeIn = GetStage()->GetSharedGameObject<SpriteFade>(L"FadeIn");
				FadeIn->SetActionflag(true);
			}
		}
		if (m_RemoveFlag) {
			m_RemoveTime += App::GetApp()->GetElapsedTime();
			if (m_RemoveTime >= 2.0f) {
				GetStage()->RemoveGameObject<StageSelectDoor>(GetThis<StageSelectDoor>());
			}
		}
		//�A�j���[�V�����̍X�V
		UpdateAnimeTime(ElapsedTime);
	}

	void StageSelectDoor::OnUpdate2() {
	}

	void StageSelectDoor::Open() {
		m_OpenFlag = true;
		ChangeAnimation(L"OPEN_" + m_DoorNum);
		SetLooped(false);
	}
	void StageSelectDoor::StyleChange(){
		if (m_OpenFlag) {
			//�����ʒu�A�����T�C�Y�ɖ߂�
			GetComponent<Transform>()->SetWorldPosition(m_Position);
			GetComponent<Transform>()->SetScale(m_Scale);
		}
		else if (m_SelectFlag) {
			ChangeAnimation(L"SELECT_" + m_DoorNum);
			SetLooped(true);
		}
		//�I������Ă��Ȃ��A�J����Ă��Ȃ���
		else {
			//�����ʒu�A�����T�C�Y�ɖ߂�
			GetComponent<Transform>()->SetWorldPosition(m_Position);
			GetComponent<Transform>()->SetScale(m_Scale);
			//�Ԙg���Ȃ������߂�"OPEN"�A�j���A
			//�A�j���[�V�����̍X�V���s��Ȃ����ߕ�����Ԃ̂܂�
			ChangeAnimation(L"OPEN_" + m_DoorNum);
		}
	}
}
