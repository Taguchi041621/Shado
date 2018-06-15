#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//���o�p�ւ���
	//--------------------------------------------------------------------------------------
	class DirectingRing : public GameObject {
		Vec3 m_Position;
		Vec3 m_Scale;
		//���o���o���I�u�W�F�N�g����ǂꂾ�����炷��������
		Vec3 m_Shift;
		float m_Time = 0;
		wstring m_Texture;
		shared_ptr<MeshResource> m_SquareMeshResource;
	public:
		DirectingRing(const shared_ptr<Stage>& StagePtr, Vec3 position,Vec3 scale, Vec3 shift,wstring texture);
		virtual ~DirectingRing();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate();
	};
}