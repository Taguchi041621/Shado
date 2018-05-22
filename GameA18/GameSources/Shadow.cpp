#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class ShadowObject : public GameObject;
	//	用途: オブジェクトの影
	//--------------------------------------------------------------------------------------
	ShadowObject::ShadowObject(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale, const Vec3& Rotation, GameObject& Obj)
		: GameObject(StagePtr),
		m_Scale(Scale), m_Rotation(Rotation), m_Obj(Obj), m_ScaleZ(0.05f)
	{
	}
	
	ShadowObject::~ShadowObject() {}
	//初期化
	void ShadowObject::OnCreate() {
		//スケールのZを固定の大きさに
		m_Scale.z = m_ScaleZ;
		//AddComponent<Rigidbody>();
		auto PtrTransform = AddComponent<Transform>();
		//影のスケール,角度,ポジションの設定
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(ShadowLocation());

		auto PtrObb = AddComponent<CollisionObb>();
		PtrObb->SetFixed(true);

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(m_Obj.GetComponent<BcPNTStaticDraw>()->GetMeshResource());
		//真っ黒
		PtrDraw->SetColorAndAlpha(Col4(1.0f, 1.0f, 1.0f, 0.0f));
		//Mat4x4 au;
		/*au.affineTransformation(
			Vec3(1.0f, 1.0f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.0f, 0.0f, 0.0f)
			);
		PtrDraw->SetMeshToTransformMatrix(au);*/
		PtrDraw->SetTextureResource(L"Shadow_Blur_TX");
		//PtrDraw->SetAlpha(1.0f);
	}

	//変化
	void ShadowObject::OnUpdate() {
	}
	void ShadowObject::OnUpdate2() {
		//影のポジションの更新
		GetComponent<Transform>()->SetPosition(ShadowLocation());

	}

	//物体とライトの位置から、影の位置を導き出す
	Vec3 ShadowObject::ShadowLocation() {
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

		//ライトの角度を別変数で持つ
		auto AngleX = LightAngle.x;
		auto AngleY = LightAngle.y;
		//マイナスの値だったらプラスにする
		if (AngleX < 0) {
			AngleX *= -1.0f;
		}
		if (AngleY < 0) {
			AngleY *= -1.0f;
		}
		//スケールにアングルの値足す
		GetComponent<Transform>()->SetScale(m_Scale.x + AngleX, m_Scale.y + AngleY, m_ScaleZ);

		return m_kagePos;
	}
	//------------------------------------------------------------------------------------------
	///ゴールの役割をする影
	//------------------------------------------------------------------------------------------
	ShadowGoal::ShadowGoal(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale, const Vec3& Rotation, GameObject& Obj)
		: GameObject(StagePtr),
		m_Scale(Scale),m_Rotation(Rotation),m_Obj(Obj), m_ScaleZ(0.05f)
	{}

	void ShadowGoal::OnCreate() {
		//スケールのZを固定の大きさに
		m_Scale.z = m_ScaleZ;

		auto PtrTransform = GetComponent<Transform>();
		//影のスケール,角度,ポジションの設定
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(ShadowLocation());

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetFogEnabled(true);
		//実体から形を持ってくる
		PtrDraw->SetMeshResource(m_Obj.GetComponent<BcPNTStaticDraw>()->GetMeshResource());
		PtrDraw->SetOwnShadowActive(true);

		//真っ赤
		PtrDraw->SetColorAndAlpha(Col4(1.0f, 0.4f, 0.0f, 1.0f));

		flag = false;
	}

	void ShadowGoal::OnUpdate() {
		OnTriggerEnter();
		GetComponent<Transform>()->SetPosition(ShadowLocation());
	}

	void ShadowGoal::OnTriggerEnter(){
		OBB t;
		t.m_Center = this->GetComponent<Transform>()->GetWorldPosition();
		t.m_Center.z = 0;
		t.m_Size = this->GetComponent<Transform>()->GetScale() * 0.5f;

		OBB p;
		p.m_Center = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetWorldPosition();
		p.m_Center.z = 0;
		p.m_Size = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetScale() * 0.5f;
		//プレイヤーがゴールに触れたかを調べる判定
		if (HitTest::OBB_OBB(t, p)&&!flag){
			if (!GetStage()->GetSharedGameObject<Player>(L"Player")->GetGameOverFlag()) {
				if (GetStage()->GetSharedGameObject<Player>(L"Player")->GetKey() >=
					GetStage()->GetSharedObjectGroup(L"KeyGroup")->size()) {
					GetStage()->GetSharedGameObject<Player>(L"Player")->InGoal();
					flag = true;
					//PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
				}
			}
		}
	}
	//物体とライトの位置から、影の位置を導き出す
	Vec3 ShadowGoal::ShadowLocation() {
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
	//------------------------------------------------------------------------------------------
	///鍵の役割をする影
	//------------------------------------------------------------------------------------------
	ShadowKey::ShadowKey(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale, const Vec3& Rotation, GameObject& Obj)
		: GameObject(StagePtr),
		m_Scale(Scale), m_Rotation(Rotation), m_Obj(Obj), m_ScaleZ(0.05f),m_Key(0)
	{}

	void ShadowKey::OnCreate() {
		//スケールのZを固定の大きさに
		m_Scale.z = m_ScaleZ;

		auto PtrTransform = GetComponent<Transform>();
		//影のスケール,角度,ポジションの設定
		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(ShadowLocation());

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetFogEnabled(true);
		//実体から形を持ってくる
		PtrDraw->SetMeshResource(L"DEFAULT_SQUARE" );
		//PtrDraw->SetOwnShadowActive(true);

		//鍵のテクスチャ
		PtrDraw->SetTextureResource(L"Key_TX");
		PtrDraw->SetAlpha(1.0f);
	}

	void ShadowKey::OnUpdate() {
		OnTriggerEnter();
		GetComponent<Transform>()->SetPosition(ShadowLocation());
	}

	void ShadowKey::OnTriggerEnter() {
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
			//鍵の所持数の表示を変える
			GetStage()->AddGameObject<HaveKeys>((wstring)L"UI_Key_TX",m_Key);
			//プレイヤーの所持鍵数を増やす
			GetStage()->GetSharedGameObject<Player>(L"Player")->AddKey();
			//影の方で持ってる鍵の所持数を増やす
			m_Key += 1;
			//鍵を消す
			GetStage()->RemoveGameObject<ShadowKey>(GetThis<ShadowKey>());
		}
	}
	//物体とライトの位置から、影の位置を導き出す
	Vec3 ShadowKey::ShadowLocation() {
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
}