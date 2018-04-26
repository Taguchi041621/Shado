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
		m_Scale(Scale), m_Rotation(Rotation), m_Obj(Obj), m_ScaleZ(0.25f)
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
		PtrDraw->SetFogEnabled(true);

		PtrDraw->SetMeshResource(m_Obj.GetComponent<BcPNTStaticDraw>()->GetMeshResource());
		PtrDraw->SetOwnShadowActive(true);
		//真っ黒
		PtrDraw->SetColorAndAlpha(Col4(1.0f, 1.0f, 1.0f, 0.0f));
	}

	//変化
	void ShadowObject::OnUpdate() {
	}
	void ShadowObject::OnUpdate2() {
		//auto velo = ShadowLocation() - GetComponent<Transform>()->GetPosition();
		//velo = velo / App::GetApp()->GetElapsedTime();
		//GetComponent<Rigidbody>()->SetVelocity(velo);
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
		//m_kagePos.x += m_Obj.GetComponent<Transform>()->GetScale().x/2 - m_Scale.x;

		return m_kagePos;
	}
	//------------------------------------------------------------------------------------------
	///ゴールの役割をする影
	//------------------------------------------------------------------------------------------
	ShadowGoal::ShadowGoal(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale, const Vec3& Rotation, GameObject& Obj)
		: GameObject(StagePtr),
		m_Scale(Scale),m_Rotation(Rotation),m_Obj(Obj), m_ScaleZ(0.25f)
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
		PtrDraw->SetColorAndAlpha(Col4(1.0f, 0.0f, 0.0f, 1.0f));
	}

	void ShadowGoal::OnUpdate() {
		OnTriggerEnter();
		GetComponent<Transform>()->SetPosition(ShadowLocation());
	}

	void ShadowGoal::OnTriggerEnter(){
		SPHERE t;
		t.m_Center = this->GetComponent<Transform>()->GetPosition();
		t.m_Center.z = 0;
		t.m_Radius = 0.20;

		SPHERE p;
		p.m_Center = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetWorldPosition();
		p.m_Center.z = 0;
		p.m_Radius = 0.20;

		if (HitTest::SPHERE_SPHERE(t, p)){
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
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
}