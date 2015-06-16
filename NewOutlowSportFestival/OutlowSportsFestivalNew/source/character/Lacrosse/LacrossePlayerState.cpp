#include "LacrossePlayerState.h"
#include "../../GameSystem/GameController.h"
#include "../CharacterFunction.h"

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
CharacterUsualMove::MoveEvent* LacrosseState_PlayerControllMove::CreateMoveEvent(LacrossePlayer* t)
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

	return new LacrosseMoveEvent(t);
}


// �X�e�[�g�J�n
void LacrosseState_PlayerControllMove::Enter(LacrossePlayer* t)
{
	// �ړ��p�����[�^�ݒ�
	CharacterUsualMove::Params p;
	p.Acceleration = 0.2f;
	p.MaxSpeed = 0.23f;
	p.TurnSpeed = 0.3f;
	p.DownSpeed = 0.2f;

	// �ړ��N���X�쐬
	m_pMoveClass = new CharacterUsualMove(t, p, this->CreateMoveEvent(t));

}


// �X�e�[�g���s
void LacrosseState_PlayerControllMove::Execute(LacrossePlayer* t)
{
	Vector2 st = controller::GetStickValue(controller::stick::left, t->m_PlayerInfo.number);

	m_pMoveClass->SetStickValue(st);
	m_pMoveClass->Update();
	chr_func::CreateTransMatrix(t, 0.05f, &t->m_Renderer.m_TransMatrix);


	if (controller::GetTRG(controller::button::shikaku, t->m_PlayerInfo.number))
	{
		t->SetState(new LacrosseState_PlayerControllAttackClose(0));
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
m_DoCombo(false)
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
			chr_func::CreateTransMatrix(m_pLacrosse, 0.05f, &m_pLacrosse->m_Renderer.m_TransMatrix);
		}

		// �_���[�W�J�n
		void DamageStart()
		{

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

