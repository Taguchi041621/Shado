
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
		auto ActionPtr = AddComponent<Action>();
		ActionPtr->AddMoveTo(0.1f, Vec3(m_StartPos.x*0.0f, m_StartPos.y, 0.0f));
		ActionPtr->AddScaleTo(0.1f, Vec3(m_StartScale.x*2.0f, m_StartScale.y*2.0f, 0.0f));
		ActionPtr->AddScaleTo(0.5f, Vec3(m_StartScale.x, m_StartScale.y, 0.0f));
		ActionPtr->SetLooped(true);
		ActionPtr->Run();
	}

	void Sprite::OnUpdate() {
		auto ActionPtr = AddComponent<Action>();
		auto PtrTransform = GetComponent<Transform>();
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		if (m_Actionflag == true) {
			ActionPtr->Run();
		}
		if (m_Actionflag == false) {
			ActionPtr->Stop();
			PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, m_StartPos.z);
			PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		}
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
		auto light = GetStage()->AddGameObject<Sprite>(L"ball_yellow_TX", true, Vec2(30.0f,30.0f), Vec3(-540.0f, -300.0f, 0.0f));
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
			SetPosition(Vec3(-540.0f + -90*sinf(LightAngle.x), -300.0f + -90*sinf(LightAngle.y), 0.0f));
	};
	//end basecross
}