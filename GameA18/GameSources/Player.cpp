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
	Player::Player(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_MaxSpeed(7.0f),	//�ō����x
		m_Decel(0.65f),	//�����l
		m_Mass(0.5f)	//����
	{}


	Vec3 Player::GetMoveVector() const {
		Vec3 Angle(0, 0, 0);
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			if (CntlVec[0].fThumbLX != 0 || CntlVec[0].fThumbLY != 0) {
				float MoveLength = 0;	//���������̃X�s�[�h
				auto PtrTransform = GetComponent<Transform>();
				auto PtrCamera = OnGetDrawCamera();
				//�i�s�����̌������v�Z
				Vec3 Front = PtrTransform->GetPosition() - PtrCamera->GetEye();
				Front.y = 0;
				Front.normalize();
				//�i�s������������̊p�x���Z�o
				float FrontAngle = atan2(Front.z, Front.x);
				//�R���g���[���̌����v�Z
				float MoveX = CntlVec[0].fThumbLX;
				float MoveZ = CntlVec[0].fThumbLY;
				Vec2 MoveVec(MoveX, MoveZ);
				float MoveSize = MoveVec.length();
				//�R���g���[���̌�������p�x���v�Z
				float CntlAngle = atan2(-MoveX, MoveZ);
				//�g�[�^���̊p�x���Z�o
				float TotalAngle = FrontAngle + CntlAngle;
				//�p�x����x�N�g�����쐬
				Angle = Vec3(cos(TotalAngle), 0, sin(TotalAngle));
				//���K������
				Angle.normalize();
				//�ړ��T�C�Y��ݒ�B
				Angle *= MoveSize;
				//Y���͕ω������Ȃ�
				Angle.y = 0;
			}
		}
		return Angle;

	}

	void Player::MovePlayer() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		Vec3 Angle = GetMoveVector();
		//Rigidbody�����o��
		auto PtrRedit = GetComponent<Rigidbody>();
		auto Velo = PtrRedit->GetVelocity();
		if (Angle.length() <= 0.0f && Velo.y == 0.0f) {
			//�R���g���[���𗣂����Ƃ��΍�
			Velo *= GetDecel();
			PtrRedit->SetVelocity(Velo);
			return;
		}
		//Transform
		auto PtrTransform = GetComponent<Transform>();
		//���݂̑��x�����o��
		//�ړI�n���ō����x���|���ċ��߂�
		auto Target = Angle * GetMaxSpeed();
		//�ړI�n�Ɍ��������߂ɗ͂̂�����������v�Z����
		//Force�̓t�H�[�X�ł���
		auto Force = Target - Velo;
		//y��0�ɂ���
		Force.y = 0;
		//�����x�����߂�
		auto Accel = Force / GetMass();
		//�^�[�����Ԃ��|�������̂𑬓x�ɉ��Z����
		Velo += (Accel * ElapsedTime);
		//���F���V�e�B��z������0�ɂ���
		Velo.z = 0;
		//���x��ݒ肷��
		PtrRedit->SetVelocity(Velo);
		//��]�̌v�Z
		if (Angle.length() > 0.0f) {
			auto UtilPtr = GetBehavior<UtilBehavior>();
			UtilPtr->RotToHead(Angle, 1.0f);
		}
	}
	//�Փˎ��Ƀy�A�����g������
	//void Player::OnCollision(vector<shared_ptr<GameObject>>& OtherVec) {
	//	auto shadowPtr = dynamic_pointer_cast<ShadowObject>(OtherVec.at(0));
	//	if (shadowPtr) {
	//		GetComponent<Transform>()->SetParent(OtherVec.at(0));
	//	}
	//}

	//������
	void Player::OnCreate() {
		m_CameraNumber = 0;
		//�����ʒu�Ȃǂ̐ݒ�
		auto Ptr = GetComponent<Transform>();
		Ptr->SetScale(0.25f, 0.25f, 0.25f);	//���a25�Z���`�̋���
		Ptr->SetRotation(0.0f, 0.0f, 0.0f);
		Ptr->SetPosition(0.0f, 3.5f, -0.1f);

		//Rigidbody������
		auto PtrRedid = AddComponent<Rigidbody>();
		//�Փ˔��������
		auto PtrCol = AddComponent<CollisionSphere>();
		PtrCol->SetIsHitAction(IsHitAction::Auto);
		//�f�o�b�O�p�����������
		auto PtrString = AddComponent<StringSprite>();
		PtrString->SetText(L"");
		PtrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ShadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ShadowPtr->SetMeshResource(L"DEFAULT_SPHERE");
		//�`��R���|�[�l���g�̐ݒ�
		auto PtrDraw = AddComponent<BcPNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		PtrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		//�`�悷��e�N�X�`����ݒ�
		PtrDraw->SetTextureResource(L"TRACE_TX");
		//��������
		SetAlphaActive(true);
		//�J�����𓾂�
		auto PtrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (PtrCamera) {
			PtrCamera->SetTargetObject(GetThis<GameObject>());
		}
	}

	//�X�V
	void Player::OnUpdate() {
		//�v���C���[�̈ړ�
		MovePlayer();

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
		switch (m_CameraNumber)
		{
		case 0:
		{
			auto TargetPos = this->GetComponent<Transform>()->GetPosition();
			Vec3 ArmVec(0, 0.0f, -5.0f);
			Vec3 Eye = TargetPos + ArmVec;
			PtrCamera->SetAt(TargetPos);
			PtrCamera->SetEye(Eye);

		}
			break;
		case 1:
		{
			auto TargetPos = this->GetComponent<Transform>()->GetPosition();
			Vec3 ArmVec(0, 0.0f, -10.0f);
			Vec3 Eye = TargetPos + ArmVec;
			PtrCamera->SetAt(TargetPos);
			PtrCamera->SetEye(Eye);
		}

			break;
		case 2:
		{
			auto TargetPos = this->GetComponent<Transform>()->GetPosition();
			Vec3 ArmVec(0, 0.0f, -15.0f);
			Vec3 Eye = TargetPos + ArmVec;
			PtrCamera->SetAt(TargetPos);
			PtrCamera->SetEye(Eye);
		}

			break;
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
		wstring str = FPS + PositionStr + RididStr +  HitObjectStr;
		//�����������
		auto PtrString = GetComponent<StringSprite>();
		PtrString->SetText(str);
	}


}
//end basecross

