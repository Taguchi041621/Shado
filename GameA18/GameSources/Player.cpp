/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{


	//--------------------------------------------------------------------------------------
	//	class Player : public GameObject;
	//	�p�r: �v���C���[
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	Player::Player(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir,const Vec3 pos) :
		SS5ssae(StagePtr, BaseDir, L"Idea1.ssae", L"Wait"),m_Position(pos),
		m_MaxSpeed(80.0f),	//�ō����x
		m_Decel(0.65f),	//�����l
		m_Mass(0.5f),	//����
		m_Key(0),		//���̎擾��
		m_Death(0),		//������0(����)��
		m_FallSpeedFirst(-7.4f)
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.05f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(-0.5f, 0.03f, 0.0f)
		);
		m_ToAnimeMatrixRight.affineTransformation(
			Vec3(-0.1f, 0.05f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.5f, 0.03f, 0.0f)
		);
	}
	//----------------------------------------------------------------------------------------------------------
	//������
	//----------------------------------------------------------------------------------------------------------
	void Player::OnCreate() {
		m_GameClearFlag = false;
		m_GameOverFlag = false;
		m_ParentFlag = false;
		m_StandFlag = false;
		m_DamageFlag = false;
		m_FadeFlag = false;
		//�����ʒu�Ȃǂ̐ݒ�
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(0.80f, 1.60f, 0.5f);
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(m_Position);

		//�e�N���X�̃N���G�C�g���Ă�
		SS5ssae::OnCreate();
		//�l�͕b������̃t���[����
		SetFps(49.0f);

		//���ƂȂ�I�u�W�F�N�g����A�j���[�V�����I�u�W�F�N�g�ւ̍s��̐ݒ�
		SetToAnimeMatrix(m_ToAnimeMatrixRight);

		//Rigidbody������
		auto PtrRedid = AddComponent<Rigidbody>();
		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionObb>();
		PtrCol->SetIsHitAction(IsHitAction::None);
		//�f�o�b�O�p�����������
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		//Action������
		//���C���[�ύX�p
		auto PtrAction = AddComponent<Action>();
		//�A�N�V�����͖����ɂ��Ă���
		PtrAction->SetUpdateActive(false);

		//�X�e�[�g�}�V���̍\�z
		m_StateMachine = make_shared< StateMachine<Player> >(GetThis<Player>());
		//�ŏ��̃X�e�[�g��WaitState�ɐݒ�
		m_StateMachine->SetCurrentState(WaitState::Instance());
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		if (ScenePtr->GetRespawnFlag())
		{
			m_StateMachine->ChangeState(StandState::Instance());
		}
		//WaitState�̏��������s���s��
		m_StateMachine->GetCurrentState()->Enter(GetThis<Player>());

	}

	//----------------------------------------------------------------------------------------------------------
	//�X�V
	//----------------------------------------------------------------------------------------------------------
	void Player::OnUpdate() {
		//�X�e�[�g�}�V����Update���s��
		//���̒��ŃX�e�[�g�̐؂�ւ����s����
		m_StateMachine->Update();
	}

	void Player::OnUpdate2() {
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		auto PtrRedit = GetComponent<Rigidbody>();
		if (m_ParentFlag && !m_GameOverFlag && !m_GameClearFlag && ScenePtr->GetStartFlag() && !m_StandFlag && !m_DamageFlag) {
			//�v���C���[�̈ړ�
			MoveRotationMotion();
		}
		//�e�ɏ���Ă��Ȃ����痎����
		else if (!m_ParentFlag) {
			PtrRedit->SetVelocityZero();
			GetComponent<Rigidbody>()->SetVelocity(Vec3(0.0f, m_FallSpeed, 0.0f));
			m_FallSpeed += -0.08f;
		}
		PlayerHP();
	}

	//----------------------------------------------------------------------------------------------------------
	//���X�e�B�b�N
	//----------------------------------------------------------------------------------------------------------
	float Player::GetMoveLeftVectorX() const {
		float MoveX = 0;

		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		//�ڑ����ĂȂ�������0�Ԃ�
		if (!CntlVec.bConnected) {
			return 0;
		}
		if (CntlVec.fThumbLX != 0) {
			//�R���g���[���̌����v�Z
			MoveX = CntlVec.fThumbLX;
		}
		return MoveX;
	}
	//----------------------------------------------------------------------------------------------------------
	//�E�X�e�B�b�N
	//----------------------------------------------------------------------------------------------------------
	float Player::GetMoveRightVectorX() const{
		float MoveX = 0;

		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		//�ڑ����ĂȂ�������0�Ԃ�
		if (!CntlVec.bConnected) {
			return 0;
		}
		if (CntlVec.fThumbRX != 0) {
			//�R���g���[���̌����v�Z
			MoveX = CntlVec.fThumbRX;
		}
		return MoveX;
	}

	//----------------------------------------------------------------------------------------------------------
	//�ړ����Č������ړ������ɂ���
	//�ړ�������Ԃ�
	//----------------------------------------------------------------------------------------------------------
	float  Player::MoveRotationMotion() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto MoveX = GetMoveLeftVectorX();
		//Transform
		auto PtrTransform = GetComponent<Transform>();
		//Rigidbody�����o��
		auto PtrRedit = GetComponent<Rigidbody>();
		//���݂̑��x�����o��
		auto Velo = PtrRedit->GetVelocity().x;
		auto VeloY = PtrRedit->GetVelocity().y;
		//�ړI�n���ō����x���|���ċ��߂�
		auto Target = MoveX * m_MaxSpeed;
		//�ړI�n�Ɍ��������߂ɗ͂̂�����������v�Z����
		//Force�̓t�H�[�X�ł���
		auto Force = Target - Velo;
		//�����x�����߂�
		auto Accel = Force / m_Mass;
		//�^�[�����Ԃ��|�������̂𑬓x�ɉ��Z����
		Velo += (Accel * ElapsedTime);
		//��������
		Velo *= m_Decel;
		//���x��ݒ肷��
		Vec3 VecVelo(Velo, VeloY, 0);
		PtrRedit->SetVelocity(VecVelo);
		////��]�̌v�Z

		//���ƂȂ�I�u�W�F�N�g����A�j���[�V�����I�u�W�F�N�g�ւ̍s��̐ݒ�
		//Transform�̃X�P�[�����O��-1�ɂ���ƏՓ˔��肪���܂������Ȃ��̂�
		//SpriteStdio�̕��������ύX����
		if (MoveX > 0.0f) {
			SetToAnimeMatrix(m_ToAnimeMatrixRight);
			m_RightOrLeft = PlayerDirection::RIGHT;
		}
		else if (MoveX < 0.0f) {
			SetToAnimeMatrix(m_ToAnimeMatrixLeft);
			m_RightOrLeft = PlayerDirection::LEFT;
		}
		//MoveX��Ԃ�
		return MoveX;
	}

	//----------------------------------------------------------------------------------------------------------
	//�Փˎ�
	//----------------------------------------------------------------------------------------------------------
	void Player::OnCollision(vector<shared_ptr<GameObject>>& OtherVec) {
		auto playerTrans = GetComponent<Transform>();
		for (auto &obj : OtherVec) {
			//�V���h�E�I�u�W�F�N�g�����o
			auto ShadowPtr = dynamic_pointer_cast<ShadowObject>(obj);
			//���������̂��V���h�E�I�u�W�F�N�g��
			if (ShadowPtr) {
				Extrusion(ShadowPtr);//�����o���֐�
				FindParent(ShadowPtr);//�e�ɂ��邩���ׂ�֐�
			}
		}
	}

	//----------------------------------------------------------------------------------------------------------
	//�Փ˂��Ă��鎞
	//----------------------------------------------------------------------------------------------------------
	void Player::OnCollisionExcute(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto &obj : OtherVec) {
			auto ShadowPtr = dynamic_pointer_cast<ShadowObject>(obj);
			if (ShadowPtr) {
				Extrusion(ShadowPtr);
				FindParent(ShadowPtr);
			}
		}
	}

	//----------------------------------------------------------------------------------------------------------
	//�Փ˂��Ȃ��Ȃ�����
	//----------------------------------------------------------------------------------------------------------
	void Player::OnCollisionExit(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto &obj : OtherVec) {
			if (obj == GetComponent<Transform>()->GetParent()) {
				//�e�Ɨ���Ă��邩�����o
				GetComponent<Transform>()->ClearParent();
				m_ParentFlag = false;
				//�����X�s�[�h�̏�����
				m_FallSpeed = m_FallSpeedFirst;
			}
		}
	}
	//----------------------------------------------------------------------------------------------------------
	//�e�ɂȂ�����𖞂����Ă��邩�𒲂ׂāA�������Ă�����e�ɂ���
	//----------------------------------------------------------------------------------------------------------
	void Player::FindParent(const shared_ptr<GameObject>& OtherVec) {
		auto playerTrans = GetComponent<Transform>();
		auto playerPos = playerTrans->GetWorldPosition();
		auto playerSca = playerTrans->GetScale();
		auto ObjPos = OtherVec->GetComponent<Transform>()->GetWorldPosition();
		auto ObjSca = OtherVec->GetComponent<Transform>()->GetScale() * 0.5f;
		//�e�̏�ɏ���Ă��邩�𒲂ׂ�
		if ((ObjPos.x - ObjSca.x) < playerPos.x + playerSca.x * 0.5f
			&& (ObjPos.x + ObjSca.x) > playerPos.x - playerSca.x * 0.5f
			&& ObjPos.y + ObjSca.y <= playerPos.y - playerTrans->GetScale().y * 0.48f) {
			if (!playerTrans->GetParent()) {
				playerTrans->SetParent(OtherVec);
				m_ParentFlag = true;
			}
		}
	}
	//----------------------------------------------------------------------------------------------------------
	//�����o��
	//----------------------------------------------------------------------------------------------------------
	void Player::Extrusion(const shared_ptr<GameObject>& OtherVec) {
		auto playerPos = GetComponent<Transform>()->GetWorldPosition();
		auto playerScale = GetComponent<Transform>()->GetScale() * 0.5f;
		auto otherPos = OtherVec->GetComponent<Transform>()->GetWorldPosition();
		auto otherScale = OtherVec->GetComponent<Transform>()->GetScale() * 0.5f;
		//���@�Ƒ��肪�Փ˂��Ă��邩�̔���
		if (playerPos.y - playerScale.y < otherPos.y + otherScale.y && playerPos.y + playerScale.y > otherPos.y - otherScale.y &&
			playerPos.x - playerScale.x < otherPos.x + otherScale.x && playerPos.x + playerScale.x > otherPos.x - otherScale.x) {
			//���S����p��OBB
			//�G
			OBB p;
			p.m_Center = otherPos;
			p.m_Size = otherScale;
			//�C�f�A
			OBB m;
			m.m_Center = GetComponent<Transform>()->GetWorldPosition();
			m.m_Size = GetComponent<Transform>()->GetScale() * 0.3f;
			m.m_Size.z = 1.0f;

			//�e�����̂߂荞�݂��m�F
			float diff[4] = {
				(otherPos.x + otherScale.x) - (playerPos.x - playerScale.x), // �E
				(playerPos.x + playerScale.x) - (otherPos.x - otherScale.x), // ��
				(otherPos.y + otherScale.y) - (playerPos.y - playerScale.y), // ��
				(playerPos.y + playerScale.y) - (otherPos.y - otherScale.y), // ��
			};
			// ���ʂ̋������ŏ��ɂȂ��Ă���v�f��������
			int min = 0;
			for (int i = 0; i < 4; i++) {
				if (diff[i] < diff[min]) {
					min = i;
				}
			}
			//�����Ƃ��߂荞�݂����Ȃ��ʂɉ����Ԃ�
			switch (min) {
			case 0:
				//�i������������o��
				if (diff[2] < 0.4f && diff[2] >0.0f && GetMoveLeftVectorX() < -0.6f) {
					playerPos.y += diff[2];
					break;
				}
				playerPos.x += diff[min];
				//�����S�����肪���������玀��
				if (HitTest::OBB_OBB(p, m)) {
					m_Death = 1;
				}
				break;
			case 1:
				//�i������������o��
				if (diff[2] < 0.4f && diff[2] > 0.0f && GetMoveLeftVectorX() > 0.6f) {
					playerPos.y += diff[2];
					break;
				}
				playerPos.x -= diff[min];
				//�����S�����肪���������玀��
				if (HitTest::OBB_OBB(p, m)) {
					m_Death = 1;
				}
				break;
			case 2:
				playerPos.y += diff[min];
				break;
			case 3:
				//playerPos.y -= diff[min];
				//�����S�����肪���������玀��
				if (HitTest::OBB_OBB(p, m)) {
					m_Death = 1;
				}
				break;
			default:
				break;
			}
			GetComponent<Transform>()->SetWorldPosition(playerPos);
		}
	}

	//----------------------------------------------------------------------------------------------------------
	// ���S�̔���
	//----------------------------------------------------------------------------------------------------------
	void Player::PlayerHP() {
		auto PlayerPos = this->GetComponent<Transform>()->GetWorldPosition();
		//������
		if (PlayerPos.y < -25.0f && !m_GameOverFlag){
			m_GameOverFlag = true;
			m_FadeFlag = true;
		}
	}
	//----------------------------------------------------------------------------------------------------------
	//���n�����Ƃ��̉��o
	//----------------------------------------------------------------------------------------------------------
	void Player::LandingDirecting() {
		GetStage()->AddGameObject<DirectingRing>(GetComponent<Transform>()->GetWorldPosition(),
			Vec3(1.0f, 1.0f, 0.05f), Vec3(0.0f, -0.7f, 0.0f), L"Smoke_Black_TX");
	}
	//----------------------------------------------------------------------------------------------------------
	//GameOverScene�Ɉڍs����
	//----------------------------------------------------------------------------------------------------------
	void Player::GoGameOverScene() {
		m_GameOverFlag = true;
	}
	//----------------------------------------------------------------------------------------------------------
	//GameOverScene�Ɉڍs����
	//----------------------------------------------------------------------------------------------------------
	void Player::GoGameClearScene() {
		m_GameClearFlag = true;
	}
	//----------------------------------------------------------------------------------------------------------
	// �X�e�[�g���S�[���X�e�[�g�ɐ؂�ւ���
	//----------------------------------------------------------------------------------------------------------
	void Player::InGoal() {
		GetStateMachine()->ChangeState(GoalState::Instance());
	}
	//----------------------------------------------------------------------------------------------------------
	//�A�j���[�V�������X�V����
	//----------------------------------------------------------------------------------------------------------
	void Player::LoopedAnimeUpdateMotion() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//�A�j���[�V�������X�V����
		UpdateAnimeTime(ElapsedTime);
	}
	//----------------------------------------------------------------------------------------------------------
	//�A�j���[�V������؂�ւ���
	//----------------------------------------------------------------------------------------------------------
	void Player::AnimeChangeMotion(const wstring& key, bool looped) {
		ChangeAnimation(key);
		SetLooped(looped);
	}
	//----------------------------------------------------------------------------------------------------------
	//�U�����󂯂��Ƃ��̉��o
	//----------------------------------------------------------------------------------------------------------
	void Player::Damage(CannonBase::CanonDirection LR) {
		if (!m_DamageFlag) {
			m_DamageFlag = true;
			auto PtrRedit = GetComponent<Rigidbody>();
			PtrRedit->SetVelocityZero();
			if (LR == CannonBase::CanonDirection::LEFT) {
				//���ɔ��
				GetComponent<Rigidbody>()->SetVelocity(Vec3(-3.0f, 0, 0.0f));
			}
			else {
				//�E�ɔ��
				GetComponent<Rigidbody>()->SetVelocity(Vec3(3.0f, 0, 0.0f));
				if (m_RightOrLeft == PlayerDirection::LEFT) {
					m_RightOrLeft = PlayerDirection::RIGHT;
				}
				else {
					m_RightOrLeft = PlayerDirection::LEFT;
				}
			}
			GetStateMachine()->ChangeState(DamageState1::Instance());
		}
	}

	//--------------------------------------------------------------------------------------
	//	class WaitState : public ObjState<Player>;
	//	�p�r: �ҋ@���
	//--------------------------------------------------------------------------------------
	shared_ptr<WaitState> WaitState::Instance() {
		static shared_ptr<WaitState> instance;
		if (!instance) {
			instance = shared_ptr<WaitState>(new WaitState);
		}
		return instance;
	}
	void WaitState::Enter(const shared_ptr<Player>& Obj) {
		Obj->AnimeChangeMotion(L"Wait_1", true);
		Obj->SetFps(49.0f);
	}
	void WaitState::Execute(const shared_ptr<Player>& Obj) {
		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		//�ׂ�Ď��񂾂�Died�A�j���𗬂�
		if (Obj->GetDeath() == 1) {
			Obj->GetStateMachine()->ChangeState(DiedState::Instance());
		}
		//�e�����Ȃ�������Fall�A�j���𗬂�
		if (!Obj->GetParentFlag()) {
			Obj->GetStateMachine()->ChangeState(FallState::Instance());
		}
		//���X�e�B�b�N�̒l��0�ȊO�Ȃ�Walk�A�j���𗬂�
		if (Obj->GetParentFlag() && Obj->GetMoveLeftVectorX()&& ScenePtr->GetStartFlag()) {
			Obj->GetStateMachine()->ChangeState(WalkState::Instance());
		}
	}
	void WaitState::Exit(const shared_ptr<Player>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class FallState : public ObjState<Player>;
	//	�p�r: �����Ă�Ƃ�
	//--------------------------------------------------------------------------------------
	shared_ptr<FallState> FallState::Instance() {
		static shared_ptr<FallState> instance;
		if (!instance) {
			instance = shared_ptr<FallState>(new FallState);
		}
		return instance;
	}
	void FallState::Enter(const shared_ptr<Player>& Obj) {
		Obj->AnimeChangeMotion(L"Down_loop", true);
		m_Timer = 0;
		m_FallFlag = false;
	}
	void FallState::Execute(const shared_ptr<Player>& Obj) {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_Timer += ElapsedTime;

		if (m_Timer >= 0.7f){
			Obj->AnimeChangeMotion(L"Fall", false);
			m_FallFlag = true;
			m_Timer = -10;
		}
		//�ׂ�Ď��񂾂�Died�A�j���𗬂�
		if (Obj->GetDeath() == 1) {
			Obj->GetStateMachine()->ChangeState(DiedState::Instance());
		}

		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
		if (Obj->GetParentFlag() && m_FallFlag) {
			//������
			Obj->LandingDirecting();
			Obj->GetStateMachine()->ChangeState(StandState::Instance());
		}
		else if (Obj->GetParentFlag()) {
			Obj->GetStateMachine()->ChangeState(LandingState::Instance());
		}
	}
	void FallState::Exit(const shared_ptr<Player>& Obj) {
		Obj->GetComponent<Rigidbody>()->SetVelocityZero();
	}
	//--------------------------------------------------------------------------------------
	//	class LandingState : public ObjState<Player>;
	//	�p�r: ���n
	//--------------------------------------------------------------------------------------
	shared_ptr<LandingState> LandingState::Instance() {
		static shared_ptr<LandingState> instance;
		if (!instance) {
			instance = shared_ptr<LandingState>(new LandingState);
		}
		return instance;
	}
	void LandingState::Enter(const shared_ptr<Player>& Obj) {
		Obj->AnimeChangeMotion(L"Down_landing", false);

			m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
			m_AudioObjectPtr->AddAudioResource(L"se5");
			m_AudioObjectPtr->Start(L"se5", XAUDIO2_NO_LOOP_REGION, 0.32f);
			Obj->SetNowMusic(L"se5");
	}
	void LandingState::Execute(const shared_ptr<Player>& Obj) {
		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
		if (Obj->IsAnimeEnd()) {
			Obj->GetStateMachine()->ChangeState(WaitState::Instance());
		}
	}
	void LandingState::Exit(const shared_ptr<Player>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	class StandState : public ObjState<Player>;
	//	�p�r: �N���オ��
	//--------------------------------------------------------------------------------------
	shared_ptr<StandState> StandState::Instance() {
		static shared_ptr<StandState> instance;
		if (!instance) {
			instance = shared_ptr<StandState>(new StandState);
		}
		return instance;
	}
	void StandState::Enter(const shared_ptr<Player>& Obj) {
		Obj->AnimeChangeMotion(L"Stand", false);
		Obj->SetFps(45.0f);
		Obj->SetStandFlag(true);

		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"se6");
		m_AudioObjectPtr->Start(L"se6", XAUDIO2_NO_LOOP_REGION, 0.32f);
		Obj->SetNowMusic(L"se6");
	}
	void StandState::Execute(const shared_ptr<Player>& Obj) {
		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
		if (Obj->IsAnimeEnd()) {
			Obj->GetStateMachine()->ChangeState(WaitState::Instance());
			Obj->SetStandFlag(false);
		}
	}
	void StandState::Exit(const shared_ptr<Player>& Obj) {

	}

	//--------------------------------------------------------------------------------------
	//	class WalkState : public ObjState<Player>;
	//	�p�r: �������
	//--------------------------------------------------------------------------------------
	shared_ptr<WalkState> WalkState::Instance() {
		static shared_ptr<WalkState> instance;
		if (!instance) {
			instance = shared_ptr<WalkState>
				(new WalkState);
		}
		return instance;
	}
	void WalkState::Enter(const shared_ptr<Player>& Obj) {
		Obj->SetFps(49.0f);
		Obj->AnimeChangeMotion(L"Walk", true);

		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"walk");
		m_AudioObjectPtr->Start(L"walk", XAUDIO2_LOOP_INFINITE, 0.28f);
		Obj->SetNowMusic(L"walk");
	}
	void WalkState::Execute(const shared_ptr<Player>& Obj) {
		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
		//�ׂ�Ď��񂾂�Died�A�j���𗬂�
		if (Obj->GetDeath() == 1) {
			Obj->GetStateMachine()->ChangeState(DiedState::Instance());
		}
		//�e�����Ȃ������痎����A�j���[�V����
		if (!Obj->GetParentFlag()) {
			Obj->GetStateMachine()->ChangeState(FallState::Instance());
		}
		//���X�e�B�b�N�̒l��0(���͂���Ȃ��Ȃ���)�Ȃ�Wait�A�j���𗬂�
		if (Obj->GetMoveLeftVectorX() == 0.0f) {
			Obj->GetStateMachine()->ChangeState(WaitState::Instance());
		}
	}
	void WalkState::Exit(const shared_ptr<Player>& Obj) {
		m_AudioObjectPtr->Stop(Obj->GetNowMusic());
	}

	//--------------------------------------------------------------------------------------
	//	class DiedState : public ObjState<Player>;
	//	�p�r: ���S���
	//--------------------------------------------------------------------------------------
	shared_ptr<DiedState> DiedState::Instance() {
		static shared_ptr<DiedState> instance;
		if (!instance) {
			instance = shared_ptr<DiedState>(new DiedState);
		}
		return instance;
	}
	void DiedState::Enter(const shared_ptr<Player>& Obj) {
		//���S�A�j�����Ăяo��
		Obj->AnimeChangeMotion(L"Died_1", false);
		//������󂯕t���Ȃ�����
		Obj->SetGameOverFlag(true);
		//Velocity��0�ɂ���
		Obj->GetComponent<Rigidbody>()->SetVelocityZero();

		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"se3");
		m_AudioObjectPtr->Start(L"se3", XAUDIO2_NO_LOOP_REGION, 1.0f);
		Obj->SetNowMusic(L"se3");
	}
	void DiedState::Execute(const shared_ptr<Player>& Obj) {
		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
		//�A�j���[�V�������I�������
		if (Obj->IsAnimeEnd()) {
			//�Q�[���I�[�o�[�V�[���ɑJ�ڂ���
			Obj->SetFadeFlag(true);
		}
	}
	void DiedState::Exit(const shared_ptr<Player>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class GoalState : public ObjState<Player>;
	//	�p�r: �S�[�����B���
	//--------------------------------------------------------------------------------------
	shared_ptr<GoalState> GoalState::Instance() {
		static shared_ptr<GoalState> instance;
		if (!instance) {
			instance = shared_ptr<GoalState>(new GoalState);
		}
		return instance;
	}
	void GoalState::Enter(const shared_ptr<Player>& Obj) {
		Obj->SetFps(60.0f);
		Obj->AnimeChangeMotion(L"curtsey", false);
		Obj->SetGameClearFlag(true);
		Obj->GetComponent<Rigidbody>()->SetVelocityZero();
	}
	void GoalState::Execute(const shared_ptr<Player>& Obj) {
		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
		if (Obj->IsAnimeEnd()) {
			Obj->SetFadeFlag(true);
		}
	}
	void GoalState::Exit(const shared_ptr<Player>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	class DamageState1 : public ObjState<Player>;
	//	�p�r: Damage���
	//--------------------------------------------------------------------------------------
	shared_ptr<DamageState1> DamageState1::Instance() {
		static shared_ptr<DamageState1> instance;
		if (!instance) {
			instance = shared_ptr<DamageState1>(new DamageState1);
		}
		return instance;
	}
	void DamageState1::Enter(const shared_ptr<Player>& Obj) {
		Obj->SetFps(60.0f);
		if (Obj->GetRightOrLeft() == Player::PlayerDirection::RIGHT) {
			Obj->AnimeChangeMotion(L"Knockdown", false);
		}
		else {
			Obj->AnimeChangeMotion(L"Knockdown_front", false);
		}
	}
	void DamageState1::Execute(const shared_ptr<Player>& Obj) {
		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
		if (Obj->IsAnimeEnd()) {
			Obj->GetStateMachine()->ChangeState(DamageState2::Instance());
		}
	}
	void DamageState1::Exit(const shared_ptr<Player>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	class DamageState2 : public ObjState<Player>;
	//	�p�r: Damage���
	//--------------------------------------------------------------------------------------
	shared_ptr<DamageState2> DamageState2::Instance() {
		static shared_ptr<DamageState2> instance;
		if (!instance) {
			instance = shared_ptr<DamageState2>(new DamageState2);
		}
		return instance;
	}
	void DamageState2::Enter(const shared_ptr<Player>& Obj) {
		Obj->SetFps(60.0f);
		if (Obj->GetRightOrLeft() == Player::PlayerDirection::RIGHT) {
			Obj->AnimeChangeMotion(L"StandUp", false);
		}
		else {
			Obj->AnimeChangeMotion(L"Stand", false);
		}
		auto PtrRedit = Obj->GetComponent<Rigidbody>();
		PtrRedit->SetVelocityZero();
		Obj->SetStandFlag(true);
	}
	void DamageState2::Execute(const shared_ptr<Player>& Obj) {
		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
		if (Obj->IsAnimeEnd()) {
			Obj->GetStateMachine()->ChangeState(WaitState::Instance());
		}
	}
	void DamageState2::Exit(const shared_ptr<Player>& Obj) {
		Obj->SetDamageFlag(false);
		Obj->SetStandFlag(false);
	}
}
//end basecross

