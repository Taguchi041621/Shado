#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	鍵
	//--------------------------------------------------------------------------------------
	KeyItem::KeyItem(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_KeyPos(StartPos)
	{}
	void KeyItem::OnCreate()
	{
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetPosition(m_KeyPos);
		PtrTransform->SetScale(0.25,0.25,0.25);

		//タグ
		AddTag(L"KeyItem");
		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//描画するテクスチャを設定
		PtrDraw->SetTextureResource(L"SKY_TX");

		auto group = GetStage()->GetSharedObjectGroup(L"KeyGroup");
		group->IntoGroup(GetThis<KeyItem>());
		//auto PtrRegid = AddComponent<Rigidbody>();

		//auto PtrCol = AddComponent<CollisionSphere>();
		//PtrCol->SetIsHitAction(IsHitAction::None);

		//影をつける
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
	}

	void KeyItem::OnUpdate()
	{
		OnTriggerEnter();
	}
	//鍵が当たったとき
	void KeyItem::OnTriggerEnter()
	{
		SPHERE t;
		t.m_Center = this->GetComponent<Transform>()->GetPosition();
		t.m_Center.z = 0;
		t.m_Radius = 0.20;

		SPHERE p;
		p.m_Center = GetStage()->GetSharedGameObject<Player>(L"Player")->GetComponent<Transform>()->GetWorldPosition();
		p.m_Center.z = 0;
		p.m_Radius = 0.20;

		if (HitTest::SPHERE_SPHERE(t, p)){
			GetStage()->GetSharedGameObject<Player>(L"Player")->AddKey();
			GetStage()->RemoveGameObject<KeyItem>(GetThis<KeyItem>());
		}
	}
}