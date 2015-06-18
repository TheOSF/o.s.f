#include "LacrossePlayerState.h"
#include "../../GameSystem/GameController.h"
#include "../CharacterFunction.h"

#include "../CharacterMoveClass.h"
#include "LacrosseAttackClose.h"
#include "LacrosseEvasionClass.h"
#include "LacrosseHitBallAttackClass.h"
#include "LacrosseCounterPoseClass.h"

//*************************************************************
//
//		���N���X�̑���N���X
//
//*************************************************************


//***************************************************
//		�v���C���[����̈ړ��N���X
//     LacrosseState_PlayerControllMove
//***************************************************

// �ړ����̃C�x���g�N���X�쐬
CharacterUsualMove* LacrosseState_PlayerControllMove::CreateMoveClass(LacrossePlayer* t)
{
	class LacrosseMoveEvent : public CharacterUsualMove::MoveEvent
	{
		LacrossePlayer* m_pLacrosse;
	public:
		LacrosseMoveEvent(LacrossePlayer* pLacrosse) :
			m_pLacrosse(pLacrosse){}

		// �X�V
		void Update(bool isRun, RATIO speed_ratio)
		{
			m_pLacrosse->m_Renderer.Update(1);
		}

		// ����o������
		void RunStart()
		{
			m_pLacrosse->m_Renderer.SetMotion(lacrosse_player::mt_Run);
		}

		// �~�܂�����
		void StandStart()
		{
			m_pLacrosse->m_Renderer.SetMotion(lacrosse_player::mt_Stand);
		}
	};

	// �ړ��p�����[�^�ݒ�
	CharacterUsualMove::Params p;
	p.Acceleration = 0.2f;
	p.MaxSpeed = 0.23f;
	p.TurnSpeed = 0.3f;
	p.DownSpeed = 0.2f;

	return new CharacterUsualMove(t, p, new LacrosseMoveEvent(t), new DamageManager::HitEventBase());
}


// �X�e�[�g�J�n
void LacrosseState_PlayerControllMove::Enter(LacrossePlayer* t)
{
	// �ړ��N���X�쐬
	m_pMoveClass = this->CreateMoveClass(t);
}


// �X�e�[�g���s
void LacrosseState_PlayerControllMove::Execute(LacrossePlayer* t)
{
	Vector2 st = controller::GetStickValue(controller::stick::left, t->m_PlayerInfo.number);

	m_pMoveClass->SetStickValue(st);
	m_pMoveClass->Update();
	chr_func::CreateTransMatrix(t, 0.05f, &t->m_Renderer.m_TransMatrix);

	if (controller::GetTRG(controller::button::batu, t->m_PlayerInfo.number))
	{// [�~] �� [���]
		t->SetState(new LacrosseState_PlayerControllEvasion());
		return;
	}

	if (controller::GetTRG(controller::button::shikaku, t->m_PlayerInfo.number))
	{// [��] �� [�ߐڍU��]
		t->SetState(new LacrosseState_PlayerControllAttackClose(0));
		return;
	}

	if (controller::GetTRG(controller::button::sankaku, t->m_PlayerInfo.number))
	{// [��] �� [�������U��]
		t->SetState(new LacrosseState_PlayerControllHitBallAttack());
		return;
	}

	if (controller::GetTRG(controller::button::_R1, t->m_PlayerInfo.number))
	{// [R1] �� [�J�E���^�[�\��]
		t->SetState(new LacrosseState_PlayerControllCounterPose());
		return;
	}
}


// �X�e�[�g�I��
void LacrosseState_PlayerControllMove::Exit(LacrossePlayer* t)
{
	delete m_pMoveClass;
}



//***************************************************
//		�v���C���[����̋ߋ����U���N���X
//***************************************************

// �ő�R���{��
const int LacrosseState_PlayerControllAttackClose::kComboMax = 3;

// �R���X�g���N�^
LacrosseState_PlayerControllAttackClose::LacrosseState_PlayerControllAttackClose(int combo) :
m_ComboCount(combo),
m_DoCombo(false),
m_pAttackClass(nullptr)
{

}


