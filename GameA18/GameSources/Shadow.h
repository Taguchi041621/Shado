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
	//--------------------------------------------------------------------------------------
	//	class ShadowObject3 : public GameObject;
	//	�p�r: �I�u�W�F�N�g�̉e
	//--------------------------------------------------------------------------------------
	class ShadowObject3 : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		//�Ή��������ԃI�u�W�F�N�g�̃|�C���^
		GameObject& m_Obj;
		//�X�P�[����Z�̌Œ�l
		float m_ScaleZ;
	public:
		//�\�z�Ɣj��
		ShadowObject3(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			GameObject& Obj
		);

		virtual ~ShadowObject3();
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
		Mat4x4 m_ToAnimeMatrixDark;
		Mat4x4 m_ToAnimeMatrixLight;

		bool flag;
		bool m_LightFlag;
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
		//�S�[���ɔ��ł����t���O
		bool m_GoGoal = false;
		//�S�[���ɔ�ԑO�ɉ��ۂ̌��ݎ���
		float m_spin = 0.0f;
		//�⊮�̍ۂɎg�����ݎ���
		float m_Lerp = 0.0f;
		//�o�H���o�����߂̓_
		Vec3 p0,p1,p2,p3;
		shared_ptr<MeshResource> m_MeshResource;
		Mat4x4 m_ToAnimeMatrix;

		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		wstring m_StopNowMusic;

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
		void SetNowMusic(wstring NowMusic) {
			m_StopNowMusic = NowMusic;
		}
		wstring GetNowMusic() {
			return m_StopNowMusic;
		}

		void OnTriggerEnter();

		//�e�̏ꏊ���v�Z����
		Vec3 ShadowLocation();
	};

}