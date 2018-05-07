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
		m_MaxSpeed(20.0f),	//�ō����x
		m_Decel(0.65f),	//�����l
		m_Mass(0.5f)	//����
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

	SPHERE Player::GetHitSphere() {
		return m_HitSpere;
	}

	//�Փˎ�
	void Player::OnCollision(vector<shared_ptr<GameObject>>& OtherVec) {
		auto playerTrans = GetComponent<Transform>();
		for (auto &obj : OtherVec) {
			//�V���h�E�I�u�W�F�N�g�����o
			auto ShadowPtr = dynamic_pointer_cast<ShadowObject>(obj);
			//���������̂��V���h�E�I�u�W�F�N�g��
			if (ShadowPtr) {
				//�����蔻��̍X�V
				m_HitSpere.m_Center = playerTrans->GetWorldPosition();
				//�����`�̉��̕��ɔz�u
				m_HitSpere.m_Center.y += -playerTrans->GetScale().y * 0.5f;
				//�V���h�E�̔���
				OBB p;
				p.m_Center = ShadowPtr->GetComponent<Transform>()->GetWorldPosition();
				p.m_Size = ShadowPtr->GetComponent<Transform>()->GetScale() * 0.5f;
				Vec3 HitPoint;
				//�C�f�A�ƃV���h�E�̐ڐG����
				if (HitTest::SPHERE_OBB(m_HitSpere, p, HitPoint)) {
					//�v���C���[�̔�������A�q�b�g�|�C���g��Y���Ⴍ��
					//X���̒��ɓ����Ă�����
					if ((m_HitSpere.m_Center.x - m_HitSpere.m_Radius) <= HitPoint.x
						&& (m_HitSpere.m_Center.x + m_HitSpere.m_Radius) >= HitPoint.x
						&& p.m_Center.y <= m_HitSpere.m_Center.y - m_HitSpere.m_Radius) {
						//�y�A�����g�����Ă�I�u�W�F�N�g������������y�A�����g��
						if (!playerTrans->GetParent()) {
							//�y�A�����g������
							playerTrans->SetParent(ShadowPtr);
						}
						//�������Ă�I�u�W�F�N�g���e�I�u�W�F�N�g���ᖳ��������
						else if (!(playerTrans->GetParent() == ShadowPtr)) {
							//���̐e�������ĐV���ɐe��ݒ肷��
							playerTrans->ClearParent();
							playerTrans->SetParent(ShadowPtr);
						}
					}
				}

				bool isHit = false;
				auto playerPos = playerTrans->GetPosition();
				auto playerSca = playerTrans->GetScale() * 0.5f;
				auto shadowPos = ShadowPtr->GetComponent<Transform>()->GetPosition();
				auto shadowSca = ShadowPtr->GetComponent<Transform>()->GetScale() * 0.5f;
				if (playerPos.x - playerSca.x < shadowPos.x + shadowSca.x && playerPos.x + playerSca.x > shadowPos.x - shadowSca.x &&
					playerPos.y + playerSca.y < shadowPos.y + shadowSca.y && playerPos.y - playerSca.y > shadowPos.y - shadowSca.y) {
					// �Փ˂����o����܂���
					isHit = true;
				}
				if (isHit) {
					// �Փ˂��Ă���̂ŉ������s��
					float diff[] = {
						(shadowPos.x + shadowSca.x) - (playerPos.x - playerSca.x), // �E
						(playerPos.x + playerSca.x) - (shadowPos.x - shadowSca.x), // ��
						(shadowPos.y + shadowSca.y) - (playerPos.y - playerSca.y), // ��
						(playerPos.y + playerSca.y) - (shadowPos.y - shadowSca.y), // ��
					};
					// ���ʂ̋������ŏ��ɂȂ��Ă���v�f��������
					int min = 0;
					for (int i = 0; i < 4; i++) {
						if (diff[i] < diff[min]) {
							min = i;
						}
					}
					// �ŏ��ɂȂ��Ă�������ɑ΂��ĉ����o�����s��
					switch (min) {
					case 0:
						playerPos.x += diff[min];
						break;
					case 1:
						playerPos.x -= diff[min];
						break;
					case 2:
						playerPos.y += diff[min];
						break;
					case 3:
						playerPos.y -= diff[min];
						break;
					default:
						break;
					}
				}
				// �C�f�A�Ɉʒu�𔽉f������
				playerTrans->SetPosition(playerPos);

				//-0.5�����Ă���̂ɂP�𑫂���0.5��ɂ��Ē����`�̏�̂ق��ɔz�u
				m_HitSpere.m_Center.y += playerTrans->GetScale().y;
				//���t�߂����������玀��
				if (HitTest::SPHERE_OBB(m_HitSpere, p, HitPoint)) {
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOver");
				}
			}
		}
	}

	//�Փ˂��Ă��鎞
	void Player::OnCollisionExcute(vector<shared_ptr<GameObject>>& OtherVec) {
		for (auto &obj : OtherVec) {
			if (GetComponent<Transform>()->GetParent() == obj) {
				auto ParentTrans = obj->GetComponent<Transform>();
				auto Ppos = GetComponent<Transform>()->GetWorldPosition();
				Ppos.y = ParentTrans->GetPosition().y + ParentTrans->GetScale().y * 0.5f
									+ GetComponent<Transform>()->GetScale().y * 0.5f;
				//������݂̂߂荞�݂𒼂�
				GetComponent<Transform>()->SetWorldPosition(Ppos);
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
				}
			}
		}
	}

	//������
	void Player::OnCreate() {
		CameraPosZ = -10;
		//�����ʒu�Ȃǂ̐ݒ�
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(0.40f, 0.80f, 0.40f);	//X,Z25�AY50�̒����`
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
		PtrCol->SetDrawActive(true);
		//�f�o�b�O�p�����������
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		//���̂̓����蔻��̃T�C�Y��ݒ�
		m_HitSpere.m_Radius = Ptr->GetScale().x * 0.5f;

		m_HitOBB.m_Size.x = Ptr->GetScale().x * 0.5f;
		m_HitOBB.m_Size.y = Ptr->GetScale().y * 0.5f;

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
		PtrGrav->SetGravity(Vec3(0.0f,-4.9f,0.0f));
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
		//�v���C���[�̈ړ�
		MoveRotationMotion();

		//������̕\��
		DrawStrings();

		CameraChanger();

		PlayerHP();
	}

	void Player::CameraChanger() {
		auto PtrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());

		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
				CameraPosZ += 0.2;
				if (CameraPosZ >= -10) {
					CameraPosZ = -10;
				}
			}
			else if (CntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER){
				CameraPosZ -= 0.2;
				if (CameraPosZ <= -20) {
					CameraPosZ = -20;
				}
			}
		}

	    auto TargetPos = this->GetComponent<Transform>()->GetWorldPosition();
		Vec3 ArmVec(0, 0.0f, CameraPosZ);
		Vec3 Eye = TargetPos + ArmVec;
		PtrCamera->SetAt(TargetPos);
		PtrCamera->SetEye(Eye);
	}
	void Player::PlayerHP() {
		m_PlayerHP = 3;

		auto PlayerPos = this->GetComponent<Transform>()->GetPosition();
		//������
		if (PlayerPos.y < -20.0f){
			m_PlayerHP = 0;
		}

		if (m_PlayerHP == 0){
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

