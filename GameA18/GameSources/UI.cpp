
#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	///	�X�v���C�g
	//--------------------------------------------------------------------------------------
	Sprite::Sprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_Actionflag(false)
	{}

	Sprite::~Sprite() {}
	void Sprite::OnCreate() {
		float HelfSize = 0.5f;
		//���_�z��
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, m_StartPos.z);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_TextureKey);
		SetAlphaActive(true);
		auto ActionPtr = AddComponent<Action>();
		/*ActionPtr->AddMoveTo(0.1f, Vec3(m_StartPos.x*0.0f, m_StartPos.y, 0.0f));
		ActionPtr->AddScaleTo(0.1f, Vec3(m_StartScale.x*2.0f, m_StartScale.y*2.0f, 0.0f));
		ActionPtr->AddScaleTo(0.5f, Vec3(m_StartScale.x, m_StartScale.y, 0.0f));
		ActionPtr->SetLooped(true);
		ActionPtr->Run();*/
	}

	void Sprite::OnUpdate() {
		auto ActionPtr = AddComponent<Action>();
		auto PtrTransform = GetComponent<Transform>();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		/*if (m_Actionflag == true) {
			ActionPtr->Run();
		}
		if (m_Actionflag == false) {
			ActionPtr->Stop();
			PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, m_StartPos.z);
			PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		}*/

	};
	//-------------------------------------------------------------------------------------
	///�X�e�[�W��̌��̐��ƌ��ݎ擾�������̐���\������
	//-------------------------------------------------------------------------------------
	HaveKeys::HaveKeys(const shared_ptr<Stage>& StagePtr,wstring& TextureKey,int order)
		: GameObject(StagePtr),m_TextureKey(TextureKey),m_order(order)
	{
	};
	//--------------------------------------------------------------------------------------
	/*!
	@brief �f�X�g���N�^
	*/
	//--------------------------------------------------------------------------------------
	HaveKeys::~HaveKeys() {};
	//--------------------------------------------------------------------------------------
	/*!
	@brief ������
	@return	�Ȃ�
	*/
	//--------------------------------------------------------------------------------------
	void HaveKeys::OnCreate() {
		//������������ɍs���N���G�C�g
		if (m_TextureKey == (wstring)L"Key_TX") {
			GetStage()->AddGameObject<Sprite>(m_TextureKey, true,
				Vec2(60.0f, 120.0f), Vec3(-600.0f + (50.0f * m_order), 330.0f, 0.0f));
			return;
		}
		//�X�e�[�W���ł����Ƃ��ɍs���N���G�C�g
		GetStage()->AddGameObject<Sprite>(m_TextureKey, true,
			Vec2(60.0f, 120.0f),Vec3(-600.0f + (50.0f * m_order), 330.0f, 0.1f));
		//�ŏ����炠������O���[�v�ɓo�^����
		auto group = GetStage()->GetSharedObjectGroup(L"HaveKeysGroup");
		group->IntoGroup(GetThis<HaveKeys>());
	};
	//--------------------------------------------------------------------------------------
	/*!
	@brief �X�V
	@return	�Ȃ�
	*/
	//--------------------------------------------------------------------------------------
	void HaveKeys::OnUpdate() {};

	//-------------------------------------------------------------------------------------
	///���C�g�̈ʒu��\������~�j�}�b�v
	//-------------------------------------------------------------------------------------
	MiniMap::MiniMap(const shared_ptr<Stage>& StagePtr)
		: GameObject(StagePtr)
	{
	};
	//--------------------------------------------------------------------------------------
	/*!
	@brief �f�X�g���N�^
	*/
	//--------------------------------------------------------------------------------------
	MiniMap::~MiniMap() {};
	//--------------------------------------------------------------------------------------
	/*!
	@brief ������
	@return	�Ȃ�
	*/
	//--------------------------------------------------------------------------------------
	void MiniMap::OnCreate() {
		GetStage()->AddGameObject<Sprite>(L"pane_TX", true, Vec2(160.0f, 160.0f), Vec3(-540.0f, -300.0f, 0.1f));
		auto light = GetStage()->AddGameObject<Sprite>(L"ball_yellow_TX", true, Vec2(30.0f,30.0f), Vec3(-540.0f, -300.0f, 0.1f));
		light->AddComponent<Action>();
		light->GetComponent<Action>()->AllActionClear();
		GetStage()->SetSharedGameObject(L"MiniMapLight", light);
	};
	//--------------------------------------------------------------------------------------
	/*!
	@brief �X�V
	@return	�Ȃ�
	*/
	//--------------------------------------------------------------------------------------
	void MiniMap::OnUpdate() {
		auto ptrMyLight = GetStage()->GetSharedGameObject<LightController>(L"LightController");
		auto LightAngle = ptrMyLight->GetLightAngle();
		auto MiniMapLight = GetStage()->GetSharedGameObject<Sprite>(L"MiniMapLight");
		MiniMapLight->GetComponent<Transform>()->
			SetPosition(Vec3(-540.0f + -90*sinf(LightAngle.x), -300.0f + -90*sinf(LightAngle.y), 0.1f));
	};

	//-------------------------------------------------------------------------------------
	///���C�g�̈ʒu��\�������
	//-------------------------------------------------------------------------------------
	LightSign::LightSign(const shared_ptr<Stage>& StagePtr)
		: GameObject(StagePtr)
	{
	};
	//--------------------------------------------------------------------------------------
	/*!
	@brief �f�X�g���N�^
	*/
	//--------------------------------------------------------------------------------------
	LightSign::~LightSign() {};
	//--------------------------------------------------------------------------------------
	/*!
	@brief ������
	@return	�Ȃ�
	*/
	//--------------------------------------------------------------------------------------
	void LightSign::OnCreate() {
		auto light = GetStage()->AddGameObject<Sprite>(L"LIGHT_Illust_TX", true, Vec2(160.0f, 160.0f), Vec3(0.0f, 0.0f, 0.1f));
		light->AddComponent<Action>();
		light->GetComponent<Action>()->AllActionClear();
		GetStage()->SetSharedGameObject(L"LightSign", light);
	};
	//--------------------------------------------------------------------------------------
	/*!
	@brief �X�V
	@return	�Ȃ�
	*/
	//--------------------------------------------------------------------------------------
	void LightSign::OnUpdate() {
		auto LightAngle = GetStage()->GetSharedGameObject<LightController>(L"LightController")->GetLightAngle();
		auto MiniMapLight = GetStage()->GetSharedGameObject<Sprite>(L"LightSign");
		//��ʒ[�ł����o��悤�ɂ���
		if (LightAngle.x < 0.5f && LightAngle.x > -0.5f && LightAngle.y <0.5f && LightAngle.y > -0.5f) {
			MiniMapLight->SetDrawActive(false);
		}
		else {
			MiniMapLight->SetDrawActive(true);
		}
		Vec3 LightPos;
		//�|�W�V�����̌v�Z
		LightPos.z = 0.1f;
		LightPos.x = 840 * -sinf(LightAngle.x);
		LightPos.y = 500 * -sinf(LightAngle.y);
		//�|�W�V�����̔��f
		MiniMapLight->GetComponent<Transform>()->SetPosition(LightPos);

		//�X�e�[�W�̃��C�g�p�x����I�u�W�F�N�g�̊p�x���o��
		auto an = atan2f(LightAngle.x, LightAngle.y);
		MiniMapLight->GetComponent<Transform>()->SetRotation(Vec3(0.0f,0.0f,-an));

		//�X�e�[�W�̃��C�g��ʂŎ�����
		Vec3 angle = LightAngle;
		//���̐��ɂ���
		if (LightAngle.x < 0) {
			angle.x = -LightAngle.x;
		}
		if (LightAngle.y < 0) {
			angle.y = -LightAngle.y;
		}
		//���C�g�A���O���̒l�ɉ����ăA���t�@�l��ς���
		float AlphaLight = angle.x;
		if (AlphaLight < angle.y) {
			AlphaLight = angle.y;
		}
		//�����x��ς���
		MiniMapLight->GetComponent<PCTSpriteDraw>()->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, AlphaLight));
	};

	//--------------------------------------------------------------------------------------
	///	�g��k�����J��Ԃ��X�v���C�g
	//--------------------------------------------------------------------------------------
	ScaleChangeSprite::ScaleChangeSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos, const float f,bool ScaleChangeFlag) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		f(f),
		m_ScaleChangeFlag(ScaleChangeFlag),
		m_SceleFlag(true)
	{}

	ScaleChangeSprite::~ScaleChangeSprite() {}
	void ScaleChangeSprite::OnCreate() {
		float HelfSize = 0.5f;
		//���_�z��
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 0.1f);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(m_TextureKey);
	}

	void ScaleChangeSprite::OnUpdate() {
		auto PtrTransform = GetComponent<Transform>();
		auto PtrScale = PtrTransform->GetScale();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_Timer += ElapsedTime;
		if (m_ScaleChangeFlag) {
			if (m_SceleFlag) {
				PtrTransform->SetScale(PtrScale.x + f, PtrScale.y + f, m_StartPos.z);
			}
			else {
				PtrTransform->SetScale(PtrScale.x - f, PtrScale.y - f, m_StartPos.z);
			}
			if (1 <= m_Timer)
			{
				if (m_SceleFlag) {
					m_SceleFlag = false;
					m_Timer = 0;
				}
				else if (!m_SceleFlag) {
					m_SceleFlag = true;
					m_Timer = 0;
				}
			}
		}
		else {
			PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 0.1f);
			m_Timer = 0;
			m_SceleFlag = true;
		}

	};

	//--------------------------------------------------------------------------------------
	///	�����̃X�v���C�g
	//--------------------------------------------------------------------------------------
	ScoreSprite::ScoreSprite(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
		const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos,float Score, bool ScaleChange, float ChangeFloat) :
		GameObject(StagePtr),
		m_NumberOfDigits(NumberOfDigits),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_Score(Score),
		m_ScaleChangeFlag(ScaleChange),
		m_ChangeFloat(ChangeFloat)
	{}

	void ScoreSprite::OnCreate() {
		float XPiecesize = 1.0f / (float)m_NumberOfDigits;
		float HelfSize = 0.5f;
		m_SceleFlag = true;
		//�C���f�b�N�X�z��
		vector<uint16_t> indices;
		for (UINT i = 0; i < m_NumberOfDigits; i++) {
			float Vertex0 = -HelfSize + XPiecesize * (float)i;
			float Vertex1 = Vertex0 + XPiecesize;
			//0
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(Vertex0, HelfSize, 0), Vec2(0.0f, 0.0f))
			);
			//1
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(Vertex1, HelfSize, 0), Vec2(0.1f, 0.0f))
			);
			//2
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(Vertex0, -HelfSize, 0), Vec2(0.0f, 1.0f))
			);
			//3
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(Vertex1, -HelfSize, 0), Vec2(0.1f, 1.0f))
			);
			indices.push_back(i * 4 + 0);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 2);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 3);
			indices.push_back(i * 4 + 2);
		}

		SetAlphaActive(m_Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto PtrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);
		PtrDraw->SetTextureResource(m_TextureKey);
	}

	void ScoreSprite::OnUpdate() {
		vector<VertexPositionTexture> NewVertices;
		UINT Num;
		int VerNum = 0;
		for (UINT i = m_NumberOfDigits; i > 0; i--) {
			UINT Base = (UINT)pow(10, i);
			Num = ((UINT)m_Score) % Base;
			Num = Num / (Base / 10);
			Vec2 UV0 = m_BackupVertices[VerNum].textureCoordinate;
			UV0.x = (float)Num / 10.0f;
			auto v = VertexPositionTexture(
				m_BackupVertices[VerNum].position,
				UV0
			);
			NewVertices.push_back(v);

			Vec2 UV1 = m_BackupVertices[VerNum + 1].textureCoordinate;
			UV1.x = UV0.x + 0.1f;
			v = VertexPositionTexture(
				m_BackupVertices[VerNum + 1].position,
				UV1
			);
			NewVertices.push_back(v);

			Vec2 UV2 = m_BackupVertices[VerNum + 2].textureCoordinate;
			UV2.x = UV0.x;

			v = VertexPositionTexture(
				m_BackupVertices[VerNum + 2].position,
				UV2
			);
			NewVertices.push_back(v);

			Vec2 UV3 = m_BackupVertices[VerNum + 3].textureCoordinate;
			UV3.x = UV0.x + 0.1f;

			v = VertexPositionTexture(
				m_BackupVertices[VerNum + 3].position,
				UV3
			);
			NewVertices.push_back(v);

			VerNum += 4;
		}
		ScaleChange(m_ChangeFloat);
		auto PtrDraw = GetComponent<PTSpriteDraw>();
		PtrDraw->UpdateVertices(NewVertices);
	}

	void ScoreSprite::ScaleChange(float f) {
		auto PtrTransform = GetComponent<Transform>();
		auto PtrScale = PtrTransform->GetScale();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_Timer += ElapsedTime;
		if (m_ScaleChangeFlag) {
			if (m_SceleFlag) {
				PtrTransform->SetScale(PtrScale.x + f, PtrScale.y + f, m_StartPos.z);
			}
			else {
				PtrTransform->SetScale(PtrScale.x - f, PtrScale.y - f, m_StartPos.z);
			}
			if (1 <= m_Timer)
			{
				if (m_SceleFlag) {
					m_SceleFlag = false;
					m_Timer = 0;
				}
				else if (!m_SceleFlag) {
					m_SceleFlag = true;
					m_Timer = 0;
				}
			}
		}
		else {
			PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 0.1f);
			m_Timer = 0;
			m_SceleFlag = true;
		}

	}

	//------------------------------------------------------------------------------------------
	///Tutorial
	//------------------------------------------------------------------------------------------
	Tutorial::Tutorial(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
		const Vec3& m_Scale, const Vec3& Rotation, const Vec3& Position, const wstring AnimeName)
		: SS5ssae(StagePtr, BaseDir, L"XBOXcontroler.ssae", AnimeName),
		m_Scale(m_Scale), m_Rotation(Rotation), m_Position(Position), m_ScaleZ(0.05f)
	{
		m_ToAnimeMatrix.affineTransformation(
			Vec3(0.15f, 0.15f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0, 0.0f, 0.0f)
		);
	}

	void Tutorial::OnCreate() {
		////�X�P�[����Z���Œ�̑傫����
		//m_Scale.z = m_ScaleZ;

		//auto PtrTransform = GetComponent<Transform>();
		////�e�̃X�P�[��,�p�x,�|�W�V�����̐ݒ�
		//PtrTransform->SetScale(m_Scale);
		//PtrTransform->SetRotation(m_Rotation);
		//PtrTransform->SetPosition(ShadowLocation());

		//auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//PtrDraw->SetFogEnabled(true);
		////���̂���`�������Ă���
		//PtrDraw->SetMeshResource(m_Obj.GetComponent<BcPNTStaticDraw>()->GetMeshResource());
		//PtrDraw->SetOwnShadowActive(true);

		////�^����
		//PtrDraw->SetColorAndAlpha(Col4(1.0f, 0.4f, 0.0f, 1.0f));

		//flag = false;

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
		SetFps(60);
		//�A�j���[�V�����̃��[�v�ݒ�
		SetLooped(true);
		//�A�j���[�V�����ɂ����郁�g���b�N�X�̐ݒ�
		SetToAnimeMatrix(m_ToAnimeMatrix);
	}

	void Tutorial::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//�A�j���[�V�������X�V����
		UpdateAnimeTime(ElapsedTime);
	}

	//--------------------------------------------------------------------------------------
	// �R�c��Ԃ̃X�v���C�g
	//--------------------------------------------------------------------------------------
	Sprite3D::Sprite3D(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale, const Vec3& Rotation, const Vec3& Position,const wstring TextureName)
		: GameObject(StagePtr),
		m_Scale(Scale), m_Rotation(Rotation), m_Position(Position), m_ScaleZ(0.05f), m_TextureName(TextureName)
	{
	}

	Sprite3D::~Sprite3D() {}
	//������
	void Sprite3D::OnCreate() {
		//�X�P�[����Z���Œ�̑傫����
		m_Scale.z = m_ScaleZ;
		//AddComponent<Rigidbody>();
		auto PtrTransform = AddComponent<Transform>();
		//�e�̃X�P�[��,�p�x,�|�W�V�����̐ݒ�
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(m_Position);

		//auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//PtrDraw->SetMeshResource(m_Obj.GetComponent<BcPNTStaticDraw>()->GetMeshResource());
		////�^����
		//PtrDraw->SetColorAndAlpha(Col4(1.0f, 1.0f, 1.0f, 0.0f));
		////Mat4x4 au;
		///*au.affineTransformation(
		//	Vec3(1.0f, 1.0f, 0.1f),
		//	Vec3(0, 0, 0),
		//	Vec3(0, 0, 0),
		//	Vec3(0.0f, 0.0f, 0.0f)
		//	);
		//PtrDraw->SetMeshToTransformMatrix(au);*/
		//PtrDraw->SetTextureResource(L"Shadow_Blur_TX");
		//PtrDraw->SetAlpha(1.0f);
		//PtrDraw->SetPerPixelLighting(false);
		//���_�z��
		vector<VertexPositionNormalTexture> vertices;
		//�C���f�b�N�X���쐬���邽�߂̔z��
		vector<uint16_t> indices;
		//Square�̍쐬(�w���p�[�֐��𗘗p)
		MeshUtill::CreateSquare(1.0f, vertices, indices);

		//���㒸�_
		vertices[0].textureCoordinate = Vec2(0, 0);
		//�E�㒸�_
		vertices[1].textureCoordinate = Vec2(1, 0);
		//�������_
		vertices[2].textureCoordinate = Vec2(0, 1.0f);
		//�E�����_
		vertices[3].textureCoordinate = Vec2(1, 1.0f);
		//���_�̌^��ς����V�������_���쐬
		vector<VertexPositionColorTexture> new_vertices;
		for (auto& v : vertices) {
			VertexPositionColorTexture nv;
			nv.position = v.position;
			nv.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
			nv.textureCoordinate = v.textureCoordinate;
			new_vertices.push_back(nv);
		}
		//�V�������_���g���ă��b�V�����\�[�X�̍쐬
		m_SquareMeshResource = MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true);

		auto DrawComp = AddComponent<PCTStaticDraw>();
		DrawComp->SetMeshResource(m_SquareMeshResource);
		//�`�悷��e�N�X�`����ݒ�
		DrawComp->SetTextureResource(m_TextureName);
		//��������
		SetAlphaActive(true);
	}

	//�ω�
	void Sprite3D::OnUpdate() {

	}
	void Sprite3D::OnUpdate2() {

	}
	//end basecross
}