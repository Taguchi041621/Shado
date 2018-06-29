#pragma once
#include "stdafx.h"

namespace basecross
{
	class StageSelect : public Stage
	{
		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		wstring m_StopNowMusic;
		//�r���[�̍쐬
		void CreateViewLight();
		//�X�v���C�g�̍쐬
		void CreateTitleSprite();
		//�g�̍쐬
		void CreateFrame();

		//�t�F�[�h�̍쐬
		void CreateFadeOutSprite();
		void CreateFadeSprite();
		bool m_SelectFlag;

		//�h�A
		void CreateDoor();
		//�X�e�[�W�ԍ��̍쐬
		void StageNumberSprite();

		int m_StageNumber;
		bool onectrl;

		int m_MaxStageNumber;
		
		float m_CoolTime;
		wstring DataDir;

	public:
		//�\�z�Ɣj��
		StageSelect() :Stage() {}
		virtual ~StageSelect() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		void SetNowMusic(wstring NowMusic) {
			m_StopNowMusic = NowMusic;
		}
		wstring GetNowMusic() {
			return m_StopNowMusic;
		}
	};

	//--------------------------------------------------------------------------------------
	//	Door
	//--------------------------------------------------------------------------------------
	class StageSelectDoor : public SS5ssae {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		//�X�P�[����Z�̌Œ�l
		float m_ScaleZ;
		//���g�̔ԍ�������
		wstring m_DoorNum;
		//���̃I�u�W�F�N�g�݂̂Ŏg�p����X�N�G�A���b�V��
		shared_ptr<MeshResource> m_SquareMeshResource;
		Mat4x4 m_ToAnimeMatrix;

		shared_ptr<MultiAudioObject> m_AudioObjectPtr;
		wstring m_StopNowMusic;

		bool m_SelectFlag;
		bool m_OpenFlag;
		bool m_RemoveFlag;
		float m_RemoveTime = 0.0f;
	public:
		//�\�z�Ɣj��
		StageSelectDoor(const shared_ptr<Stage>& StagePtr,
			const wstring BaseDir,
			const Vec3& Scale,
			const Vec3& Position,
			const Vec3& Rotation,
			const wstring DoorNum
			);

		virtual ~StageSelectDoor();
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

		void SetSelectFlag(bool f) { m_SelectFlag = f; }
		bool GetSelectFlag() { return m_SelectFlag; }

		void SetRemoveFlag(bool f) { m_RemoveFlag = f; }
		//���̑傫���ς�
		float deflection = 0.001f;

		void Open();
		void StyleChange();
	};
}