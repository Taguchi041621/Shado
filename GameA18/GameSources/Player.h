/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�v���C���[
	//--------------------------------------------------------------------------------------
	class Player : public SS5ssae {

		shared_ptr< StateMachine<Player> >  m_StateMachine;	//�X�e�[�g�}�V�[��
		//�J������Z���̐؂�ւ�
		float CameraPosZ;
		//�J�����̐؂�ւ��Ɏg��
		int m_CameraNumber;
		//�v���C���[��HP
		int m_PlayerHP;
		//�ō����x
		float m_MaxSpeed;
		//������
		float m_Decel;
		//����
		float m_Mass;
		//������̕\��
		void DrawStrings();
		//�f�[�^�ƃQ�[���Ƃ̕ϊ��s��
		Mat4x4 m_ToAnimeMatrixLeft;
		Mat4x4 m_ToAnimeMatrixRight;
	public:
		//�\�z�Ɣj��
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		@param[in]	StagePtr	�X�e�[�W
		*/
		//--------------------------------------------------------------------------------------
		Player(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Player() {}
		//�A�N�Z�T
		//--------------------------------------------------------------------------------------
		/*!
		�R���g���[����������x�N�g���𓾂�
		*/
		//--------------------------------------------------------------------------------------
		float GetMoveVector(int LR) const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�ō����x�𓾂�
		@return	�ō����x
		*/
		//--------------------------------------------------------------------------------------
		float GetMaxSpeed() const {
			return m_MaxSpeed;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�����l�𓾂�
		@return	�����l
		*/
		//--------------------------------------------------------------------------------------
		float GetDecel() const {
			return m_Decel;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	���ʂ𓾂�
		@return	����
		*/
		//--------------------------------------------------------------------------------------
		float GetMass() const {
			return m_Mass;
		}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	����������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�X�V����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	��X�V����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate2() override;

		//�Փ˂����Ƃ�
		virtual void OnCollision(vector<shared_ptr<GameObject>>& OtherVec) override;
		//�Փ˂��Ă���Ƃ�
		virtual void OnCollisionExcute(vector<shared_ptr<GameObject>>& OtherVec) override;
		//�Փ˂��I�������
		virtual void OnCollisionExit(vector<shared_ptr<GameObject>>& OtherVec) override;


		//LR�������ꂽ�Ƃ��J������ς���
		void CameraChanger();

		//�v���C���[��HP
		void PlayerHP();

		//�A�N�Z�T
		shared_ptr< StateMachine<Player> > GetStateMachine() const {
			return m_StateMachine;
		}

		void AnimeChangeMotion(const wstring& key, bool looped);
		void LoopedAnimeUpdateMotion();

		//���[�V��������������֐��Q
		//�ړ����Č������ړ������ɂ���
		//�ړ�������Ԃ�
		float MoveRotationMotion();
	};

	//--------------------------------------------------------------------------------------
	//	class WaitState : public ObjState<Player>;
	//	�p�r: �ҋ@���
	//--------------------------------------------------------------------------------------
	class WaitState : public ObjState<Player>
	{
		WaitState() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		static shared_ptr<WaitState> Instance();
		//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};


}
//end basecross

