#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//���o�p�ւ���
	//--------------------------------------------------------------------------------------
	DirectingRing::DirectingRing(const shared_ptr<Stage>& StagePtr, Vec3 position,Vec3 scale, Vec3 shift,wstring texture)
		: GameObject(StagePtr), m_Position(position),m_Scale(scale), m_Shift(shift),m_Texture(texture)
	{}
	DirectingRing::~DirectingRing() {};
	void DirectingRing::OnCreate() {
		auto Trans = GetComponent<Transform>();
		//���S�_�����炷
		m_Position += m_Shift;
		Trans->SetWorldPosition(m_Position);
		Trans->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		Trans->SetScale(m_Scale);

		//���_�z��
		vector<VertexPositionNormalTexture> vertices;
		//�C���f�b�N�X���쐬���邽�߂̔z��
		vector<uint16_t> indices;
		//Square�̍쐬(�w���p�[�֐��𗘗p)
		MeshUtill::CreateSquare(1.0f, vertices, indices);

		//���㒸�_
		vertices[0].textureCoordinate = Vec2(0, 0);
		//�E�㒸�_
		vertices[1].textureCoordinate = Vec2(1, 0);
		//�������_
		vertices[2].textureCoordinate = Vec2(0, 1.0f);
		//�E�����_
		vertices[3].textureCoordinate = Vec2(1, 1.0f);
		//���_�̌^��ς����V�������_���쐬
		vector<VertexPositionColorTexture> new_vertices;
		for (auto& v : vertices) {
			VertexPositionColorTexture nv;
			nv.position = v.position;
			nv.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
			nv.textureCoordinate = v.textureCoordinate;
			new_vertices.push_back(nv);
		}
		//�V�������_���g���ă��b�V�����\�[�X�̍쐬
		m_SquareMeshResource = MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true);

		auto DrawComp = AddComponent<PCTStaticDraw>();
		DrawComp->SetMeshResource(m_SquareMeshResource);
		DrawComp->SetTextureResource(m_Texture);
		SetAlphaActive(true);
		auto act = AddComponent<Action>();
		//�������傫������
		act->AddScaleTo(1.0f, Vec3(m_Scale.x * 1.5f, m_Scale.y * 1.5f, 0.1f), Lerp::Linear);
		act->Run();
	}
	void DirectingRing::OnUpdate() {
		m_Time += App::GetApp()->GetElapsedTime();
		if (m_Time >= 0.3f) {
			//��������������
			GetComponent<PCTStaticDraw>()->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.3 - m_Time));
			//�ݒ肵���傫���܂ő傫���Ȃ�����
			if (GetComponent<Action>()->GetArrived()) {
				//������
				GetStage()->RemoveGameObject<DirectingRing>(GetThis<DirectingRing>());
			}
		}
	}

}