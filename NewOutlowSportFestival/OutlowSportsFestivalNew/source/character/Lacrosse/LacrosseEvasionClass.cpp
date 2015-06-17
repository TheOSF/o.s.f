#include "LacrossePlayer.h"
#include "LacrosseEvasionClass.h"
#include "../CharacterFunction.h"


//***************************************************
//		���N���X�p����N���X
//***************************************************


// �R���X�g���N�^
LacrosseEvasion::LacrosseEvasion(
	LacrossePlayer* pLacrossePlayer,
	Event* pEvent,
	const EvasionParams& evasion_params
	) :
	m_EvasionParams(evasion_params),
	m_StickValue(0, 0),
	m_pLacrossePlayer(pLacrossePlayer),
	m_Timer(0),
	m_pEvent(pEvent)
{

}


// �f�X�g���N�^
LacrosseEvasion::~LacrosseEvasion()
{
	delete m_pEvent;
}


// �X�V
bool LacrosseEvasion::Update()
{
	// �ړ�
	chr_func::AddMoveFront(
		m_pLacrossePlayer,
		m_EvasionParams.MoveSpeed,
		m_EvasionParams.MoveSpeed);

	if (m_Timer == 0)
	{// ����J�n
		m_pEvent->EvasionStart();

		// �ړ������␳
		chr_func::AddXZMove(
			m_pLacrossePlayer,
			m_StickValue.x,
			m_StickValue.y,
			m_EvasionParams.MoveSpeed);

		// �����␳
		chr_func::AngleControll(
			m_pLacrossePlayer,
			m_pLacrossePlayer->m_Params.pos + m_pLacrossePlayer->m_Params.move,
			m_EvasionParams.MaxTurnRadian
			);
	}

	// ���W�X�V
	chr_func::PositionUpdate(m_pLacrossePlayer);

	// ����
	chr_func::XZMoveDown(
		m_pLacrossePlayer,
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
void LacrosseEvasion::SetStickValue(CrVector2 stickValue)
{
	m_StickValue = stickValue;
}


// �_���[�W���󂯂邱�Ƃ��ł��邩�ǂ���
bool LacrosseEvasion::CanGetDamage()const
{
	return (
		m_Timer < m_EvasionParams.NoDamageStartFrame || 
		m_Timer >= m_EvasionParams.NoDamageEndFrame
		);
}
