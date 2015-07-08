#include "CharacterAttack.h"
#include "CharacterFunction.h"
#include "CharacterBase.h"


//****************************************************************
//		�L�����N�^���ʂ̍U���N���X
//****************************************************************

CharacterNearAttack::CharacterNearAttack(
	CharacterBase*	pParent,
	const Params&	param,
	AttackEvent*		pMoveEvent) :
	m_StickValue(0, 0),
	m_pCharacter(pParent),
	m_timer(0),
	m_pAttackEvent(pMoveEvent)
{
	m_Params = param;
}
CharacterNearAttack::~CharacterNearAttack()
{
	delete m_pAttackEvent;
}
bool CharacterNearAttack::Update()
{
	if (m_timer == 0)
	{
		// �U���J�n
		m_pAttackEvent->AttackStart();

		// �ړ�
		chr_func::AddMoveFront(
			m_pCharacter,
			m_Params.speed,
			m_Params.speed
			);

		// �ړ������␳
		chr_func::AddXZMove(
			m_pCharacter,
			m_StickValue.x,
			m_StickValue.y,
			m_Params.speed
			);
		// �����␳
		chr_func::AngleControll(
			m_pCharacter,
			m_pCharacter->m_Params.pos + Vector3(m_StickValue.x, 0, m_StickValue.y),
			m_Params.TurnSpeed
			);
	}
	// ���W�X�V
	chr_func::PositionUpdate(m_pCharacter);

	// ����
	chr_func::XZMoveDown(
		m_pCharacter,
		m_Params.speed);

	// �X�V
	m_pAttackEvent->Update();

	if (m_timer == m_Params.AttackFrame)
	{// �_���[�W�����t���[��
		m_pAttackEvent->Assault();
	}
	if (m_timer >= m_Params.EndFrame)
	{// �U���I��
		m_pAttackEvent->AttackEnd();
		return false;
	}
	// �^�C�}�[�X�V
	m_timer++;

	return true;
}
void CharacterNearAttack::SetStickValue(CrVector2 StickValue)
{
	m_StickValue = StickValue;
}
// �R���{�ł��邩�ǂ���
bool CharacterNearAttack::CanDoCombo()const
{
	return (m_timer >= m_Params.CanDoComboFrame);
}
// �R���{���s�ł��邩�ǂ���
bool CharacterNearAttack::CanGoNextCombo()const
{
	return (m_timer >= m_Params.GoNextComboFrame);
}