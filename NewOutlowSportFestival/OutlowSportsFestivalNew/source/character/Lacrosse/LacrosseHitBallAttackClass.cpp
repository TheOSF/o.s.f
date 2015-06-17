#include "LacrossePlayer.h"
#include "LacrosseHitBallAttackClass.h"
#include "../CharacterFunction.h"


//***************************************************
//		���N���X�p �������U�� (�{�[���ł��o��) �N���X
//***************************************************

// �R���X�g���N�^
LacrosseHitBallAttack::LacrosseHitBallAttack(
	LacrossePlayer* pLacrossePlayer,
	Event* pEvent,
	const AttackParams& attack_params
	) :
	m_AttackParams(attack_params),
	m_StickValue(0, 0),
	m_pLacrossePlayer(pLacrossePlayer),
	m_Timer(0),
	m_pEvent(pEvent)
{

}


// �f�X�g���N�^
LacrosseHitBallAttack::~LacrosseHitBallAttack()
{
	delete m_pEvent;
}


// �X�V
bool LacrosseHitBallAttack::Update()
{
	if (m_Timer == 0)
	{// �U���J�n
		m_pEvent->AttackStart();

		// �����␳
		chr_func::AngleControll(
			m_pLacrossePlayer,
			m_pLacrossePlayer->m_Params.pos + Vector3(m_StickValue.x, 0, m_StickValue.y) ,
			m_AttackParams.MaxTurnRadian
			);
	}

	// ���W�X�V
	chr_func::PositionUpdate(m_pLacrossePlayer);

	// ����
	chr_func::XZMoveDown(
		m_pLacrossePlayer,
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
void LacrosseHitBallAttack::SetStickValue(CrVector2 stickValue)
{
	m_StickValue = stickValue;
}

