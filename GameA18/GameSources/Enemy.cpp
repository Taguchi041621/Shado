#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//大砲
	//--------------------------------------------------------------------------------------
	Cannon::Cannon(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
		const Vec3& Scale, const Vec3& Rotation, weak_ptr<GameObject> Obj, CannonBase::CanonDirection LR)
		: SS5ssae(StagePtr, BaseDir, L"Cannon.ssae", L"Fire"),
		m_Scale(Scale), m_Rotation(Rotation), m_Obj(Obj), m_ScaleZ(0.05f), m_CoolTime(0), m_BulletFlag(false),m_LR(LR)
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.13f, 0.12f, 0.7f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.0f, -0.01f, 0.0f)
		);
		m_ToAnimeMatrixRight.affineTransformation(
			Vec3(-0.13f, 0.12f, 0.7f),
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
		if (m_LR == CannonBase::CanonDirection::LEFT) {
			//アニメーションにかけるメトリックスの設定
			SetToAnimeMatrix(m_ToAnimeMatrixLeft);
		}
		else {
			//アニメーションにかけるメトリックスの設定
			SetToAnimeMatrix(m_ToAnimeMatrixRight);
		}
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
					//左向き
					if (m_LR == CannonBase::CanonDirection::LEFT) {
						GetStage()->AddGameObject<Bullet>(
							GetComponent<Transform>()->GetScale(),
							GetComponent<Transform>()->GetRotation(),
							GetComponent<Transform>()->GetPosition() - Vec3(1, -0.4f, 0),
							m_LR
							);
						//煙だす
						GetStage()->AddGameObject<DirectingRing>(GetComponent<Transform>()->GetWorldPosition(),
							Vec3(1.5f, 1.5f, 0.05f), Vec3(-1.0f, 0.5f, 0.0f), L"Smoke_Black_TX");
					}
					//右向き
					else {
						GetStage()->AddGameObject<Bullet>(
							GetComponent<Transform>()->GetScale(),
							GetComponent<Transform>()->GetRotation(),
							GetComponent<Transform>()->GetPosition() - Vec3(-1, -0.4f, 0),
							m_LR
							);
						//煙だす
						GetStage()->AddGameObject<DirectingRing>(GetComponent<Transform>()->GetWorldPosition(),
							Vec3(1.5f, 1.5f, 0.05f), Vec3(1.0f, 0.5f, 0.0f), L"Smoke_Black_TX");

					}
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
		auto obj = m_Obj.lock();
		//実体ブロックのポジション
		auto ObjPos = obj->GetComponent<Transform>()->GetPosition();
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
		const Vec3& Scale, const Vec3& Rotation, const Vec3& Position,CannonBase::CanonDirection LR)
		: GameObject(StagePtr),
		m_Scale(Scale), m_Rotation(Rotation), m_Position(Position), m_ScaleZ(0.05f),m_LR(LR)
	{
	}

	Bullet::~Bullet() {}
	//初期化
	void Bullet::OnCreate() {
		if (m_LR == CannonBase::CanonDirection::RIGTH) {
			m_Scale *= -1.0f;
		}
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
		DrawComp->SetTextureResource(L"BULLET_TX");
		//透明処理
		SetAlphaActive(true);
		auto PtrRedid = AddComponent<Rigidbody>();
		auto PtrCol = AddComponent<CollisionObb>();
	}
	//当たり判定
	void Bullet::OnCollision(vector<shared_ptr<GameObject>>& OtherVec) {
		auto playerTrans = GetComponent<Transform>();
		for (auto &obj : OtherVec) {
			//シャドウオブジェクトを検出
			auto ShadowPtr = dynamic_pointer_cast<ShadowObject>(obj);
			auto BulletPtr = dynamic_pointer_cast<Bullet>(obj);
			auto PlayerPtr = dynamic_pointer_cast<Player>(obj);
			//影ブロックと当たる
			if (ShadowPtr) {
				//輪っかを出す
				GetStage()->AddGameObject<DirectingRing>(playerTrans->GetWorldPosition(),
					Vec3(1.0f,1.0f,0.05f), Vec3(-0.5f, 0.0f, 0.0f),L"Ring_TX");
				GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
			}
			//弾と当たる
			else if (BulletPtr) {
				//輪っかを出す
				GetStage()->AddGameObject<DirectingRing>(playerTrans->GetWorldPosition(),
					Vec3(1.0f, 1.0f, 0.05f), Vec3(-0.5f, 0.0f, 0.0f), L"Ring_TX");
				GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
			}
			//イデアと当たりう
			else if (PlayerPtr) {
				PlayerPtr->Damage(m_LR);
				//輪っかを出す
				GetStage()->AddGameObject<DirectingRing>(playerTrans->GetWorldPosition(),
					Vec3(1.0f, 1.0f, 0.05f), Vec3(-0.5f, 0.0f, 0.0f),L"Ring_TX");
				GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
			}
		}
	}

	//変化
	void Bullet::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto PtrTransform = AddComponent<Transform>();
		auto Pos = PtrTransform->GetPosition();
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		if (!ScenePtr->GetPauseFlag()) {
			if (m_LR == CannonBase::CanonDirection::LEFT) {
				Pos.x -= 7.0f*ElapsedTime;
				PtrTransform->SetPosition(Pos);

				//OnTriggerEnter();
				if (Pos.x <= -30) {
					GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
				}
			}
			else {
				Pos.x += 7.0f*ElapsedTime;
				PtrTransform->SetPosition(Pos);
				if (Pos.x >= 30) {
					GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
				}
			}
		}
	}
	void Bullet::OnUpdate2() {

	}

}