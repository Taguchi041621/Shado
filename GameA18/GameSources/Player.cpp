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
	Player::Player(const shared_ptr<Stage>& StagePtr, const wstring& BaseDir) :
		SS5ssae(StagePtr, BaseDir, L"Idea1.ssae", L"Wait"),
		m_MaxSpeed(50.0f),	//�ō����x
		m_Decel(0.65f),	//�����l
		m_Mass(0.5f),	//����
		m_Key(0),		//���̎擾��
		m_Death(0)		//������0(����)��
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.05f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(-0.5f, 0.0f, 0.0f)
		);
		m_ToAnimeMatrixRight.affineTransformation(
			Vec3(-0.1f, 0.05f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.5f, 0.0f, 0.0f)
		);
	}

	//0��n���ƍ��A1��n���ƉE�̃X�e�B�b�N��X�l��Ԃ�
	float Player::GetMoveVector(int LR) const {
		float MoveX = 0;
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			switch (LR){
			case 0:
				if (CntlVec[0].fThumbLX != 0) {
					//�R���g���[���̌����v�Z
					MoveX = CntlVec[0].fThumbLX;
				}
				break;
			case 1:
				if (CntlVec[0].fThumbRX != 0) {
					//�R���g���[���̌����v�Z
					MoveX = CntlVec[0].fThumbRX;
				}
				break;
			default:
				break;
			}
		}
		return MoveX;
	}

	//���[�V��������������֐��Q
	//�ړ����Č������ړ������ɂ���
	//�ړ�������Ԃ�
	float  Player::MoveRotationMotion() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto MoveX = GetMoveVector(0);
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
		}
		else if (MoveX < 0.0f) {
			SetToAnimeMatrix(m_ToAnimeMatrixLeft);
		}
		//MoveX��Ԃ�
		return MoveX;
	}

	//�Փˎ�
	void Player::OnCollision(vector<shared_ptr<GameObject>>& OtherVec) {
		auto playerTrans = GetComponent<Transform>();
		for (auto &obj : OtherVec) {
			//�V���h�E�I�u�W�F�N�g�����o
			auto ShadowPtr = dynamic_pointer_cast<ShadowObject>(obj);
			//���������̂��V���h�E�I�u�W�F�N�g��
			if (ShadowPtr) {
				//�V���h�E�̔���
				OBB p;
				p.m_Center = ShadowPtr->GetComponent<Transform>()->GetWorldPosition();
				p.m_Size = ShadowPtr->GetComponent<Transform>()->GetScale() * 0.5f;
				Vec3 HitPoint;
				//�C�f�A�̒��S�_����V���h�E�܂ł̍Őڋߓ_�̎Z�o
				HitTest::ClosestPtPointOBB(playerTrans->GetWorldPosition(), p, HitPoint);
				//�v���C���[�̔�������A�q�b�g�|�C���g��Y���Ⴍ��
				//X���̒��ɓ����Ă�����
				if ((playerTrans->GetWorldPosition().x - playerTrans->GetScale().x) <= HitPoint.x
					&& (playerTrans->GetWorldPosition().x + playerTrans->GetScale().x) >= HitPoint.x
					&& playerTrans->GetWorldPosition().y >= p.m_Center.y + p.m_Size.y) {
					//�y�A�����g�����Ă�I�u�W�F�N�g������������y�A�����g��
					if (!playerTrans->GetParent()) {
						//�y�A�����g������
						playerTrans->SetParent(ShadowPtr);
						m_ParentFlag = true;
					}
					//�������Ă�I�u�W�F�N�g���e�I�u�W�F�N�g���ᖳ��������
					else if (!(playerTrans->GetParent() == ShadowPtr)) {
						//���̐e�������ĐV���ɐe��ݒ肷��
						playerTrans->ClearParent();
						playerTrans->SetParent(ShadowPtr);
					}

				}
			}
		}
	}

	//�Փ˂��Ă��鎞
	void Player::OnCollisionExcute(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto &obj : OtherVec) {
			//���ꂪ�e��������
			if (GetComponent<Transform>()->GetParent() == obj) {
				//�v���C���[��Y��e�̏�ɏ��悤�ɂ���
				auto ParentTrans = obj->GetComponent<Transform>();
				auto Ppos = GetComponent<Transform>()->GetWorldPosition();
				Ppos.y = ParentTrans->GetPosition().y + ParentTrans->GetScale().y * 0.5f
									+ GetComponent<Transform>()->GetScale().y * 0.5f;
				//�K�p����
				GetComponent<Transform>()->SetWorldPosition(Ppos);
			}

			OBB p;
			p.m_Center = obj->GetComponent<Transform>()->GetWorldPosition();
			p.m_Size = obj->GetComponent<Transform>()->GetScale() * 0.5f;
			//�����蔻��̍X�V
			m_DieOBB.m_Center = GetComponent<Transform>()->GetWorldPosition();
			//�����S�����肪���������玀��
			if (HitTest::OBB_OBB(m_DieOBB, p)) {
				m_Death = 1;
			}
		}
	}

	//�Փ˂��Ȃ��Ȃ�����
	void Player::OnCollisionExit(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto &obj : OtherVec) {
			//�V���h�E�I�u�W�F�N�g�����o
			auto ShadowPtr = dynamic_pointer_cast<ShadowObject>(obj);
			//���ꂪ�e�̃V���h�E��
			if (ShadowPtr == GetComponent<Transform>()->GetParent()) {
				auto shadowPos = ShadowPtr->GetComponent<Transform>()->GetWorldPosition();
				auto shadowSca = ShadowPtr->GetComponent<Transform>()->GetScale();
				//�e�I�u�W�F�̉��ɗ����Ă���
				if((shadowPos.x - shadowSca.x * 0.5f) >= GetComponent<Transform>()->GetWorldPosition().x ||
					(shadowPos.x + shadowSca.x * 0.5f) <= GetComponent<Transform>()->GetWorldPosition().x){
					//�y�A�����g��������
					GetComponent<Transform>()->ClearParent();
					m_ParentFlag = false;
				}
			}
		}
	}

	//������
	void Player::OnCreate() {
		m_GameClearFlag = false;
		m_GameOverFlag = false;
		m_ParentFlag = false;
		//�����ʒu�Ȃǂ̐ݒ�
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(0.80f, 1.60f, 0.40f);	//X,Z25�AY50�̒����`
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(-8.0f, 5.5f, 0.0f);

		//�e�N���X�̃N���G�C�g���Ă�
		SS5ssae::OnCreate();
		//�l�͕b������̃t���[����
		SetFps(49.0f);

		//���ƂȂ�I�u�W�F�N�g����A�j���[�V�����I�u�W�F�N�g�ւ̍s��̐ݒ�
		SetToAnimeMatrix(m_ToAnimeMatrixLeft);

		//Rigidbody������
		auto PtrRedid = AddComponent<Rigidbody>();
		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionObb>();
		//auto PtrCol = AddComponent<CollisionSphere>();
		PtrCol->SetIsHitAction(IsHitAction::Auto);
		//�R���W������\������ꍇ�͈ȉ���ݒ�
		//PtrCol->SetDrawActive(true);
		//�f�o�b�O�p�����������
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		//���S����pOBB�̑傫���ݒ�
		m_DieOBB.m_Size.x = Ptr->GetScale().x * 0.3f;
		m_DieOBB.m_Size.y = Ptr->GetScale().y * 0.3f;

		//Action������
		//���C���[�ύX�p
		auto PtrAction = AddComponent<Action>();
		//�A�N�V�����͖����ɂ��Ă���
		PtrAction->SetUpdateActive(false);

		//�X�e�[�g�}�V���̍\�z
		m_StateMachine = make_shared< StateMachine<Player> >(GetThis<Player>());
		//�ŏ��̃X�e�[�g��WaitState�ɐݒ�
		m_StateMachine->SetCurrentState(WaitState::Instance());
		//WaitState�̏��������s���s��
		m_StateMachine->GetCurrentState()->Enter(GetThis<Player>());
	}

	//�X�V
	void Player::OnUpdate() {
			//�X�e�[�g�}�V����Update���s��
			//���̒��ŃX�e�[�g�̐؂�ւ����s����
			m_StateMachine->Update();

			//�d�͂�������
			auto PtrGrav = GetBehavior<Gravity>();
			PtrGrav->SetGravity(Vec3(0.0f, -4.9f, 0.0f));
			PtrGrav->Execute();
	}

	void Player::OnUpdate2() {
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		if (m_ParentFlag && !m_GameOverFlag && !m_GameClearFlag && ScenePtr->GetStartFlag()) {
			//�v���C���[�̈ړ�
			MoveRotationMotion();
			//������̕\��
			//DrawStrings();
		}

		if (!m_ParentFlag) {
			auto PtrRedit = GetComponent<Rigidbody>();
			PtrRedit->SetVelocityZero();

		}
			PlayerHP();
	}
	//
	void Player::PlayerHP() {
		m_PlayerHP = 3;
		auto PlayerPos = this->GetComponent<Transform>()->GetPosition();
		//������
		if (PlayerPos.y < -25.0f){
			m_PlayerHP = 0;
		}

		if (m_PlayerHP == 0&& !m_GameOverFlag){
			m_GameOverFlag = true;
			m_FadeFlag = true;
		}
	}
	//GameOverScene�Ɉڍs����
	void Player::GoGameOverScene() {
		m_GameOverFlag = true;
	}
	//GameOverScene�Ɉڍs����
	void Player::GoGameClearScene() {
		m_GameClearFlag = true;
	}
	void Player::InGoal() {
		GetStateMachine()->ChangeState(GoalState::Instance());
	}

	//������̕\��
	void Player::DrawStrings() {

		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring FPS(L"FPS: ");
		FPS += Util::UintToWStr(fps);
		FPS += L"\nElapsedTime: ";
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		FPS += Util::FloatToWStr(ElapsedTime);
		FPS += L"\n";

		auto Pos = GetComponent<Transform>()->GetPosition();
		wstring PositionStr(L"Position:\t");
		PositionStr += L"X=" + Util::FloatToWStr(Pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Y=" + Util::FloatToWStr(Pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		PositionStr += L"Z=" + Util::FloatToWStr(Pos.z, 6, Util::FloatModify::Fixed) + L"\n";

		auto WPos = GetComponent<Transform>()->GetWorldPosition();
		wstring WPositionStr(L"WPosition:");
		WPositionStr += L"X=" + Util::FloatToWStr(WPos.x, 6, Util::FloatModify::Fixed) + L",\t";
		WPositionStr += L"Y=" + Util::FloatToWStr(WPos.y, 6, Util::FloatModify::Fixed) + L",\t";
		WPositionStr += L"Z=" + Util::FloatToWStr(WPos.z, 6, Util::FloatModify::Fixed) + L"\n";


		wstring RididStr(L"Velocity:\t");
		auto Velocity = GetComponent<Rigidbody>()->GetVelocity();
		RididStr += L"X=" + Util::FloatToWStr(Velocity.x, 6, Util::FloatModify::Fixed) + L",\t";
		RididStr += L"Y=" + Util::FloatToWStr(Velocity.y, 6, Util::FloatModify::Fixed) + L",\t";
		RididStr += L"Z=" + Util::FloatToWStr(Velocity.z, 6, Util::FloatModify::Fixed) + L"\n";


		wstring HitObjectStr(L"HitObject: ");
		if (GetComponent<Collision>()->GetHitObjectVec().size() > 0) {
			for (auto&v : GetComponent<Collision>()->GetHitObjectVec()) {
				HitObjectStr += Util::UintToWStr((UINT)v.get()) + L",";
			}
			HitObjectStr += L"\n";
		}
		else {
			HitObjectStr += L"NULL\n";
		}
		wstring str = FPS + PositionStr +WPositionStr + RididStr +  HitObjectStr;
		//�����������
		auto PtrString = GetComponent<StringSprite>();
		PtrString->SetText(str);
	}

	void Player::LoopedAnimeUpdateMotion() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		//�A�j���[�V�������X�V����
		UpdateAnimeTime(ElapsedTime);
	}

	void Player::AnimeChangeMotion(const wstring& key, bool looped) {
		ChangeAnimation(key);
		SetLooped(looped);
	}

	//--------------------------------------------------------------------------------------
	//	class WaitState : public ObjState<Player>;
	//	�p�r: �ҋ@���
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<WaitState> WaitState::Instance() {
		static shared_ptr<WaitState> instance;
		if (!instance) {
			instance = shared_ptr<WaitState>(new WaitState);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void WaitState::Enter(const shared_ptr<Player>& Obj) {
		Obj->AnimeChangeMotion(L"Wait_1", true);
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void WaitState::Execute(const shared_ptr<Player>& Obj) {
		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
		//�ׂ�Ď��񂾂�Died�A�j���𗬂�
		if (Obj->GetDeath() == 1) {
			Obj->GetStateMachine()->ChangeState(DiedState::Instance());
		}
		auto ScenePtr = App::GetApp()->GetScene<Scene>();
		//���X�e�B�b�N�̒l��0�ȊO�Ȃ�Walk�A�j���𗬂�
		if (Obj->GetParentFlag() && Obj->GetMoveVector(0)&& ScenePtr->GetStartFlag()) {
			Obj->GetStateMachine()->ChangeState(WalkState::Instance());
		}
		if (!Obj->GetParentFlag()) {
			Obj->GetStateMachine()->ChangeState(FallState::Instance());
		}
	}
	//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
	void WaitState::Exit(const shared_ptr<Player>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class FallState : public ObjState<Player>;
	//	�p�r: �����Ă�Ƃ�
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<FallState> FallState::Instance() {
		static shared_ptr<FallState> instance;
		if (!instance) {
			instance = shared_ptr<FallState>(new FallState);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void FallState::Enter(const shared_ptr<Player>& Obj) {
		Obj->AnimeChangeMotion(L"Jump_1", true);
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void FallState::Execute(const shared_ptr<Player>& Obj) {
		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
		//���X�e�B�b�N�̒l��0�ȊO�Ȃ�Walk�A�j���𗬂�
		if (Obj->GetParentFlag()) {
			Obj->GetStateMachine()->ChangeState(WaitState::Instance());
		}
	}
	//�X�e�[�g���甲����Ƃ��ɌĂ΂��֐�
	void FallState::Exit(const shared_ptr<Player>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class WalkState : public ObjState<Player>;
	//	�p�r: �������
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<WalkState> WalkState::Instance() {
		static shared_ptr<WalkState> instance;
		if (!instance) {
			instance = shared_ptr<WalkState>(new WalkState);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void WalkState::Enter(const shared_ptr<Player>& Obj) {
		Obj->AnimeChangeMotion(L"Walk", true);
		//---------------------------------------------------------------
		wstring DataDir;
		//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
		//App::GetApp()->GetAssetsDirectory(DataDir);
		//�e�Q�[���͈ȉ��̂悤�Ƀf�[�^�f�B���N�g�����擾���ׂ�
		App::GetApp()->GetDataDirectory(DataDir);

		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"walk");
		m_AudioObjectPtr->Start(L"walk", XAUDIO2_LOOP_INFINITE, 0.1f);
		Obj->SetNowMusic(L"walk");
		//----------------------------------------------------------------
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void WalkState::Execute(const shared_ptr<Player>& Obj) {
		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
		//�ׂ�Ď��񂾂�Died�A�j���[�V�����𗬂�
		if (Obj->GetDeath() == 1) {
			Obj->GetStateMachine()->ChangeState(DiedState::Instance());
		}
		//���X�e�B�b�N�̒l��0(���͂���Ȃ��Ȃ���)�Ȃ�Wait�A�j���𗬂�
		if (Obj->GetMoveVector(0) == 0.0f) {
			Obj->GetStateMachine()->ChangeState(WaitState::Instance());
		}
	}
	//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
	void WalkState::Exit(const shared_ptr<Player>& Obj) {
		m_AudioObjectPtr->Stop(Obj->GetNowMusic());
	}

	//--------------------------------------------------------------------------------------
	//	class DiedState : public ObjState<Player>;
	//	�p�r: ���S���
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<DiedState> DiedState::Instance() {
		static shared_ptr<DiedState> instance;
		if (!instance) {
			instance = shared_ptr<DiedState>(new DiedState);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void DiedState::Enter(const shared_ptr<Player>& Obj) {
		//���S�A�j�����Ăяo��
		Obj->AnimeChangeMotion(L"Died_1", false);
		//������󂯕t���Ȃ�����
		Obj->SetGameOverFlag(true);
		//Velocity��0�ɂ���
		Obj->GetComponent<Rigidbody>()->SetVelocityZero();
		//---------------------------------------------------------------
		wstring DataDir;
		//�T���v���̂��߃A�Z�b�g�f�B���N�g�����擾
		//App::GetApp()->GetAssetsDirectory(DataDir);
		//�e�Q�[���͈ȉ��̂悤�Ƀf�[�^�f�B���N�g�����擾���ׂ�
		App::GetApp()->GetDataDirectory(DataDir);

		m_AudioObjectPtr = ObjectFactory::Create<MultiAudioObject>();
		m_AudioObjectPtr->AddAudioResource(L"dead");
		m_AudioObjectPtr->Start(L"dead", XAUDIO2_NO_LOOP_REGION, 0.1f);
		Obj->SetNowMusic(L"dead");
		//----------------------------------------------------------------
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void DiedState::Execute(const shared_ptr<Player>& Obj) {
		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
		//�A�j���[�V�������I�������
		if (Obj->IsAnimeEnd()) {
			//�Q�[���I�[�o�[�V�[���ɑJ�ڂ���
			Obj->SetFadeFlag(true);
		}
	}
	//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
	void DiedState::Exit(const shared_ptr<Player>& Obj) {
	}
	//--------------------------------------------------------------------------------------
	//	class GoalState : public ObjState<Player>;
	//	�p�r: �S�[�����B���
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<GoalState> GoalState::Instance() {
		static shared_ptr<GoalState> instance;
		if (!instance) {
			instance = shared_ptr<GoalState>(new GoalState);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void GoalState::Enter(const shared_ptr<Player>& Obj) {
		Obj->SetFps(60.0f);
		Obj->AnimeChangeMotion(L"curtsey", false);
		Obj->SetGameClearFlag(true);
		Obj->GetComponent<Rigidbody>()->SetVelocityZero();
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void GoalState::Execute(const shared_ptr<Player>& Obj) {
		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
		if (Obj->IsAnimeEnd()) {
			Obj->SetFadeFlag(true);
		}
	}
	//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
	void GoalState::Exit(const shared_ptr<Player>& Obj) {
	}

}
//end basecross

