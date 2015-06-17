#include "CharacterBase.h"
#include "CharacterEvasionClass.h"
#include "CharacterFunction.h"


//***************************************************
//		���N���X�p����N���X
//***************************************************


// �R���X�g���N�^
CharacterEvasion::CharacterEvasion(
	CharacterBase* pCharacterBase,
	Event* pEvent,
	const EvasionParams& evasion_params
	) :
	m_EvasionParams(evasion_params),
	m_StickValue(0, 0),
	m_pCharacterBase(pCharacterBase),
	m_Timer(0),
	m_pEvent(pEvent)
{

}


// �f�X�g���N�^
CharacterEvasion::~CharacterEvasion()
{
	delete m_pEvent;
}


// �X�V
bool CharacterEvasion::Update()
{
	// �ړ�
	chr_func::AddMoveFront(
		m_pCharacterBase,
		m_EvasionParams.MoveSpeed,
		m_EvasionParams.MoveSpeed);

	if (m_Timer == 0)
	{// ����J�n
		m_pEvent->EvasionStart();

		// �ړ������␳
		chr_func::AddXZMove(
			m_pCharacterBase,
			m_StickValue.x,
			m_StickValue.y,
			m_EvasionParams.MoveSpeed);

		// �����␳
		chr_func::AngleControll(
			m_pCharacterBase,
			m_pCharacterBase->m_Params.pos + m_pCharacterBase->m_Params.move,
			m_EvasionParams.MaxTurnRadian
			);
	}

	// ���W�X�V
	chr_func::PositionUpdate(m_pCharacterBase);

	// ����
	chr_func::XZMoveDown(
		m_pCharacterBase,
		m_EvasionParams.MoveDownSpeed);

	// �X�V
	m_pEvent->Update();

	if (m_Timer >= m_EvasionParams.AllFrame)
	{// ����I��
		m_pEvent->EvasionEnd();
		return false;
	}

	// �^�C�}�[�X�V
	m_Timer++;
	
	return true;
}


// �X�e�B�b�N�̒l�Z�b�g
void CharacterEvasion::SetStickValue(CrVector2 stickValue)
{
	m_StickValue = stickValue;
}


// �_���[�W���󂯂邱�Ƃ��ł��邩�ǂ���
bool CharacterEvasion::CanGetDamage()const
{
	return (
		m_Timer < m_EvasionParams.NoDamageStartFrame || 
		m_Timer >= m_EvasionParams.NoDamageEndFrame
		);
}
