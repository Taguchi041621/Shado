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
			m_RightOrLeft = true;
		}
		else if (MoveX < 0.0f) {
			SetToAnimeMatrix(m_ToAnimeMatrixLeft);
			m_RightOrLeft = false;
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
			auto EnemyPtr = dynamic_pointer_cast<Enemy>(obj);
			//���������̂��V���h�E�I�u�W�F�N�g��
			if (ShadowPtr) {
				Extrusion(ShadowPtr);//�����o���֐�
				FindParent(ShadowPtr);//�e�ɂ��邩���ׂ�֐�
			}
			else if (EnemyPtr) {
				m_PlayerHP = 0;
				if (m_PlayerHP == 0) {
					PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetSceneInterface(), L"ToGameOverStage");
				}
			}
		}
	}

	//�Փ˂��Ă��鎞
	void Player::OnCollisionExcute(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto &obj : OtherVec) {
			auto ShadowPtr = dynamic_pointer_cast<ShadowObject>(obj);
			if (ShadowPtr) {
				Extrusion(ShadowPtr);
				FindParent(ShadowPtr);
			}
		}
	}

	//�Փ˂��Ȃ��Ȃ�����
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
	//�e�ɂȂ�����𖞂����Ă��邩�𒲂ׂāA�������Ă�����e�ɂ���
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
				if (diff[2] < 0.4f && diff[2] >0.0f && GetMoveVector(0) < -0.6f) {
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
				if (diff[2] < 0.4f && diff[2] > 0.0f && GetMoveVector(0) > 0.6f) {
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

	//������
	void Player::OnCreate() {
		m_GameClearFlag = false;
		m_GameOverFlag = false;
		m_ParentFlag = false;
		m_StandFlag = false;
		m_DamageFlag = false;
		//�����ʒu�Ȃǂ̐ݒ�
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(0.80f, 1.60f, 0.040f);	//X,Z25�AY50�̒����`
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(-8.0f, 5.5f, 0.0f);

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
		//auto PtrCol = AddComponent<CollisionSphere>();
		PtrCol->SetIsHitAction(IsHitAction::None);
		//�R���W������\������ꍇ�͈ȉ���ݒ�
		//PtrCol->SetDrawActive(true);
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

	//�X�V
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
			//������̕\��
		}
		else if (!m_ParentFlag) {
			
			PtrRedit->SetVelocityZero();
			GetComponent<Rigidbody>()->SetVelocity(Vec3(0.0f, m_FallSpeed, 0.0f));
			m_FallSpeed += -0.08f;
		}
	    else if (m_DamageFlag)
		{
			//PtrRedit->SetVelocityZero();
		}
		PlayerHP();
		//DrawStrings();
	}
	//
	void Player::PlayerHP() {
		m_PlayerHP = 3;
		auto PlayerPos = this->GetComponent<Transform>()->GetWorldPosition();
		//������
		if (PlayerPos.y < -25.0f){
			m_PlayerHP = 0;
		}
		
		if (m_PlayerHP == 0 && !m_GameOverFlag){
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

	void Player::Damage() {
		if (!m_DamageFlag) {
			m_DamageFlag = true;
			auto PtrRedit = GetComponent<Rigidbody>();
			PtrRedit->SetVelocityZero();
			GetComponent<Rigidbody>()->SetVelocity(Vec3(-1.0f, 0, 0.0f));
			GetStateMachine()->ChangeState(DamageState1::Instance());
		}
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
		Obj->SetFps(49.0f);
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
		//�e�����Ȃ�������Fall�A�j���𗬂�
		if (!Obj->GetParentFlag()) {
			Obj->GetStateMachine()->ChangeState(FallState::Instance());
		}
		//���X�e�B�b�N�̒l��0�ȊO�Ȃ�Walk�A�j���𗬂�
		if (Obj->GetParentFlag() && Obj->GetMoveVector(0)&& ScenePtr->GetStartFlag()) {
			Obj->GetStateMachine()->ChangeState(WalkState::Instance());
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
		Obj->AnimeChangeMotion(L"Down_loop", true);
		m_Timer = 0;
		m_FallFlag = false;
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void FallState::Execute(const shared_ptr<Player>& Obj) {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_Timer += ElapsedTime;

		if (m_Timer >= 0.7f)
		{
			Obj->AnimeChangeMotion(L"Fall", false);
			m_FallFlag = true;
			m_Timer = -10;
		}

		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
		if (Obj->GetParentFlag() && m_FallFlag) {
			Obj->GetStateMachine()->ChangeState(StandState::Instance());
		}
		else if (Obj->GetParentFlag()) {
			Obj->GetStateMachine()->ChangeState(LandingState::Instance());
		}
	}
	//�X�e�[�g���甲����Ƃ��ɌĂ΂��֐�
	void FallState::Exit(const shared_ptr<Player>& Obj) {
		
	}
	//--------------------------------------------------------------------------------------
	//	class LandingState : public ObjState<Player>;
	//	�p�r: ���n
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<LandingState> LandingState::Instance() {
		static shared_ptr<LandingState> instance;
		if (!instance) {
			instance = shared_ptr<LandingState>(new LandingState);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void LandingState::Enter(const shared_ptr<Player>& Obj) {
		Obj->AnimeChangeMotion(L"Down_landing", false);
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void LandingState::Execute(const shared_ptr<Player>& Obj) {
		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
		if (Obj->IsAnimeEnd()) {
			Obj->GetStateMachine()->ChangeState(WaitState::Instance());
		}
	}
	//�X�e�[�g���甲����Ƃ��ɌĂ΂��֐�
	void LandingState::Exit(const shared_ptr<Player>& Obj) {

	}

	//--------------------------------------------------------------------------------------
	//	class StandState : public ObjState<Player>;
	//	�p�r: �N���オ��
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<StandState> StandState::Instance() {
		static shared_ptr<StandState> instance;
		if (!instance) {
			instance = shared_ptr<StandState>(new StandState);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void StandState::Enter(const shared_ptr<Player>& Obj) {
		Obj->AnimeChangeMotion(L"Stand", false);
		Obj->SetFps(45.0f);
		Obj->SetStandFlag(true);
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void StandState::Execute(const shared_ptr<Player>& Obj) {
		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
		if (Obj->IsAnimeEnd()) {
			Obj->GetStateMachine()->ChangeState(WaitState::Instance());
			Obj->SetStandFlag(false);
		}
	}
	//�X�e�[�g���甲����Ƃ��ɌĂ΂��֐�
	void StandState::Exit(const shared_ptr<Player>& Obj) {

	}

	//--------------------------------------------------------------------------------------
	//	class WalkState : public ObjState<Player>;
	//	�p�r: �������
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<WalkState> WalkState::Instance() {
		static shared_ptr<WalkState> instance;
		if (!instance) {
			instance = shared_ptr<WalkState>
				(new WalkState);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void WalkState::Enter(const shared_ptr<Player>& Obj) {
		Obj->SetFps(49.0f);
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
		if (!Obj->GetParentFlag()) {
			Obj->GetStateMachine()->ChangeState(FallState::Instance());
		}
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

	//--------------------------------------------------------------------------------------
	//	class DamageState1 : public ObjState<Player>;
	//	�p�r: Damage���
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<DamageState1> DamageState1::Instance() {
		static shared_ptr<DamageState1> instance;
		if (!instance) {
			instance = shared_ptr<DamageState1>(new DamageState1);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void DamageState1::Enter(const shared_ptr<Player>& Obj) {
		Obj->SetFps(60.0f);
		if (Obj->GetRightOrLeft()) {
			Obj->AnimeChangeMotion(L"Knockdown", false);
		}
		else {
			Obj->AnimeChangeMotion(L"Knockdown_front", false);
		}
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void DamageState1::Execute(const shared_ptr<Player>& Obj) {
		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
		if (Obj->IsAnimeEnd()) {
			Obj->GetStateMachine()->ChangeState(DamageState2::Instance());
		}
	}
	//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
	void DamageState1::Exit(const shared_ptr<Player>& Obj) {
		//Obj->SetDamageFlag(false);
	}

	//--------------------------------------------------------------------------------------
	//	class DamageState2 : public ObjState<Player>;
	//	�p�r: Damage���
	//--------------------------------------------------------------------------------------
	//�X�e�[�g�̃C���X�^���X�擾
	shared_ptr<DamageState2> DamageState2::Instance() {
		static shared_ptr<DamageState2> instance;
		if (!instance) {
			instance = shared_ptr<DamageState2>(new DamageState2);
		}
		return instance;
	}
	//�X�e�[�g�ɓ������Ƃ��ɌĂ΂��֐�
	void DamageState2::Enter(const shared_ptr<Player>& Obj) {
		Obj->SetFps(60.0f);
		if (Obj->GetRightOrLeft()) {
			Obj->AnimeChangeMotion(L"StandUp", false);
		}
		else {
			Obj->AnimeChangeMotion(L"Stand", false);
		}
		auto PtrRedit = Obj->GetComponent<Rigidbody>();
		PtrRedit->SetVelocityZero();
		Obj->SetStandFlag(true);
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void DamageState2::Execute(const shared_ptr<Player>& Obj) {
		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
		if (Obj->IsAnimeEnd()) {
			Obj->GetStateMachine()->ChangeState(WaitState::Instance());
		}
	}
	//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
	void DamageState2::Exit(const shared_ptr<Player>& Obj) {
		Obj->SetDamageFlag(false);
		Obj->SetStandFlag(false);
	}

}
//end basecross

