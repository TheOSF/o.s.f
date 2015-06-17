#include "CharacterBase.h"
#include "CharacterHitBallAttackClass.h"
#include "CharacterFunction.h"


//***************************************************
//		���N���X�p �������U�� (�{�[���ł��o��) �N���X
//***************************************************

// �R���X�g���N�^
CharacterHitBallAttack::CharacterHitBallAttack(
	CharacterBase* pCharacter,
	Event* pEvent,
	const AttackParams& attack_params
	) :
	m_AttackParams(attack_params),
	m_StickValue(0, 0),
	m_pCharacter(pCharacter),
	m_Timer(0),
	m_pEvent(pEvent)
{

}


// �f�X�g���N�^
CharacterHitBallAttack::~CharacterHitBallAttack()
{
	delete m_pEvent;
}


// �X�V
bool CharacterHitBallAttack::Update()
{
	if (m_Timer == 0)
	{// �U���J�n
		m_pEvent->AttackStart();

		// �����␳
		chr_func::AngleControll(
			m_pCharacter,
			m_pCharacter->m_Params.pos + Vector3(m_StickValue.x, 0, m_StickValue.y),
			m_AttackParams.MaxTurnRadian
			);
	}

	// ���W�X�V
	chr_func::PositionUpdate(m_pCharacter);

	// ����
	chr_func::XZMoveDown(
		m_pCharacter,
		m_AttackParams.MoveDownSpeed);

	// �X�V
	m_pEvent->Update();

	if (m_Timer == m_AttackParams.DamageOutbreakFrame)
	{// �_���[�W�����t���[��
		m_pEvent->DamageStart();
	}

	if (m_Timer >= m_AttackParams.AllFrame)
	{// �U���I��
		m_pEvent->AttackEnd();
		return false;
	}

	// �^�C�}�[�X�V
	m_Timer++;

	return true;
}


// �X�e�B�b�N�̒l�Z�b�g
void CharacterHitBallAttack::SetStickValue(CrVector2 stickValue)
{
	m_StickValue = stickValue;
}
