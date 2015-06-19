#include "CharacterBase.h"
#include "CharacterCounterPoseClass.h"
#include "CharacterFunction.h"


//***************************************************
//		�L�����N�^�[���� �J�E���^�[�\���N���X
//***************************************************


// �R���X�g���N�^
CharacterCounterPose::CharacterCounterPose(
	const int                               maxLevel,                  // �ő僌�x��
	const CounterPoseParams& counterPoseParams, // �\���p�����[�^
	CharacterBase*                    pCharacter,               // �����������L�����N�^�[
	Event*                                  pEvent	                      // �\���C�x���g
	) :
	m_MaxLevel(maxLevel),
	m_NowLevel(0),
	m_Timer(0),
	m_TotalFrame(0),
	m_CounterPoseParams(counterPoseParams),
	m_pCharacter(pCharacter),
	m_pEvent(pEvent)
{
	m_TotalFrame = (m_MaxLevel*m_CounterPoseParams.LevelUpFrame) + m_CounterPoseParams.MaxPoseFrame;
}


// �f�X�g���N�^
CharacterCounterPose::~CharacterCounterPose()
{
	delete m_pEvent;
}


// �X�V
bool CharacterCounterPose::Update()
{
	if (m_Timer == 0)
	{// �\���J�n
		m_pEvent->PoseStart();
	}

	
	if (m_Timer == ((m_NowLevel + 1)* m_CounterPoseParams.LevelUpFrame))
	{// ���x���A�b�v
		if (m_NowLevel < m_MaxLevel)
		{
			m_NowLevel++;
			m_pEvent->LevelUp(m_NowLevel);
		}
	}

	// ���W�X�V
	chr_func::PositionUpdate(m_pCharacter);

	// ����
	chr_func::XZMoveDown(
		m_pCharacter,
		m_CounterPoseParams.MoveDownSpeed
		);

	// �X�V
	m_pEvent->Update();

	if (m_Timer == m_TotalFrame)
	{// �\���I��
		m_pEvent->PoseEnd();
		return false;
	}

	// �^�C�}�[�X�V
	m_Timer++;

	return true;
}


// �ő僌�x�����ǂ���
bool CharacterCounterPose::IsMaxLevel(int level)const
{
	return (level >= m_MaxLevel);
}

bool CharacterCounterPose::IsMaxLevel()const
{
	return m_NowLevel >= m_MaxLevel;
}

