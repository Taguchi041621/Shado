#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class ShadowObject : public GameObject;
	//	用途: オブジェクトの影
	//--------------------------------------------------------------------------------------
	ShadowObject::ShadowObject(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale, const Vec3& Rotation, const wstring& Mesh, GameObject& Obj)
		: GameObject(StagePtr),
		m_Scale(Scale), m_Rotation(Rotation), m_Mesh(Mesh), m_Obj(Obj)
	{
	}

	ShadowObject::~ShadowObject() {}
	//初期化
	void ShadowObject::OnCreate() {
		m_Scale.z = 0.1f;
		auto PtrTransform = AddComponent<Transform>();
		//影のポジションを出す
		auto kagePos = ShadowLocation();

		PtrTransform->SetScale(m_Scale);
		PtrTransform->SetRotation(m_Rotation);
		PtrTransform->SetPosition(kagePos);

		auto PtrObb = AddComponent<CollisionObb>();
		PtrObb->SetFixed(true);

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetFogEnabled(true);
		PtrDraw->SetMeshResource(m_Mesh);
		PtrDraw->SetOwnShadowActive(true);
		PtrDraw->SetTextureResource(L"Oreng_TX");
	}
	//変化
	void ShadowObject::OnUpdate() {
		//Vec3 ShadowToMe = ShadowLocation() - GetComponent<Transform>()->GetPosition();
		GetComponent<Transform>()->SetPosition(ShadowLocation());
	}

	//物体の位置から、影の位置を導き出す
	Vec3 ShadowObject::ShadowLocation() {
		//実体ブロックのポジション
		auto ObjPos = m_Obj.GetComponent<Transform>()->GetPosition();
		//マルチライトを取得
		auto MultiLightPtr = dynamic_pointer_cast<MultiLight>(GetStage()->GetLight());
		Vec3 LightPos;
		if (MultiLightPtr) {
			//メインライトを持ってくる
			auto mainIndex = MultiLightPtr->GetMainIndex();
			//メインライトのポジションを出す
			LightPos = MultiLightPtr->GetLight(mainIndex).m_Directional;
		}

		auto LightHeight = AddComponent<Shadowmap>()->GetLightHeight();
		//ライトと実体ブロックのXYZの差を出す
		float m_X = LightPos.x * LightHeight - ObjPos.x;
		float m_Y = LightPos.y * LightHeight - ObjPos.y;
		float m_Z = -LightPos.z * LightHeight - (-ObjPos.z);
		auto AngleX = atan2(LightPos.x, LightPos.z);
		auto AngleY = atan2(LightPos.y, LightPos.z);

		//実体ブロックから壁までのY距離を単位変位値に乗算して、実体ブロックからの影のXYのずれを算出し代入
		Vec3 m_kagePos;
		m_kagePos.x = ObjPos.x - ObjPos.z * AngleX;
		m_kagePos.y = ObjPos.y - ObjPos.z * AngleY;
		m_kagePos.z = 0;

		return m_kagePos;
	}
}