#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void BannerStage::CreateViewLight()
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
	}
	void BannerStage::CreateBanner() {
		wstring DateDir;
		App::GetApp()->GetDataDirectory(DateDir);
		auto banner = AddGameObject<SpriteStudioBanner>(DateDir,Vec3(0.5f,0.5f,0.5f),Vec3(0.0f,0.0f,0.0f),Vec3(0.0f,0.0f,0.0f));
		SetSharedGameObject(L"Banner", banner);
	}
	void BannerStage::OnCreate() {
		CreateViewLight();
		CreateBanner();
	}
	void BannerStage::OnUpdate() {
		if (!CreditFlag) {
			//�X�v���C�g�X�^�W�I���S�̃A�j�����I�������
			if (GetSharedGameObject<SpriteStudioBanner>(L"Banner")->GetBannerEnd()) {
				//�X�v���C�g�X�^�W�I���S�̏���
				RemoveGameObject<SpriteStudioBanner>(GetSharedGameObject<SpriteStudioBanner>(L"Banner"));
				//�N���W�b�g�摜�̕\��
				AddGameObject<Sprite>(L"Credit_Link_TX", true,Vec2(1280.0f, 800.0f), Vec3(0, 0.0f, 0.0f));
				//�N���W�b�g��\�������Ƃ����t���O
				CreditFlag = true;
				//3�b��ɃV�[���J��
				PostEvent(3.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			}
		}
		else {
			FadeTime += App::GetApp()->GetElapsedTime();
			if (FadeTime >= 2.2f) {
				 auto fade = AddGameObject<SpriteFade>(L"Shadow_TX", true,
					Vec2(840, 600), Vec3(900.0f, 0.0f, 0.0f));
				 fade->SetActionflag(true);
				 FadeTime = -10.0f;
			}
		}
	}

	SpriteStudioBanner::SpriteStudioBanner(const shared_ptr<Stage>& StagePtr,const wstring BaseDir,
		const Vec3& Scale,const Vec3& Rotation,const Vec3& Position)
		: SS5ssae(StagePtr,BaseDir + L"SpriteStudioBanner\\splash512\\",L"splash512_instance.ssae", L"in"),
		m_Scale(Scale), m_Rotation(Rotation),m_Position(Position){
	}
	void SpriteStudioBanner::OnCreate() {
		auto PtrTransform = AddComponent<Transform>();
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(m_Position);
		//�e�N���X�̃N���G�C�g���Ă�
		SS5ssae::OnCreate();
		//�l�͕b������̃t���[����
		SetFps(60);
		//�A�j���[�V�����̃��[�v�ݒ�
		SetLooped(false);
		//SetSpriteDraw(true);
	}
	void SpriteStudioBanner::OnUpdate() {
		if (IsAnimeEnd()) {
			BannerEnd = true;
		}

		UpdateAnimeTime(App::GetApp()->GetElapsedTime());
	}
}