// �X�e�[�g�J�n
void LacrosseState_PlayerControllAttackClose::Enter(LacrossePlayer* t)
{
	static const lacrosse_player::MotionType motion_type[kComboMax] = {
		lacrosse_player::mt_AttackClose_1,
		lacrosse_player::mt_AttackClose_2,
		lacrosse_player::mt_AttackClose_3
	};

	// �U���N���X�쐬
	m_pAttackClass = CreateAttackClass(t, motion_type[m_ComboCount]);
}


// �X�e�[�g���s
void LacrosseState_PlayerControllAttackClose::Execute(LacrossePlayer* t)
{
	// �X�e�B�b�N�̒l�Z�b�g
	m_pAttackClass->SetStickValue(
		controller::GetStickValue(controller::stick::left, t->m_PlayerInfo.number));
	
	// �X�V
	if (m_pAttackClass->Update() == false)
	{
		return;
	}
	
	if (controller::GetPush(controller::button::shikaku, t->m_PlayerInfo.number)&&
		m_pAttackClass->CanDoCombo())
	{// �R���{�t���O �I��
		m_DoCombo = true;
	}

	if (m_DoCombo&&
		m_pAttackClass->CanDoCombo()&&
		m_ComboCount+1 < kComboMax)
	{// �R���{���s
		t->SetState(new LacrosseState_PlayerControllAttackClose(m_ComboCount + 1));
		return;
	}
}


// �X�e�[�g�I��
void LacrosseState_PlayerControllAttackClose::Exit(LacrossePlayer* t)
{
	delete m_pAttackClass;
}


// �ߐڍU���N���X�쐬
LacrosseAttackClose* LacrosseState_PlayerControllAttackClose::CreateAttackClass(LacrossePlayer* t, lacrosse_player::MotionType motion)
{
	static  const LacrosseAttackClose::ComboParams combo_params[kComboMax] = {
		{ 0.5f, 0.3f, PI / 4, 10, 30, 17 },
		{ 0.5f, 0.3f, PI / 4, 10, 30, 17 },
		{ 0.5f, 0.3f, PI / 4, 10, 30, 17 }
	};

	class AttackCloseEvent : public LacrosseAttackClose::Event
	{
		LacrossePlayer* m_pLacrosse; // ���N���X�N���X
		const lacrosse_player::MotionType m_Motion; // �U�����[�V����
	public:
		// �R���X�g���N�^
		AttackCloseEvent(LacrossePlayer* t, const lacrosse_player::MotionType motion) :
			m_pLacrosse(t), m_Motion(motion){}

		// �X�V
		void Update()override
		{
			// ���f���X�V
			m_pLacrosse->m_Renderer.Update(1.0f);

			// �]���s��X�V
			chr_func::CreateTransMatrix(
				m_pLacrosse,
				0.05f,
				&m_pLacrosse->m_Renderer.m_TransMatrix);
		}

		// �_���[�W�J�n
		void DamageStart()
		{// �Ƃ肠�����u���Ă���

		}

		// �U���J�n
		void AttackStart()override
		{
			m_pLacrosse->m_Renderer.SetMotion(m_Motion);
		}

		// �U���I��
		void AttackEnd()override
		{
			// �ʏ�ړ���
			m_pLacrosse->m_Renderer.SetMotion(lacrosse_player::mt_Stand);
			m_pLacrosse->SetState(new LacrosseState_PlayerControllMove());
		}
	};

	return new LacrosseAttackClose(
		t, 
		new AttackCloseEvent(t, motion), 
		combo_params[m_ComboCount]);
}




//***************************************************
//		�v���C���[����̉���N���X
//***************************************************

// �R���X�g���N�^
LacrosseState_PlayerControllEvasion::LacrosseState_PlayerControllEvasion() :
m_pEvasionClass(nullptr)
{

}


// �X�e�[�g�J�n
void LacrosseState_PlayerControllEvasion::Enter(LacrossePlayer* t)
{
	// ����N���X�쐬
	m_pEvasionClass = this->CreateEvasionClass(t);
}


// �X�e�[�g���s
void LacrosseState_PlayerControllEvasion::Execute(LacrossePlayer* t)
{
	// �X�e�B�b�N�̒l�Z�b�g
	m_pEvasionClass->SetStickValue(
		controller::GetStickValue(controller::stick::left, t->m_PlayerInfo.number));

	// �X�V
	if (m_pEvasionClass->Update() == false)
	{
		return;
	}
}


