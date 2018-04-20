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
		SS5ssae(StagePtr, BaseDir, L"Idea1.ssae", L"Walk"),
		m_MaxSpeed(40.0f),	//�ō����x
		m_Decel(0.65f),	//�����l
		m_Mass(0.5f)	//����
	{
		m_ToAnimeMatrixLeft.affineTransformation(
			Vec3(0.1f, 0.1f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(-0.3f, 0.5f, 0.0f)
		);
		m_ToAnimeMatrixRight.affineTransformation(
			Vec3(-0.1f, 0.1f, 0.1f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(0.3f, 0.5f, 0.0f)
		);

	}


	float Player::GetMoveVector() const {
		float MoveX = 0;
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].fThumbLX != 0) {
				//�R���g���[���̌����v�Z
				MoveX = CntlVec[0].fThumbLX;
			}
		}
		return MoveX;
	}

	//���[�V��������������֐��Q
	//�ړ����Č������ړ������ɂ���
	//�ړ�������Ԃ�
	float  Player::MoveRotationMotion() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		auto MoveX = GetMoveVector();
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
		if (MoveX >= 0.0f) {
			SetToAnimeMatrix(m_ToAnimeMatrixRight);
		}
		else {
			SetToAnimeMatrix(m_ToAnimeMatrixLeft);
		}
		//MoveX��Ԃ�
		return MoveX;
	}

	void Player::OnCollision(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto &obj : OtherVec) {
			//�V���h�E�I�u�W�F�N�g�����o
			auto ShadowPtr = dynamic_pointer_cast<ShadowObject>(obj);
			//���������̂��V���h�E�I�u�W�F�N�g��
			//�y�A�����g�����Ă�I�u�W�F�N�g������������y�A�����g��
			if (ShadowPtr && !GetComponent<Transform>()->GetParent()) {
				//�C�f�A�̔���
				SPHERE t;
				t.m_Center = GetComponent<Transform>()->GetPosition();
				t.m_Center.z = 0;
				t.m_Radius = 0.30;
				//�V���h�E�̔���
				PLANE p;
				auto objPos = obj->GetComponent<Transform>()->GetPosition();
				auto objSca = obj->GetComponent<Transform>()->GetScale();
				float pull = 0.4f;//����ɏ��������o�����鋗��
								  //�V���h�E�I�u�W�F�̏�̕��ɉ����̔�������
				Plane4 pla = Plane4(objPos.x - objSca.x / 2, objPos.y + objSca.y / 2 + pull, objSca.x, objSca.y);
				//�C�f�A�ƃV���h�E�̐ڐG����
				if (!HitTest::SPHERE_PLANE(t, pla)) {
					//�y�A�����g��������
					GetComponent<Transform>()->SetParent(obj);
				}
				GetComponent<Transform>()->SetParent(ShadowPtr);
			}
		}
	}

	//�Փ˂��Ă��鎞
	void Player::OnCollisionExcute(vector<shared_ptr<GameObject>>& OtherVec) {
	}

	//�Փ˂��Ȃ��Ȃ�����
	void Player::OnCollisionExit(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto &obj : OtherVec) {
			//�V���h�E�I�u�W�F�N�g�����o
			auto ShadowPtr = dynamic_pointer_cast<ShadowObject>(obj);
			//���ꂪ�e�̃V���h�E��
			if (ShadowPtr == GetComponent<Transform>()->GetParent()) {
				//�C�f�A�̔���
				SPHERE t;
				t.m_Center = GetComponent<Transform>()->GetPosition();
				t.m_Center.z = 0;
				t.m_Radius = 0.30;
				//�V���h�E�̔���
				float pull = 0.4f;//����ɏ��������o�����鋗��
				auto objPos = obj->GetComponent<Transform>()->GetPosition();
				auto objSca = obj->GetComponent<Transform>()->GetScale();
				//�V���h�E�I�u�W�F�̏�̕��ɉ����̔�������
				objPos.y += pull;
				OBB p(objSca,Vec3(1,1,1),objPos);
				Vec3 HitPoint;
				//�C�f�A�ƃV���h�E�̐ڐG����
				if (!HitTest::SPHERE_OBB(t, p,HitPoint)){
					//�y�A�����g��������
					GetComponent<Transform>()->SetParent(nullptr);

				}
			}
		}
	}

	//������
	void Player::OnCreate() {
		CameraPosZ = -5;
		m_CameraNumber = 0;
		//�����ʒu�Ȃǂ̐ݒ�
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(0.25f, 0.25f, 0.25f);	//���a25�Z���`�̋���
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(-8.0f, 5.5f, -0.1f);

		//�e�N���X�̃N���G�C�g���Ă�
		SS5ssae::OnCreate();
		//�l�͕b������̃t���[����
		SetFps(49.0f);


		//���ƂȂ�I�u�W�F�N�g����A�j���[�V�����I�u�W�F�N�g�ւ̍s��̐ݒ�
		SetToAnimeMatrix(m_ToAnimeMatrixLeft);

		//Rigidbody������
		auto PtrRedid = AddComponent<Rigidbody>();
		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionSphere>();
		PtrCol->SetIsHitAction(IsHitAction::Auto);
		//�R���W������\������ꍇ�͈ȉ���ݒ�
		PtrCol->SetDrawActive(true);
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
		//WaitState�̏��������s���s��
		m_StateMachine->GetCurrentState()->Enter(GetThis<Player>());
	}

	//�X�V
	void Player::OnUpdate() {

		//�X�e�[�g�}�V����Update���s��
		//���̒��ŃX�e�[�g�̐؂�ւ����s����
		m_StateMachine->Update();
		//�v���C���[�̈ړ�
		MoveRotationMotion();

		//�d�͂�������
		auto PtrGrav = GetBehavior<Gravity>();
		PtrGrav->Execute();
		//�J�����𓾂�
		//auto PtrCamera = dynamic_pointer_cast<LookAtCamera>(OnGetDrawCamera());
		//if (PtrCamera) {
		//	//LookAtCamera�ł���
		//	//LookAtCamera�ɒ��ڂ���I�u�W�F�N�g�i�v���C���[�j�̐ݒ�
		//	PtrCamera->SetTargetObject(GetThis<GameObject>());
		//	//player�̈ʒu�ƃJ�����ʒu�𓯊�����
		//	auto p_pos = GetThis<GameObject>()->GetComponent<Transform>()->GetPosition();
		//	PtrCamera->SetEye(Vec3(p_pos.x, p_pos.y+10.0f, -20.0f));
		//}


	}

	void Player::OnUpdate2() {
		//������̕\��
		DrawStrings();

		CameraChanger();

		PlayerHP();


	}

	void Player::CameraChanger() {
		auto PtrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) 
			{
				m_CameraNumber -= 1;
			}
			else if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				m_CameraNumber += 1;
			}
		}

		if (m_CameraNumber < 0) {
			m_CameraNumber = 2;
		}
		if (m_CameraNumber > 2) {
			m_CameraNumber = 0;
		}
		auto PtrMCamera = dynamic_pointer_cast<MyCamera>(GetStage()->GetView()->GetTargetCamera());
		PtrMCamera->SetToTargetLerp(0.5);

	    auto TargetPos = this->GetComponent<Transform>()->GetWorldPosition();
		Vec3 ArmVec(0, 0.0f, CameraPosZ);
		Vec3 Eye = TargetPos + ArmVec;
		PtrCamera->SetAt(TargetPos);
		PtrCamera->SetEye(Eye);

		if (CameraPosZ > -10)
		{
			CameraPosFlag = true;
		}
		else if (CameraPosZ < -10)
		{
			CameraPosFlag = false;
		}
		switch (m_CameraNumber)
		{
		case 0:
		{
			if (CameraPosZ == -5)
			{
				break;
			}
			CameraPosZ += 0.2;
			if (CameraPosZ > -5)
			{
				CameraPosZ = -5;
			}
			break;
		}

		case 1:
		{
			if (CameraPosZ == -10)
			{
				break;
			}
			if (CameraPosFlag)
			{
				CameraPosZ -= 0.2;
			}
			else if (!CameraPosFlag)
			{
				CameraPosZ += 0.2;
			}

			if (CameraPosZ >= -10.2f && CameraPosZ <= -9.8f)
			{
				CameraPosZ = -10;
			}

			break;
		}
		case 2:
		{
			if (CameraPosZ == -15)
			{
				break;
			}
			CameraPosZ -= 0.2;
			if (CameraPosZ < -15)
			{
				CameraPosZ = -15;
			}
			break;
		}

		case 3:
		{

		}
		break;
		}
	}
	void Player::PlayerHP() {
		m_PlayerHP = 3;

		auto PlayerPos = this->GetComponent<Transform>()->GetPosition();
		//������
		if (PlayerPos.y < -5)
		{
			m_PlayerHP = 0;
		}

		if (m_PlayerHP == 0)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOver");
		}
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
		wstring WPositionStr(L"WPosition:\t");
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
		Obj->AnimeChangeMotion(L"Walk", true);
	}
	//�X�e�[�g���s���ɖ��^�[���Ă΂��֐�
	void WaitState::Execute(const shared_ptr<Player>& Obj) {
		//�A�j���[�V�����X�V
		Obj->LoopedAnimeUpdateMotion();
	}
	//�X�e�[�g�ɂ��甲����Ƃ��ɌĂ΂��֐�
	void WaitState::Exit(const shared_ptr<Player>& Obj) {
	}

}
//end basecross

