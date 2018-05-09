#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	��
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

		//�^�O
		AddTag(L"KeyItem");
		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//�`�悷��e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"SKY_TX");

		auto group = GetStage()->GetSharedObjectGroup(L"KeyGroup");
		group->IntoGroup(GetThis<KeyItem>());
		//auto PtrRegid = AddComponent<Rigidbody>();

		//auto PtrCol = AddComponent<CollisionSphere>();
		//PtrCol->SetIsHitAction(IsHitAction::None);

		//�e������
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
	}

	void KeyItem::OnUpdate()
	{
		OnTriggerEnter();
	}
	//�������������Ƃ�
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