/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class WhiteCube : public GameObject {
		Vec3 m_StartScale;
		Quat m_StartQt;
		Vec3 m_StartPos;
		shared_ptr<MeshResource> m_MeshResource;

		shared_ptr<Rigidbody> m_Rigidbody;

		bool m_MoveFlag;
		bool m_HengMoveFlag;
		bool m_VerticalMoveFlag;
		Vec3 m_Speed;
		//�Z��������
		float m_alpha;

		float m_HengTimer;
		float m_VerticalTimer;
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
		WhiteCube(const shared_ptr<Stage>& StagePtr,
			const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos, const Vec3& StartSpeed, const bool& Move);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~WhiteCube() {}
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

		//virtual  const Light& OnGetDrawLight() const override {

		//}
	};
	class BlueCube : public GameObject {
		Vec3 m_StartScale;
		Quat m_StartQt;
		Vec3 m_StartPos;
		shared_ptr<MeshResource> m_MeshResource;

		shared_ptr<Rigidbody> m_Rigidbody;

		bool m_MoveFlag;
		bool m_HengMoveFlag;
		bool m_VerticalMoveFlag;
		Vec3 m_Speed;
		//�Z��������
		float m_alpha;

		float m_HengTimer;
		float m_VerticalTimer;
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
		BlueCube(const shared_ptr<Stage>& StagePtr,
			const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos, const Vec3& StartSpeed, const bool& Move);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~BlueCube() {}
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

		//virtual  const Light& OnGetDrawLight() const override {

		//}
	};
	class YellowCube : public GameObject {
		Vec3 m_StartScale;
		Quat m_StartQt;
		Vec3 m_StartPos;
		shared_ptr<MeshResource> m_MeshResource;

		shared_ptr<Rigidbody> m_Rigidbody;

		bool m_MoveFlag;
		bool m_HengMoveFlag;
		bool m_VerticalMoveFlag;
		Vec3 m_Speed;
		//�Z��������
		float m_alpha;

		float m_HengTimer;
		float m_VerticalTimer;
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
		YellowCube(const shared_ptr<Stage>& StagePtr,
			const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos, const Vec3& StartSpeed, const bool& Move);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~YellowCube() {}
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

		//virtual  const Light& OnGetDrawLight() const override {

		//}
	};
	class Goal : public GameObject {
		Vec3 m_StartScale;
		Quat m_StartQt;
		Vec3 m_StartPos;
		shared_ptr<MeshResource> m_MeshResource;
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
		Goal(const shared_ptr<Stage>& StagePtr,
			const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Goal() {}
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

		//virtual  const Light& OnGetDrawLight() const override {

		//}
	};

	//--------------------------------------------------------------------------------------
	///	��C�̌��̃I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class CannonBase : public GameObject {
		Vec3 m_StartScale;
		Quat m_StartQt;
		Vec3 m_StartPos;
		shared_ptr<MeshResource> m_MeshResource;

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
		CannonBase(const shared_ptr<Stage>& StagePtr,
			const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~CannonBase() {}
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

		//virtual  const Light& OnGetDrawLight() const override {

		//}
	};
	//--------------------------------------------------------------------------------------
	///	��C�̌��̃I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class CannonBaseR : public GameObject {
		Vec3 m_StartScale;
		Quat m_StartQt;
		Vec3 m_StartPos;
		shared_ptr<MeshResource> m_MeshResource;

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
		CannonBaseR(const shared_ptr<Stage>& StagePtr,
			const Vec3& StartScale, const Quat& StartQt, const Vec3& StartPos);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~CannonBaseR() {}
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
	};


	//--------------------------------------------------------------------------------------
	///	Paper
	//--------------------------------------------------------------------------------------
	class StageLight : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:
		//�\�z�Ɣj��
		StageLight(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~StageLight();
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;

	};

}
//end basecross
