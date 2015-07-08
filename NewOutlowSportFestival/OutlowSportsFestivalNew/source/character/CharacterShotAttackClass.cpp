#include "CharacterBase.h"
#include "CharacterShotAttackClass.h"
#include "CharacterFunction.h"


//***************************************************
//		���N���X�p �������U�� (�{�[���ł��o��) �N���X
//***************************************************

// �R���X�g���N�^
CharacterShotAttack::CharacterShotAttack(
	CharacterBase* pCharacter,
	Event* pEvent,
	const AttackParams& attack_params,
	HitEventBase*    pHitEventBase
	) :
	m_AttackParams(attack_params),
	m_StickValue(0, 0),
	m_pCharacter(pCharacter),
	m_Timer(0),
	m_pEvent(pEvent),
	m_pHitEventBase(pHitEventBase)
{

}


// �f�X�g���N�^
CharacterShotAttack::~CharacterShotAttack()
{
	delete m_pEvent;
	delete m_pHitEventBase;
}


// �X�V
bool CharacterShotAttack::Update()
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

	if (m_Timer == m_AttackParams.ShotFrame)
	{// �_���[�W�����t���[��
		m_pEvent->Shot();
	}

	if (m_Timer >= m_AttackParams.AllFrame)
	{// �U���I��
		m_pEvent->AttackEnd();
		return false;
	}

	// �^�C�}�[�X�V
	m_Timer++;

	// �_���[�W������Ƃ�
	chr_func::DamageCheck(m_pCharacter, m_pHitEventBase);

	return true;
}


// �X�e�B�b�N�̒l�Z�b�g
void CharacterShotAttack::SetStickValue(CrVector2 stickValue)
{
	m_StickValue = stickValue;
}

