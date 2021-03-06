
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
	}

	void Sprite::OnUpdate() {
		auto ActionPtr = AddComponent<Action>();
		auto PtrTransform = GetComponent<Transform>();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
	};

	//-------------------------------------------------------------------------------------
	///ライトの位置を表示するライト
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
		auto light = GetStage()->AddGameObject<Sprite>(L"LIGHT_Illust_TX", true, Vec2(160.0f, 160.0f), Vec3(0.0f, 0.0f, 0.1f));
		light->AddComponent<Action>();
		light->GetComponent<Action>()->AllActionClear();
		light->SetDrawActive(false);
		GetStage()->SetSharedGameObject(L"LightSign", light);
	};
	//--------------------------------------------------------------------------------------
	/*!
	@brief 更新
	@return	なし
	*/
	//--------------------------------------------------------------------------------------
	void LightSign::OnUpdate() {
		auto LightAngle = GetStage()->GetSharedGameObject<LightController>(L"LightController")->GetLightAngle();
		auto MiniMapLight = GetStage()->GetSharedGameObject<Sprite>(L"LightSign");
		if (App::GetApp()->GetScene<Scene>()->GetStartFlag()) {
			MiniMapLight->SetDrawActive(true);
			if (App::GetApp()->GetScene<Scene>()->GetPauseFlag()) {
				MiniMapLight->SetDrawActive(false);
			}
		}
		Vec3 LightPos;
		//ポジションの計算
		LightPos.z = 0.1f;
		LightPos.x = 840 * -sinf(LightAngle.x);
		LightPos.y = 500 * -sinf(LightAngle.y);
		//ポジションの反映
		MiniMapLight->GetComponent<Transform>()->SetPosition(LightPos);

		//ステージのライト角度からオブジェクトの角度を出す
		auto an = atan2f(LightAngle.x, LightAngle.y);
		MiniMapLight->GetComponent<Transform>()->SetRotation(Vec3(0.0f,0.0f,-an));

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
		const Vec2& StartScale, const Vec3& StartPos,int Score, bool ScaleChange, float ChangeFloat) :
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

	//--------------------------------------------------------------------------------------
	// ３Ｄ空間のスプライト
	//--------------------------------------------------------------------------------------
	Sprite3D::Sprite3D(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale, const Vec3& Rotation, const Vec3& Position,const wstring TextureName)
		: GameObject(StagePtr),
		m_Scale(Scale), m_Rotation(Rotation), m_Position(Position), m_ScaleZ(0.05f), m_TextureName(TextureName)
	{
	}

	Sprite3D::~Sprite3D() {}
	//初期化
	void Sprite3D::OnCreate() {
		//スケールのZを固定の大きさに
		m_Scale.z = m_ScaleZ;
		//AddComponent<Rigidbody>();
		auto PtrTransform = AddComponent<Transform>();
		//影のスケール,角度,ポジションの設定
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(m_Position);

		//頂点配列
		vector<VertexPositionNormalTexture> vertices;
		//インデックスを作成するための配列
		vector<uint16_t> indices;
		//Squareの作成(ヘルパー関数を利用)
		MeshUtill::CreateSquare(1.0f, vertices, indices);

		//左上頂点
		vertices[0].textureCoordinate = Vec2(0, 0);
		//右上頂点
		vertices[1].textureCoordinate = Vec2(1, 0);
		//左下頂点
		vertices[2].textureCoordinate = Vec2(0, 1.0f);
		//右下頂点
		vertices[3].textureCoordinate = Vec2(1, 1.0f);
		//頂点の型を変えた新しい頂点を作成
		vector<VertexPositionColorTexture> new_vertices;
		for (auto& v : vertices) {
			VertexPositionColorTexture nv;
			nv.position = v.position;
			nv.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
			nv.textureCoordinate = v.textureCoordinate;
			new_vertices.push_back(nv);
		}
		//新しい頂点を使ってメッシュリソースの作成
		m_SquareMeshResource = MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true);

		auto DrawComp = AddComponent<PCTStaticDraw>();
		DrawComp->SetMeshResource(m_SquareMeshResource);
		//描画するテクスチャを設定
		DrawComp->SetTextureResource(m_TextureName);
		//透明処理
		SetAlphaActive(true);
	}

	//変化
	void Sprite3D::OnUpdate() {

	}
	void Sprite3D::OnUpdate2() {

	}
	//end basecross
}