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
		PtrTransform->SetPosition(0,0,-0.1);
		PtrTransform->SetScale(0.25,0.5,0.25);

		//�^�O
		AddTag(L"KeyItem");
		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//�`�悷��e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"SKY_TX");


		//auto Coll = AddComponent<CollisionObb>();
		//Coll->SetFixed(true);
		//auto PtrRegid = AddComponent<Rigidbody>();

		auto PtrCol = AddComponent<Collision>();
		PtrCol->SetIsHitAction(IsHitAction::None);

		//�e������
		//auto ShadowPtr = AddComponent<Shadowmap>();
		//ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
	}
}