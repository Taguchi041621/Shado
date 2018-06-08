#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//------------------------------------------------------------------------------------------
	///敵(影)
	//------------------------------------------------------------------------------------------
	ShadowEnemy::ShadowEnemy(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
		const Vec3& Scale, const Vec3& Rotation, GameObject& Obj)
		: SS5ssae(StagePtr, BaseDir, L"SnakeTest.ssae", L"Attack"),
		m_Scale(Scale), m_Rotation(Rotation), m_Obj(Obj), m_ScaleZ(0.05f)
	{
		m_ToAnimeMatrix.affineTransformation(
			Vec3(0.10f, 0.10f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.0f, 0.0f, 0.0f)
		);
	}

	void ShadowEnemy::OnCreate() {
		//スケールのZを固定の大きさに
		m_Scale.z = m_ScaleZ;

		auto PtrTransform = GetComponent<Transform>();
		//影のスケール,角度,ポジションの設定
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(ShadowLocation());

		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(49.0f);
		//アニメーションのループ設定
		SetLooped(true);
		//アニメーションにかけるメトリックスの設定
		SetToAnimeMatrix(m_ToAnimeMatrix);
	}

	void ShadowEnemy::OnUpdate() {
		OnTriggerEnter();
		GetComponent<Transform>()->SetPosition(ShadowLocation());

		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//アニメーションを更新する
		UpdateAnimeTime(ElapsedTime);
	}

	void ShadowEnemy::OnTriggerEnter() {
		OBB t;
		t.m_Center = this->GetComponent<Transform>()->GetWorldPosition();
		t.m_Center.z = 0;
		t.m_Size = this->GetComponent<Transform>()->GetScale() * 0.5f;

		OBB p;
		p.m_Center = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetWorldPosition();
		p.m_Center.z = 0;
		p.m_Size = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetScale() * 0.5f;
		//プレイヤーが鍵に触れたかを調べる判定
		if (HitTest::OBB_OBB(t, p)) {
		}
	}
	//物体とライトの位置から、影の位置を導き出す
	Vec3 ShadowEnemy::ShadowLocation() {
		//実体ブロックのポジション
		auto ObjPos = m_Obj.GetComponent<Transform>()->GetPosition();
		//ライトのコントローラーを持ってくる
		auto ptrMyLight = GetStage()->GetSharedGameObject<LightController>(L"LightController");
		//角度を取り出す
		auto LightAngle = ptrMyLight->GetLightAngle();

		//ライトの角度と対応した実態ブロックの壁までの距離から影の位置を出す
		Vec3 m_kagePos;
		m_kagePos.x = ObjPos.x - ObjPos.z * tanf(LightAngle.x);
		m_kagePos.y = ObjPos.y - ObjPos.z * tanf(LightAngle.y);

		m_kagePos.z = -1;

		return m_kagePos;
	}

	//--------------------------------------------------------------------------------------
	///	敵の実体
	//--------------------------------------------------------------------------------------
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_KeyPos(StartPos)
	{}
	void Enemy::OnCreate() {
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetPosition(m_KeyPos);
		PtrTransform->SetScale(0.50, 1.00, 0.50);

		//タグ
		AddTag(L"Enemy");
		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		////描画するテクスチャを設定
		//PtrDraw->SetTextureResource(L"UI_Key_TX");
		PtrDraw->SetDrawActive(false);

		/*auto group = GetStage()->GetSharedObjectGroup(L"Eeney");
		group->IntoGroup(GetThis<Enemy>());*/

		//影をつける
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		//-------------------------------------------------
		//影の作成
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		GetStage()->AddGameObject<ShadowEnemy>(
			DataDir + L"Enemy\\",
			GetComponent<Transform>()->GetScale(),
			GetComponent<Transform>()->GetRotation(),
			*GetThis<GameObject>()
			);
	}

	void Enemy::OnUpdate()
	{
	}


	//--------------------------------------------------------------------------------------
	//大砲
	//--------------------------------------------------------------------------------------
	Cannon::Cannon(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
		const Vec3& Scale, const Vec3& Rotation, GameObject& Obj)
		: SS5ssae(StagePtr, BaseDir, L"Cannon.ssae", L"Fire"),
		m_Scale(Scale), m_Rotation(Rotation), m_Obj(Obj), m_ScaleZ(0.05f), m_CoolTime(0), m_BulletFlag(false)
	{
		m_ToAnimeMatrix.affineTransformation(
			Vec3(0.13f, 0.12f, 0.7f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.0f, -0.01f, 0.0f)
		);
	}

	Cannon::~Cannon() {}
	//初期化
	void Cannon::OnCreate() {
		//スケールのZを固定の大きさに
		m_Scale.z = m_ScaleZ;

		auto PtrTransform = GetComponent<Transform>();
		//影のスケール,角度,ポジションの設定
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(ShadowLocation());

		//親クラスのクリエイトを呼ぶ
		SS5ssae::OnCreate();
		//値は秒あたりのフレーム数
		SetFps(60);
		//アニメーションのループ設定
		SetLooped(false);
		//アニメーションにかけるメトリックスの設定
		SetToAnimeMatrix(m_ToAnimeMatrix);
		//SetAlphaActive(true);
		//auto PtrCol = AddComponent<CollisionObb>();
		//PtrCol->SetDrawActive(true);
		UpdateAnimeTime(0);
	}

	//変化
	void Cannon::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		if (!m_BulletFlag) {
			m_CoolTime += ElapsedTime;
			UpdateAnimeTime(0);
		}

		if (m_CoolTime >= 5)
		{
			m_BulletFlag = true;
			ChangeAnimation(L"Fire");
			m_CoolTime = 0;
		}
		if (m_BulletFlag) {
			UpdateAnimeTime(ElapsedTime);

			if (IsAnimeEnd()) {
				GetStage()->AddGameObject<Bullet>(
					GetComponent<Transform>()->GetScale(),
					GetComponent<Transform>()->GetRotation(),
					GetComponent<Transform>()->GetPosition() - Vec3(1, -0.4f, 0)
					);
				m_BulletFlag = false;

				if (m_StopNowMusic != L"")
				{
					m_AudioObjectPtr->Stop(m_StopNowMusic);
				}
				wstring DataDir;
				//サンプルのためアセットディレクトリを取得
				//App::GetApp()->GetAssetsDirectory(DataDir);
				//各ゲームは以下のようにデータディレクトリを取得すべき
				App::GetApp()->GetDataDirectory(DataDir);

				m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
				m_AudioObjectPtr->AddAudioResource(L"se4");
				m_AudioObjectPtr->Start(L"se4", XAUDIO2_NO_LOOP_REGION, 0.1f);
				SetNowMusic(L"se4");
				auto ScenePtr = App::GetApp()->GetScene<Scene>();
				if (!ScenePtr->GetPauseFlag()) {
					if (m_CoolTime >= 5)
					{
						m_BulletFlag = true;
						ChangeAnimation(L"Fire");
						m_CoolTime = 0;
					}
					if (m_BulletFlag) {
						UpdateAnimeTime(ElapsedTime);

						if (IsAnimeEnd()) {
							GetStage()->AddGameObject<Bullet>(
								GetComponent<Transform>()->GetScale(),
								GetComponent<Transform>()->GetRotation(),
								GetComponent<Transform>()->GetPosition() - Vec3(1, -0.4f, 0)
								);
							m_BulletFlag = false;
						}
					}
				}
			}
		}
	}

	void Cannon::OnUpdate2() {
		//影のポジションの更新
		GetComponent<Transform>()->SetPosition(ShadowLocation());

	}

	//物体とライトの位置から、影の位置を導き出す
	Vec3 Cannon::ShadowLocation() {
		//実体ブロックのポジション
		auto ObjPos = m_Obj.GetComponent<Transform>()->GetPosition();
		//ライトのコントローラーを持ってくる
		auto ptrMyLight = GetStage()->GetSharedGameObject<LightController>(L"LightController");
		//角度を取り出す
		auto LightAngle = ptrMyLight->GetLightAngle();

		//ライトの角度と対応した実態ブロックの壁までの距離から影の位置を出す
		Vec3 m_kagePos;
		m_kagePos.x = ObjPos.x - ObjPos.z * tanf(LightAngle.x);
		m_kagePos.y = ObjPos.y - ObjPos.z * tanf(LightAngle.y);

		m_kagePos.z = 0;

		return m_kagePos;
	}

	//--------------------------------------------------------------------------------------
	//弾
	//--------------------------------------------------------------------------------------
	Bullet::Bullet(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale, const Vec3& Rotation, const Vec3& Position)
		: GameObject(StagePtr),
		m_Scale(Scale), m_Rotation(Rotation), m_Position(Position), m_ScaleZ(0.05f)
	{
	}

	Bullet::~Bullet() {}
	//初期化
	void Bullet::OnCreate() {
		//スケールのZを固定の大きさに
		m_Scale.z = m_ScaleZ;
		//AddComponent<Rigidbody>();
		auto PtrTransform = AddComponent<Transform>();
		//影のスケール,角度,ポジションの設定
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(m_Position);

		//auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//PtrDraw->SetMeshResource(m_Obj.GetComponent<BcPNTStaticDraw>()->GetMeshResource());
		////真っ黒
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
		DrawComp->SetTextureResource(L"BULLET_TX");
		//透明処理
		SetAlphaActive(true);
		/*Mat4x4 au;
		au.affineTransformation(
		Vec3(0.0f, 0.9f, 0.1f),
		Vec3(0, 0, 0),
		Vec3(0, 0, 0),
		Vec3(0.0f, 0.0f, 0.0f)
		);
		PtrDraw->SetMeshToTransformMatrix(au);*/

	}

	//変化
	void Bullet::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto PtrTransform = AddComponent<Transform>();
		auto Pos = PtrTransform->GetPosition();
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		if (!ScenePtr->GetPauseFlag()) {
			Pos.x -= 5.0f*ElapsedTime;
			PtrTransform->SetPosition(Pos);

			OnTriggerEnter();

			if (Pos.x <= -30) {
				GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
			}
		}
	}
	void Bullet::OnUpdate2() {

	}

	void Bullet::OnTriggerEnter() {
		auto PtrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");

		SPHERE t;
		t.m_Center = GetComponent<Transform>()->GetWorldPosition();
		t.m_Center.z = 0;
		t.m_Radius = GetComponent<Transform>()->GetScale().x/2;

		OBB p;
		p.m_Center = PtrPlayer->GetComponent<Transform>()->GetWorldPosition();
		p.m_Center.z = 0;
		p.m_Size = PtrPlayer->GetComponent<Transform>()->GetScale()/2.3;

		//プレイヤーが弾に触れたかを調べる判定
		if (HitTest::SPHERE_OBB(t, p,Vec3(0))) {
			PtrPlayer->Damage();
		}
	}
}