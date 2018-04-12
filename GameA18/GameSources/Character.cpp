/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	����������
	//--------------------------------------------------------------------------------------
	WhiteCube::WhiteCube(const shared_ptr<Stage>& StagePtr,
		const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_StartScale(StartScale),
		m_StartQt(StartQt),
		m_StartPos(StartPos)
	{}

	void WhiteCube::OnCreate() {
		vector<VertexPositionNormalTexture> vertices;
		vector<VertexPositionNormal> new_vertices;

		vector<uint16_t> indices;
		MeshUtill::CreateCube(1.0f, vertices, indices);
		for (size_t i = 0; i < vertices.size(); i++) {
			VertexPositionNormal new_v;
			new_v.position = vertices[i].position;
			new_v.normal = vertices[i].normal;
			new_vertices.push_back(new_v);
		}
		m_MeshResource = MeshResource::CreateMeshResource(new_vertices, indices, false);

		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale);
		PtrTransform->SetQuaternion(m_StartQt);
		PtrTransform->SetPosition(m_StartPos);

		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		PtrDraw->SetMeshResource(m_MeshResource);

		//�e������
		auto ShadowPtr = AddComponent<Shadowmap>();
		ShadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		//--------------------------------------------------------
		GetStage()->AddGameObject<ShadowObject>(
			GetComponent<Transform>()->GetScale(),
			GetComponent<Transform>()->GetRotation(),
			L"DEFAULT_CUBE",
			*GetThis<GameObject>()
			);
	}
	void WhiteCube::OnUpdate() {
	}
	//--------------------------------------------------------------------------------------
	//	class ShadowObject : public GameObject;
	//	�p�r: �I�u�W�F�N�g�̉e
	//--------------------------------------------------------------------------------------
	ShadowObject::ShadowObject(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale, const Vec3& Rotation, const wstring& Mesh, GameObject& Obj)
		: GameObject(StagePtr),
		m_Scale(Scale), m_Rotation(Rotation), m_Mesh(Mesh), m_Obj(Obj)
	{
	}

	ShadowObject::~ShadowObject() {}
	//������
	void ShadowObject::OnCreate() {
		m_Scale.z = 0.1f;
		auto PtrTransform = AddComponent<Transform>();
		//�e�̃|�W�V�������o��
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
	//�ω�
	void ShadowObject::OnUpdate() {
		//Vec3 ShadowToMe = ShadowLocation() - GetComponent<Transform>()->GetPosition();
		GetComponent<Transform>()->SetPosition(ShadowLocation());
	}

	//���̂̈ʒu����A�e�̈ʒu�𓱂��o��
	Vec3 ShadowObject::ShadowLocation() {
		//���̃u���b�N�̃|�W�V����
		auto ObjPos = m_Obj.GetComponent<Transform>()->GetPosition();
		//�}���`���C�g���擾
		auto MultiLightPtr = dynamic_pointer_cast<MultiLight>(GetStage()->GetLight());
		Vec3 LightPos;
		if (MultiLightPtr) {
			//���C�����C�g�������Ă���
			auto mainIndex = MultiLightPtr->GetMainIndex();
			//���C�����C�g�̃|�W�V�������o��
			LightPos = MultiLightPtr->GetLight(mainIndex).m_Directional;
		}

		//���C�g�Ǝ��̃u���b�N��XYZ�̍����o��
		float m_X = LightPos.x - ObjPos.x;
		float m_Y = LightPos.y - ObjPos.y;
		float m_Z = LightPos.z - ObjPos.z;
		//XY�̍����AY�P���̕ω��ʂŏo��
		float m_DisplacementX = m_X / m_Z;
		float m_DisplacementY = m_Y / m_Z;
		//���̃u���b�N����ǂ܂ł�Y������P�ʕψʒl�ɏ�Z���āA���̃u���b�N����̉e��XY�̂�����Z�o�����
		Vec3 m_kagePos;
		m_kagePos.x = ObjPos.x + LightPos.x * m_DisplacementX;
		m_kagePos.y = ObjPos.y + LightPos.y * m_DisplacementY;
		m_kagePos.z = 0;

		return m_kagePos;
	}
}
//end basecross