// �X�e�[�g�I��
void LacrosseState_PlayerControllEvasion::Exit(LacrossePlayer* t)
{
	delete m_pEvasionClass;
}


// ����N���X�쐬
LacrosseEvasion* LacrosseState_PlayerControllEvasion::CreateEvasionClass(LacrossePlayer* t)
{
	class EvasionEvent : public LacrosseEvasion::Event
	{
		LacrossePlayer* m_pLacrosse; // ���N���X
	public:
		// �R���X�g���N�^
		EvasionEvent(LacrossePlayer* pLacrosse) :
			m_pLacrosse(pLacrosse){}


		// �X�V
		void Update()override
		{
			// ���f���X�V
			m_pLacrosse->m_Renderer.Update(1.0f);

			// �]���s��X�V
			chr_func::CreateTransMatrix(
				m_pLacrosse, 
				0.05f, 
				&m_pLacrosse->m_Renderer.m_TransMatrix);
		}


		// ����s���J�n
		void EvasionStart()override
		{
			m_pLacrosse->m_Renderer.SetMotion(lacrosse_player::mt_Evasion);
		}


		// ����s���I��
		void EvasionEnd()override
		{
			// �ʏ�ړ���
			m_pLacrosse->m_Renderer.SetMotion(lacrosse_player::mt_Stand);
			m_pLacrosse->SetState(new LacrosseState_PlayerControllMove());
		}
	};

	// ����p�����[�^�ݒ�
	LacrosseEvasion::EvasionParams params;
	params.AllFrame                      = 35;         // �S35�t���[��
	params.MaxTurnRadian            = PI / 4;    // 45��
	params.MoveDownSpeed         = 0.2f;      // ��������
	params.MoveSpeed                  = 0.25f;    // �ړ��X�s�[�h
	params.NoDamageStartFrame = 3;          // �J�n3�t���[���Ŗ��G�J�n
	params.NoDamageEndFrame   = 20;       // �J�n20�t���[���Ŗ��G�I��

	// �쐬
	return new LacrosseEvasion(
		t,
		new EvasionEvent(t),
		params
		);
}




//***************************************************
//		�v���C���[����� �������U�� (�{�[���ł��o��) �N���X
//***************************************************

// �R���X�g���N�^
LacrosseState_PlayerControllHitBallAttack::LacrosseState_PlayerControllHitBallAttack() :
m_pAttackClass(nullptr)
{

}


// �X�e�[�g�J�n
void LacrosseState_PlayerControllHitBallAttack::Enter(LacrossePlayer* t)
{
	m_pAttackClass = this->CreateAttackClass(t);
}


// �X�e�[�g���s
void LacrosseState_PlayerControllHitBallAttack::Execute(LacrossePlayer* t)
{
	// �X�e�B�b�N�̒l�Z�b�g
	m_pAttackClass->SetStickValue(
		controller::GetStickValue(controller::stick::left, t->m_PlayerInfo.number)
		);

	// �X�V
	if (m_pAttackClass->Update() == false)
	{
		return;
	}
}


// �X�e�[�g�I��
void LacrosseState_PlayerControllHitBallAttack::Exit(LacrossePlayer* t)
{
	delete m_pAttackClass;
}


