
#include "CharacterCounterClass.h"
#include "CharacterBase.h"
#include "CharacterFunction.h"

#include "../Ball/Ball.h"


//***************************************************
//		�L�����N�^�[���� �J�E���^�[�N���X
//***************************************************

// �R���X�g���N�^
CharacterCounter::CharacterCounter(
	const int                       maxLevel,           // �ő僌�x��
	const CounterParams& counterParams, // �J�E���^�[�p�����[�^
	CharacterBase*            pCharacter,        // �����������L�����N�^�[
	Event*                          pEvent               // �J�E���^�[�C�x���g
	) :
	m_MaxLevel(maxLevel),
	m_NowLevel(0),
	m_Timer(0),
	m_TotalPoseFrame(0),
	m_PoseFlg(true),
	m_StickValue(0, 0),
	m_CounterParams(counterParams),
	m_pCharacter(pCharacter),
	m_pEvent(pEvent),
	m_pCounterBall(nullptr),
	m_pCounterBallOwner(nullptr),
	m_CounterPos(m_pCharacter->m_Params.pos)
{
	m_TotalPoseFrame = (m_MaxLevel*m_CounterParams.LevelUpFrame) + m_CounterParams.MaxPoseFrame;
}


// �f�X�g���N�^
CharacterCounter::~CharacterCounter()
{
	delete m_pEvent;
}


// �X�V
bool CharacterCounter::Update()
{
	if (m_PoseFlg)
	{
		if (m_Timer == 0)
		{// �\���J�n
			m_pEvent->CounterPoseStart();
		}

		if (m_Timer == ((m_NowLevel + 1)*m_CounterParams.LevelUpFrame))
		{// ���x���A�b�v
			if (m_NowLevel < m_MaxLevel)
			{
				m_NowLevel++;
				m_pEvent->LevelUp(m_NowLevel);
			}
		}

		if (m_Timer == m_TotalPoseFrame)
		{// �\���I��
			m_PoseFlg = false;
			m_Timer = 0;
			m_pEvent->CounterPoseEnd();
		}
	}
	else
	{
		if (m_Timer == 0)
		{
			// �{�[������
			bool result = DefBallMgr.GetCounterBall(
				&m_pCounterBall,
				m_pCharacter->m_Params.pos,
				&m_CounterPos,
				m_CounterParams.CanCounterArea,
				m_CounterParams.CounterMoveFrame
				);

			if (result == true &&
				m_pCounterBall->m_Params.pParent != m_pCharacter)
			{
				// ��������
				// �J�E���^�[�ł���{�[���Ȃ�
				m_pCounterBallOwner = m_pCounterBall->m_Params.pParent;
			}
			else
			{
				// ������Ȃ�����
				m_CounterPos = m_pCharacter->m_Params.pos;
			}
		}

		if (m_Timer < m_CounterParams.CounterMoveFrame)
		{// �ړ�
			float t = 1.0f / m_CounterParams.CounterMoveFrame;
			m_pCharacter->m_Params.pos =
				(m_pCharacter->m_Params.pos*(1.0f - t)) + (m_CounterPos*t);
		}

		if (m_Timer == m_CounterParams.CounterMoveFrame)
		{// �J�E���^�[�J�n
			m_pEvent->CounterStart(m_NowLevel);

			if (m_pCounterBall != nullptr && m_pCounterBallOwner != nullptr)
			{// �{�[��������΃J�E���^�[
				float speed = m_pCounterBall->m_Params.move.Length();
				m_pCounterBall->m_Params.move = (m_pCounterBallOwner->m_Params.pos - m_pCharacter->m_Params.pos);
				m_pCounterBall->m_Params.move.Normalize();
				m_pCounterBall->m_Params.move *= speed;
				m_pCounterBall->m_Params.pParent = m_pCharacter;
			}
		}

		if (m_Timer == m_CounterParams.CounterTotalFrame)
		{// �J�E���^�[�I��
			m_pEvent->CounterEnd();
		}
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

	// �^�C�}�[�X�V
	m_Timer++;

	return true;
}


// level ���ő僌�x�����ǂ���
bool CharacterCounter::IsMaxLevel(int level)const
{
	return (level >= m_MaxLevel);
}


// ���ݍő僌�x�����ǂ���
bool CharacterCounter::IsMaxLevel()const
{
	return (m_NowLevel >= m_MaxLevel);
}


// ���߃t���O�Z�b�g
void CharacterCounter::SetPoseEndFlg()
{
	if (m_PoseFlg == true)
	{
		m_PoseFlg = false;
		m_Timer = 0;
	}
}