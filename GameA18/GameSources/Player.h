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
		//���̎擾��
		int m_Key;
		//�f�[�^�ƃQ�[���Ƃ̕ϊ��s��
		Mat4x4 m_ToAnimeMatrixLeft;
		Mat4x4 m_ToAnimeMatrixRight;
		//���S����̂��߂�OBB
		OBB m_DieOBB;
		//���S��Ԃ����ϐ�[1:���E]
		int m_Death;

		bool m_GameOverFlag;

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

		//�v���C���[��HP
		void PlayerHP();

		//���ɐG�ꂽ�Ƃ��Ɏg���Am_Key�̒l�𑝂₷
		void AddKey() { m_Key += 1; }
		//m_Key�̒l���擾����
		int GetKey() { return m_Key; }
		//m_Death�̒l���擾����
		int GetDeath() { return m_Death; }

		//GameOverScene���Ăяo��
		void GoGameOverScene();
		//GameClearScene���Ăяo��
		void GoGameClearScene();
		//�S�[���ɓ��������ɌĂԁA�N���A���o������
		void InGoal();

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
		//�Q�[���I�[�o�[�Ǘ�
		void SetGameOverFlag(bool f) { m_GameOverFlag = f; }
		bool GetGameOverFlag() { return m_GameOverFlag; }
	};

	//--------------------------------------------------------------------------------------
	//	class WaitState : public ObjState<Player>;
	//	�p�r: �ҋ@���
	//--------------------------------------------------------------------------------------
	class WaitState : public ObjState<Player>{
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
	//--------------------------------------------------------------------------------------
	//	class WalkState : public ObjState<Player>;
	//	�p�r: �������
	//--------------------------------------------------------------------------------------
	class WalkState : public ObjState<Player>{
		WalkState() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		static shared_ptr<WalkState> Instance();
		//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class DiedState : public ObjState<Player>;
	//	�p�r: ���S���
	//--------------------------------------------------------------------------------------
	class DiedState : public ObjState<Player>{
		DiedState() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		static shared_ptr<DiedState> Instance();
		//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class GoalState : public ObjState<Player>;
	//	�p�r: �S�[�����
	//--------------------------------------------------------------------------------------
	class GoalState : public ObjState<Player> {
		GoalState() {}
	public:
		//�X�e�[�g�̃C���X�^���X�擾
		static shared_ptr<GoalState> Instance();
		//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};


}
//end basecross

