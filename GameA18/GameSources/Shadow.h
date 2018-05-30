#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class ShadowObject : public GameObject;
	//	�p�r: �I�u�W�F�N�g�̉e
	//--------------------------------------------------------------------------------------
	class ShadowObject : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		//�Ή��������ԃI�u�W�F�N�g�̃|�C���^
		GameObject& m_Obj;
		//�X�P�[����Z�̌Œ�l
		float m_ScaleZ;
	public:
		//�\�z�Ɣj��
		ShadowObject(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			GameObject& Obj
			);

		virtual ~ShadowObject();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate();
		virtual void OnUpdate2();
		//�e�̏ꏊ���v�Z����
		Vec3 ShadowLocation();
	};

	//--------------------------------------------------------------------------------------
	//	class ShadowObject2 : public GameObject;
	//	�p�r: �I�u�W�F�N�g�̉e
	//--------------------------------------------------------------------------------------
	class ShadowObject2 : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		//�Ή��������ԃI�u�W�F�N�g�̃|�C���^
		GameObject& m_Obj;
		//�X�P�[����Z�̌Œ�l
		float m_ScaleZ;
	public:
		//�\�z�Ɣj��
		ShadowObject2(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			GameObject& Obj
		);

		virtual ~ShadowObject2();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate();
		virtual void OnUpdate2();
		//�e�̏ꏊ���v�Z����
		Vec3 ShadowLocation();
	};
	//------------------------------------------------------------------------------------------
	///�S�[���̖���������e
	//------------------------------------------------------------------------------------------
	class ShadowGoal : public SS5ssae {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		GameObject& m_Obj;
		//�X�P�[����Z�̌Œ�l
		float m_ScaleZ;

		shared_ptr<MeshResource> m_MeshResource;
		Mat4x4 m_ToAnimeMatrix;

		bool flag;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	StartScale	�����X�P�[��
		@param[in]	StartQt	������]
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		ShadowGoal(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
			const Vec3& m_Scale, const Vec3& Rotation, GameObject& Obj);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~ShadowGoal() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;

		void OnTriggerEnter();

		//�e�̏ꏊ���v�Z����
		Vec3 ShadowLocation();
	};
	//------------------------------------------------------------------------------------------
	///���̖���������e
	//------------------------------------------------------------------------------------------
	class ShadowKey : public SS5ssae {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		GameObject& m_Obj;
		//�X�P�[����Z�̌Œ�l
		float m_ScaleZ;
		shared_ptr<MeshResource> m_MeshResource;
		Mat4x4 m_ToAnimeMatrix;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		@param[in]	StartScale	�����X�P�[��
		@param[in]	StartQt	������]
		@param[in]	StartPos	�����ʒu
		*/
		//--------------------------------------------------------------------------------------
		ShadowKey(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
			const Vec3& m_Scale, const Vec3& Rotation, GameObject& Obj);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~ShadowKey() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;

		void OnTriggerEnter();

		//�e�̏ꏊ���v�Z����
		Vec3 ShadowLocation();
	};

}