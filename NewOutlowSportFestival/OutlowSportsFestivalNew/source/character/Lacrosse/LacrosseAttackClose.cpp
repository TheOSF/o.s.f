#include "LacrossePlayer.h"
#include "LacrosseAttackClose.h"
#include "../CharacterFunction.h"

namespace lacrosse_player
{
	// �Ƃ肠�����萔
	static const int AttackCloseStartFrame = 0;
	static const int AttackCloseEndFrame = 60;
}

//***************************************************
//		���N���X�p�ߋ����U���N���X
//***************************************************

// �R���X�g���N�^
LacrosseAttackClose::LacrosseAttackClose(
	LacrossePlayer* pLacrossePlayer,
	Event* pEvent
	) :
	m_StickValue(0, 0),
	m_pLacrossePlayer(pLacrossePlayer),
	m_Timer(0),
	m_pEvent(pEvent)
{

}


// �f�X�g���N�^
LacrosseAttackClose::~LacrosseAttackClose()
{

}


// �X�V
void LacrosseAttackClose::Update()
{
	// �����Ȃ��悤��
	chr_func::SetMaxXZspeed(m_pLacrossePlayer, 0.0f);

	if (m_Timer == lacrosse_player::AttackCloseStartFrame)
	{
		m_pEvent->AttackStart();
	}

	if (m_Timer == lacrosse_player::AttackCloseEndFrame)
	{
		m_pEvent->AttackEnd();
	}

	m_pEvent->Update();

	// �^�C�}�[�X�V
	m_Timer++;

}


// �X�e�B�b�N�̒l�Z�b�g
void LacrosseAttackClose::SetStickValue(CrVector2 StickValue)
{
	m_StickValue = StickValue;
}

