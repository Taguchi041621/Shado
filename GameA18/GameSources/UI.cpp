
#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	///	スプライト
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
		//頂点配列
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, m_StartPos.z);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos);
		//頂点とインデックスを指定してスプライト作成
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
	///ステージ上の鍵の数と現在取得した鍵の数を表示する
	//-------------------------------------------------------------------------------------
	HaveKeys::HaveKeys(const shared_ptr<Stage>& StagePtr,wstring& TextureKey,int order)
		: GameObject(StagePtr),m_TextureKey(TextureKey),m_order(order)
	{
	};
	//--------------------------------------------------------------------------------------
	/*!
	@brief デストラクタ
	*/
	//--------------------------------------------------------------------------------------
	HaveKeys::~HaveKeys() {};
	//--------------------------------------------------------------------------------------
	/*!
	@brief 初期化
	@return	なし
	*/
	//--------------------------------------------------------------------------------------
	void HaveKeys::OnCreate() {
		//鍵を取った時に行うクリエイト
		if (m_TextureKey == (wstring)L"Key_TX") {
			GetStage()->AddGameObject<Sprite>(m_TextureKey, true,
				Vec2(60.0f, 120.0f), Vec3(-600.0f + (50.0f * m_order), 330.0f, 0.0f));
			return;
		}
		//ステージができたときに行うクリエイト
		GetStage()->AddGameObject<Sprite>(m_TextureKey, true,
			Vec2(60.0f, 120.0f),Vec3(-600.0f + (50.0f * m_order), 330.0f, 0.1f));
		//最初からある方をグループに登録する
		auto group = GetStage()->GetSharedObjectGroup(L"HaveKeysGroup");
		group->IntoGroup(GetThis<HaveKeys>());
	};
	//--------------------------------------------------------------------------------------
	/*!
	@brief 更新
	@return	なし
	*/
	//--------------------------------------------------------------------------------------
	void HaveKeys::OnUpdate() {};

	//-------------------------------------------------------------------------------------
	///ライトの位置を表示するミニマップ
	//-------------------------------------------------------------------------------------
	MiniMap::MiniMap(const shared_ptr<Stage>& StagePtr)
		: GameObject(StagePtr)
	{
	};
	//--------------------------------------------------------------------------------------
	/*!
	@brief デストラクタ
	*/
	//--------------------------------------------------------------------------------------
	MiniMap::~MiniMap() {};
	//--------------------------------------------------------------------------------------
	/*!
	@brief 初期化
	@return	なし
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
	@brief 更新
	@return	なし
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
	///ライトの位置を表示する光
	//-------------------------------------------------------------------------------------
	LightSign::LightSign(const shared_ptr<Stage>& StagePtr)
		: GameObject(StagePtr)
	{
	};
	//--------------------------------------------------------------------------------------
	/*!
	@brief デストラクタ
	*/
	//--------------------------------------------------------------------------------------
	LightSign::~LightSign() {};
	//--------------------------------------------------------------------------------------
	/*!
	@brief 初期化
	@return	なし
	*/
	//--------------------------------------------------------------------------------------
	void LightSign::OnCreate() {
		auto light = GetStage()->AddGameObject<Sprite>(L"ball_yellow_TX", true, Vec2(80.0f, 80.0f), Vec3(0.0f, 0.0f, 0.1f));
		light->AddComponent<Action>();
		light->GetComponent<Action>()->AllActionClear();
		GetStage()->SetSharedGameObject(L"LightSign", light);
	};
	//--------------------------------------------------------------------------------------
	/*!
	@brief 更新
	@return	なし
	*/
	//--------------------------------------------------------------------------------------
	void LightSign::OnUpdate() {
		auto ptrMyLight = GetStage()->GetSharedGameObject<LightController>(L"LightController");
		auto LightAngle = ptrMyLight->GetLightAngle();
		auto MiniMapLight = GetStage()->GetSharedGameObject<Sprite>(L"LightSign");
		//真ん中に居たら消える、イデアに被らないため
		if (LightAngle.x < 0.3f && LightAngle.x > -0.3f && LightAngle.y <0.3f && LightAngle.y > -0.3f) {
			//MiniMapLight->SetDrawActive(false);
		}
		else {
			MiniMapLight->SetDrawActive(true);
		}
		Vec3 LightPos;
		//ポジションの計算
		LightPos.z = 0.1f;
		LightPos.x = 840 * -sinf(LightAngle.x);
		LightPos.y = 500 * -sinf(LightAngle.y);
		//ポジションの反映
		MiniMapLight->GetComponent<Transform>()->SetPosition(LightPos);

		Vec3 angle = LightAngle;
		if (LightAngle.x < 0) {
			angle.x = -LightAngle.x;
		}
		if (LightAngle.y < 0) {
			angle.y = -LightAngle.y;
		}
		//ライトアングルの値に応じてアルファ値を変える
		float AlphaLight = angle.x;
		if (AlphaLight < angle.y) {
			AlphaLight = angle.y;
		}

		//透明度を変える
		MiniMapLight->GetComponent<PCTSpriteDraw>()->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, AlphaLight));

	};

	//--------------------------------------------------------------------------------------
	///	拡大縮小を繰り返すスプライト
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
		//頂点配列
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 0.1f);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos);
		//頂点とインデックスを指定してスプライト作成
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
	///	数字のスプライト
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
		//インデックス配列
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
		//頂点とインデックスを指定してスプライト作成
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
		const Vec3& m_Scale, const Vec3& Rotation, const Vec3& Position)
		: SS5ssae(StagePtr, BaseDir, L"XBOXcontroler.ssae", L"R_stick"),
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
		////スケールのZを固定の大きさに
		//m_Scale.z = m_ScaleZ;

		//auto PtrTransform = GetComponent<Transform>();
		////影のスケール,角度,ポジションの設定
		//PtrTransform->SetScale(m_Scale);
		//PtrTransform->SetRotation(m_Rotation);
		//PtrTransform->SetPosition(ShadowLocation());

		//auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//PtrDraw->SetFogEnabled(true);
		////実体から形を持ってくる
		//PtrDraw->SetMeshResource(m_Obj.GetComponent<BcPNTStaticDraw>()->GetMeshResource());
		//PtrDraw->SetOwnShadowActive(true);

		////真っ赤
		//PtrDraw->SetColorAndAlpha(Col4(1.0f, 0.4f, 0.0f, 1.0f));

		//flag = false;

		//スケールのZを固定の大きさに
		m_Scale.z = m_ScaleZ;

		auto PtrTransform = GetComponent<Transform>();
		//影のスケール,角度,ポジションの設定
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(m_Position);

		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(60);
		//アニメーションのループ設定
		SetLooped(true);
		//アニメーションにかけるメトリックスの設定
		SetToAnimeMatrix(m_ToAnimeMatrix);
	}

	void Tutorial::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//アニメーションを更新する
		UpdateAnimeTime(ElapsedTime);
	}
	//end basecross
}