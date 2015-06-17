#include "LacrossePlayer.h"
#include "LacrosseAttackClose.h"
#include "../CharacterFunction.h"


//***************************************************
//		���N���X�p�ߋ����U���N���X
//***************************************************

// �R���X�g���N�^
LacrosseAttackClose::LacrosseAttackClose(
	LacrossePlayer* pLacrossePlayer,
	Event* pEvent,
	const ComboParams& combo_params
	) :
	m_ComboParams(combo_params), 
	m_StickValue(0, 0),
	m_pLacrossePlayer(pLacrossePlayer),
	m_Timer(0),
	m_pEvent(pEvent)
{

}


// �f�X�g���N�^
LacrosseAttackClose::~LacrosseAttackClose()
{
	delete m_pEvent;
}


// �X�V
bool LacrosseAttackClose::Update()
{
	if (m_Timer == 0)
	{// �U���J�n
		m_pEvent->AttackStart();

		// �ړ�
		chr_func::AddMoveFront(
			m_pLacrossePlayer,
			m_ComboParams.MoveSpeed,
			m_ComboParams.MoveSpeed
			);

		// �ړ������␳
		chr_func::AddXZMove(
			m_pLacrossePlayer,
			m_StickValue.x,
			m_StickValue.y,
			m_ComboParams.MoveSpeed
			);

		// �����␳
		chr_func::AngleControll(
			m_pLacrossePlayer,
			m_pLacrossePlayer->m_Params.pos + m_pLacrossePlayer->m_Params.move,
			m_ComboParams.MaxTurnRadian
			);
	}

	// ���W�X�V
	chr_func::PositionUpdate(m_pLacrossePlayer);

	// ����
	chr_func::XZMoveDown(
		m_pLacrossePlayer,
		m_ComboParams.MoveDownSpeed
		);

	// �X�V
	m_pEvent->Update();

	if (m_Timer == m_ComboParams.DamageOutbreakFrame)
	{// �_���[�W�����t���[��
		m_pEvent->DamageStart();
	}

	if (m_Timer >= m_ComboParams.AllFrame)
	{// �U���I��
		m_pEvent->AttackEnd();
		return false;
	}

	// �^�C�}�[�X�V
	m_Timer++;

	return true;
}


// �X�e�B�b�N�̒l�Z�b�g
void LacrosseAttackClose::SetStickValue(CrVector2 stickValue)
{
	m_StickValue = stickValue;
}


// �R���{�ł��邩�ǂ���
bool LacrosseAttackClose::CanDoCombo()const
{
	return (m_Timer >= m_ComboParams.CanDoComboFrame);
}


// �R���{���s�ł��邩�ǂ���
bool LacrosseAttackClose::CanGoNextCombo()const
{
	return (m_Timer >= m_ComboParams.GoNextComboFrame);
}

