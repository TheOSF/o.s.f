
#include "LacrosseAttackClose.h"



//***************************************************
//		���N���X�p�ߋ����U���N���X
//***************************************************

// �R���X�g���N�^
LacrosseAttackClose::LacrosseAttackClose(
	LacrossePlayer* pLacrossePlayer,
	const Params& param,
	AttackEvent* pAttackEvent
	) :
	m_pAttackEvent(pAttackEvent),
	m_StickValue(0, 0),
	m_pLacrossePlayer(pLacrossePlayer),
	m_Timer(0),
	m_Params(param)
{

}


// �f�X�g���N�^
LacrosseAttackClose::~LacrosseAttackClose()
{
	delete m_pAttackEvent;
}


// �X�V
void LacrosseAttackClose::Update()
{
	// �^�C�}�[�X�V
	m_Timer++;

	if (m_Timer == m_Params.DamageOutbreakFrame)
	{// �_���[�W����
		m_pAttackEvent->DamageStart();
	}

	if (m_Timer == m_Params.EndFrame)
	{// �U���I��
		m_pAttackEvent->AttackEnd();
	}

	// �X�V
	m_pAttackEvent->Update();



}


// �X�e�B�b�N�̒l�Z�b�g
void LacrosseAttackClose::SetStickValue(CrVector2 StickValue)
{
	m_StickValue = StickValue;
}