// ����N���X�쐬
LacrosseHitBallAttack* LacrosseState_PlayerControllHitBallAttack::CreateAttackClass(LacrossePlayer* t)
{
	class HitBallEvent : public LacrosseHitBallAttack::Event
	{
		LacrossePlayer* m_pLacrosse; // ���N���X
	public:
		// �R���X�g���N�^
		HitBallEvent(LacrossePlayer* pLacrossePlayer) :
			m_pLacrosse(pLacrossePlayer){}

		// �X�V
		void Update()override
		{
			// ���f���X�V
			m_pLacrosse->m_Renderer.Update(1.0f);

			// �]���s��X�V
			chr_func::CreateTransMatrix(
				m_pLacrosse,
				0.05f,
				&m_pLacrosse->m_Renderer.m_TransMatrix);
		}

		// �_���[�W����J�n
		void DamageStart()
		{// �Ƃ肠�����u���Ă���

		}


		// �U���J�n
		void AttackStart()override
		{
			m_pLacrosse->m_Renderer.SetMotion(lacrosse_player::mt_AttackHitBall);
		}

		// �U���I��
		void AttackEnd()override
		{
			// �ʏ�ړ���
			m_pLacrosse->m_Renderer.SetMotion(lacrosse_player::mt_Stand);
			m_pLacrosse->SetState(new LacrosseState_PlayerControllMove());
		}
	};

	// �U���p�����[�^�쐬
	LacrosseHitBallAttack::AttackParams params;
	params.AllFrame                        = 30;     // �S30�t���[��
	params.AttackPower                  = 10.0f; // �U����
	params.DamageOutbreakFrame = 5;       // �J�n5�t���[���ŋ�����
	params.MaxTurnRadian              = PI / 4; // 45��
	params.MoveDownSpeed           = 0.2f;   // ��������

	// �������ĕԂ�
	return new LacrosseHitBallAttack(
		t,
		new HitBallEvent(t),
		params);
}


//***************************************************
//		�v���C���[����� �J�E���^�[�\���N���X
//***************************************************

// �R���X�g���N�^
LacrosseState_PlayerControllCounterPose::LacrosseState_PlayerControllCounterPose() :
m_pCounterPose(nullptr)
{

}


// �X�e�[�g�J�n
void LacrosseState_PlayerControllCounterPose::Enter(LacrossePlayer* t)
{
	// �J�E���^�[�\���N���X�쐬
	m_pCounterPose = this->CreateCounterPoseClass(t);
}


// �X�e�[�g���s
void LacrosseState_PlayerControllCounterPose::Execute(LacrossePlayer* t)
{
	// �X�e�B�b�N�̒l�Z�b�g
	m_pCounterPose->SetStickValue(
		controller::GetStickValue(controller::stick::left, t->m_PlayerInfo.number)
		);

	if (controller::GetLeave(controller::button::_R1, t->m_PlayerInfo.number))
	{// [R1������] �� [�J�E���^�[] ������[�ʏ�ړ�]��
		t->m_Renderer.SetMotion(lacrosse_player::mt_Stand);
		t->SetState(new LacrosseState_PlayerControllMove());
		return;
	}

	if (m_pCounterPose->Update() == false)
	{
		return;
	}
}


// �X�e�[�g�I��
void LacrosseState_PlayerControllCounterPose::Exit(LacrossePlayer* t)
{
	delete m_pCounterPose;
}


// �J�E���^�[�\���N���X�쐬
LacrosseCounterPose* LacrosseState_PlayerControllCounterPose::CreateCounterPoseClass(LacrossePlayer* t)
{
	class CounterPoseEvent : public LacrosseCounterPose::Event
	{
		LacrossePlayer* m_pLacrosse; // ���N���X
	public:
		// �R���X�g���N�^
		CounterPoseEvent(LacrossePlayer* pLacrossePlayer) :
			m_pLacrosse(pLacrossePlayer){}

		// �X�V
		void Update()override
		{
			// ���f���X�V
			m_pLacrosse->m_Renderer.Update(1.0f);

			// �]���s��X�V
			chr_func::CreateTransMatrix(
				m_pLacrosse,
				0.05f,
				&m_pLacrosse->m_Renderer.m_TransMatrix);
		}


		// �\���J�n
		void PoseStart()override
		{
			// ���[�V�����Z�b�g
			m_pLacrosse->m_Renderer.SetMotion(lacrosse_player::mt_CounterPose);
		}


		// �\���I��
		void PoseEnd()override
		{
			// �Ƃ肠�����ʏ�ړ���
			m_pLacrosse->m_Renderer.SetMotion(lacrosse_player::mt_Stand);
			m_pLacrosse->SetState(new LacrosseState_PlayerControllMove());
		}
	};

	// �\���p�����[�^�ݒ�
	LacrosseCounterPose::CounterPoseParams params;
	params.AllFrame              = 60;      // �S�t���[��
	params.TurnSpeed           = 0.15f;  // �p�x�ω��X�s�[�h
	params.MoveDownSpeed = 0.2f;    // ��������

	// �������ĕԂ�
	return new LacrosseCounterPose(
		t,
		new CounterPoseEvent(t),
		params
		);
}


