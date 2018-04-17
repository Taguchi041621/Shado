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
		PtrTransform->SetPosition(0,0,-0.1);
		PtrTransform->SetScale(0.25,0.5,0.25);

		//タグ
		AddTag(L"KeyItem");
		//描画コンポーネントの設定
		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//描画するテクスチャを設定
		PtrDraw->SetTextureResource(L"SKY_TX");


		//auto Coll = AddComponent<CollisionObb>();
		//Coll->SetFixed(true);
		//auto PtrRegid = AddComponent<Rigidbody>();

		auto PtrCol = AddComponent<Collision>();
		PtrCol->SetIsHitAction(IsHitAction::None);

		//影をつける
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
	}
}