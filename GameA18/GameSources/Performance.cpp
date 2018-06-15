#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//演出用輪っか
	//--------------------------------------------------------------------------------------
	DirectingRing::DirectingRing(const shared_ptr<Stage>& StagePtr, Vec3 position,Vec3 scale, Vec3 shift,wstring texture)
		: GameObject(StagePtr), m_Position(position),m_Scale(scale), m_Shift(shift),m_Texture(texture)
	{}
	DirectingRing::~DirectingRing() {};
	void DirectingRing::OnCreate() {
		auto Trans = GetComponent<Transform>();
		//中心点をずらす
		m_Position += m_Shift;
		Trans->SetWorldPosition(m_Position);
		Trans->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		Trans->SetScale(m_Scale);

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
		DrawComp->SetTextureResource(m_Texture);
		SetAlphaActive(true);
		auto act = AddComponent<Action>();
		//少しずつ大きくする
		act->AddScaleTo(1.0f, Vec3(m_Scale.x * 1.5f, m_Scale.y * 1.5f, 0.1f), Lerp::Linear);
		act->Run();
	}
	void DirectingRing::OnUpdate() {
		m_Time += App::GetApp()->GetElapsedTime();
		if (m_Time >= 0.3f) {
			//少しずつ薄くする
			GetComponent<PCTStaticDraw>()->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.3 - m_Time));
			//設定した大きさまで大きくなったら
			if (GetComponent<Action>()->GetArrived()) {
				//消える
				GetStage()->RemoveGameObject<DirectingRing>(GetThis<DirectingRing>());
			}
		}
	}

}