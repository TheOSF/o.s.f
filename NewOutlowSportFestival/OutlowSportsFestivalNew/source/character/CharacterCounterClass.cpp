
#include "CharacterCounterClass.h"
#include "CharacterBase.h"
#include "CharacterFunction.h"

//***************************************************
//		�L�����N�^�[���� �J�E���^�[�N���X
//***************************************************

// �R���X�g���N�^
CharacterCounter::CharacterCounter(
	const CounterParams& counterParams,  // �J�E���^�[�p�����[�^
	CharacterBase*            pCharacter,         // �����������L�����N�^�[
	Event*                          pEvent                // �J�E���^�[�C�x���g
	) :
	m_Timer(0),
	m_StickValue(0, 0),
	m_CounterParams(counterParams),
	m_pCharacter(pCharacter),
	m_pEvent(pEvent)
{

}


// �f�X�g���N�^
CharacterCounter::~CharacterCounter()
{
	delete m_pEvent;
}


// �X�V
bool CharacterCounter::Update()
{
	if (m_Timer == 0)
	{// �J�E���^�[�J�n
		m_pEvent->CounterStart(m_CounterParams.Level);
	}

	// ���W�X�V
	chr_func::PositionUpdate(m_pCharacter);

	// ����
	chr_func::XZMoveDown(
		m_pCharacter,
		m_CounterParams.MoveDownSpeed
		);

	// �X�V
	m_pEvent->Update();

	if (m_Timer >= m_CounterParams.TotalFrame)
	{// �J�E���^�[�I��
		m_pEvent->CounterEnd();
		return false;
	}

	// �^�C�}�[�X�V
	m_Timer++;

	return true;
}


// �X�e�B�b�N�̒l�Z�b�g
void CharacterCounter::SetStickValue(CrVector2 stickValue)
{
	m_StickValue = stickValue;
}

