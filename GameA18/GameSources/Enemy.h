#pragma once
#include "stdafx.h"

namespace basecross {
	//------------------------------------------------------------------------------------------
	///�G(�e)
	//------------------------------------------------------------------------------------------
	class ShadowEnemy : public SS5ssae {
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
		ShadowEnemy(const shared_ptr<Stage>& StagePtr, const wstring BaseDir,
			const Vec3& m_Scale, const Vec3& Rotation, GameObject& Obj);
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~ShadowEnemy() {}
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
	///�G�̎���
	//------------------------------------------------------------------------------------------
	class Enemy : public GameObject {
		Vec3 m_KeyPos;
	public:
		Enemy(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos);
		virtual ~Enemy() {}
		//������
		virtual void OnCreate() override;

		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//	��C
	//--------------------------------------------------------------------------------------
	class Cannon : public SS5ssae {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		//�Ή��������ԃI�u�W�F�N�g�̃|�C���^
		GameObject& m_Obj;
		//�X�P�[����Z�̌Œ�l
		float m_ScaleZ;
		//���̃I�u�W�F�N�g�݂̂Ŏg�p����X�N�G�A���b�V��
		shared_ptr<MeshResource> m_SquareMeshResource;

		float m_CoolTime;
		bool m_BulletFlag;

		Mat4x4 m_ToAnimeMatrix;

		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		wstring m_StopNowMusic;

	public:
		//�\�z�Ɣj��
		Cannon(const shared_ptr<Stage>& StagePtr,
			const wstring BaseDir,
			const Vec3& Scale,
			const Vec3& Rotation,
			GameObject& Obj
		);

		virtual ~Cannon();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate();
		void SetNowMusic(wstring NowMusic) {
			m_StopNowMusic = NowMusic;
		}
		wstring GetNowMusic() {
			return m_StopNowMusic;
		}
		virtual void OnUpdate2();
		//�e�̏ꏊ���v�Z����
		Vec3 ShadowLocation();
	};

	//--------------------------------------------------------------------------------------
	//	�e
	//--------------------------------------------------------------------------------------

	class Bullet : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		//�X�P�[����Z�̌Œ�l
		float m_ScaleZ;
		//���̃I�u�W�F�N�g�݂̂Ŏg�p����X�N�G�A���b�V��
		shared_ptr<MeshResource> m_SquareMeshResource;
	public:
		//�\�z�Ɣj��
		Bullet(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);

		virtual ~Bullet();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate();
		virtual void OnUpdate2();
		void OnTriggerEnter();
	};
}