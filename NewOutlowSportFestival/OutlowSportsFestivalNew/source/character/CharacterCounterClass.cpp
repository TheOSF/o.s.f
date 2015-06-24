
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
	m_ButtonState(controller::button::bs_up),
	m_StickValue(0, 0),
	m_NowLevel(0),
	m_Step(CounterStep::cs_pose),
	m_CounterParams(counterParams),
	m_MaxLevel(maxLevel),
	m_pCharacter(pCharacter),
	m_pEvent(pEvent),
	m_LevelUpTimer(0),
	m_MoveTimer(0),
	m_PoseTimer(0),
	m_SwingTimer(0),
	m_pCounterBallOwner(nullptr),
	m_pCounterBall(nullptr),
	m_CounterPos(pCharacter->m_Params.pos)
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
	// �ʏ�ړ��X�V
	UsualMoveUpdate();

	// �X�V
	m_pEvent->Update();

	if (m_Step & cs_pose)
	{// �\����

		// �J�E���^�[�ł���{�[����T��
		this->SerchCounterBall();

		UpdatePose();
	}


	if (m_Step & cs_move_to_ball)
	{// �ړ���
		UpdateMove();
	}


	if (m_Step & cs_swing)
	{// �X�C���O��
		UpdateSwing();
	}

	return true;
}


// ���x���A�b�v�̍X�V
void CharacterCounter::UpdateLevelUp()
{
	if ((m_NowLevel < m_MaxLevel) &&
		(m_Step & (cs_pose | cs_move_to_ball)))
	{
		if (m_LevelUpTimer == m_CounterParams.LevelUpFrame)
		{// ���x���A�b�v
			m_LevelUpTimer = 0;
			m_NowLevel++;
			m_pEvent->LevelUp(m_NowLevel);
		}
	}
}


// �\�����̍X�V
void CharacterCounter::UpdatePose()
{
	if (m_PoseTimer == 0)
	{// �\���J�n
		m_pEvent->PoseStart();
	}

	if (((m_NowLevel == m_MaxLevel) && m_PoseTimer == m_CounterParams.MaxPoseFrame) ||
		(m_ButtonState == controller::button::bs_up))
	{// �\���I��
		m_Step &= ~cs_pose;
		m_pEvent->PoseEnd();
	}

	if (m_ButtonState == controller::button::bs_up)
	{// �\���I��
		m_Step &= ~cs_pose;
		m_pEvent->PoseEnd();

		// �{�^���������ꂽ��X�C���O
		m_Step |= cs_swing;
	}

	// �^�C�}�[�X�V
	m_PoseTimer++;
}


// �ړ����̍X�V
void CharacterCounter::UpdateMove()
{
	if (m_MoveTimer == m_CounterParams.CounterMoveFrame)
	{// �ړ��I��
		m_Step &= ~cs_move_to_ball;

		// �{�[����ł�
		this->HitBall();

		return;
	}

	// �ړ�
	MoveToBall();

	// �^�C�}�[�X�V
	m_MoveTimer++;
}


// �X�C���O���̍X�V
void CharacterCounter::UpdateSwing()
{
	if (m_SwingTimer == 0)
	{// �X�C���O�J�n

		m_pEvent->SwingStart();
	}


	if (m_SwingTimer == m_CounterParams.SwingTotalFrame)
	{// �X�C���O�I��

		m_pEvent->SwingEnd();
	}

	// �^�C�}�[�X�V
	m_SwingTimer++;
}


// �ʏ�̈ړ��X�V
void CharacterCounter::UsualMoveUpdate()
{
	// ����
	chr_func::XZMoveDown(m_pCharacter, m_CounterParams.MoveDownSpeed);

	// ���W�X�V
	chr_func::PositionUpdate(m_pCharacter);

}


// �{�[���Ɍ������ē���
void CharacterCounter::MoveToBall()
{
	if (m_pCounterBall)
	{
		float t = 1.0f / m_CounterParams.CounterMoveFrame;

		Vector3 &pos = m_pCharacter->m_Params.pos;

		pos = pos * (1.0f - t) + m_CounterPos*t;
	}
}


// �{�[����ł��Ԃ�
void CharacterCounter::HitBall()
{
	if (m_pCounterBall &&
		BallBase::isCanCounter(m_pCounterBall) == true)
	{// �J�E���^�[�ł���{�[�����ǂ���

		if (m_pCounterBallOwner &&
			m_pCounterBallOwner != m_pCharacter &&
			m_pCounterBallOwner == m_pCounterBall->m_Params.pParent
			)
		{// �ł����̂���������Ȃ� ���� �ړ����ɂق��̐l�ɃJ�E���^�[����Ă��Ȃ�

			// �Ƃ肠�����{�[���ł����l�̂Ƃ���֕Ԃ�
			Vector3 vec = m_pCounterBallOwner->m_Params.pos - m_pCharacter->m_Params.pos;

			// �ړ����x�ݒ�
			vec.Normalize();
			vec *= m_pCounterBall->m_Params.move.Length();

			// �ړ������]��
			m_pCounterBall->m_Params.move = vec;

			// �ł����l�ύX
			m_pCounterBall->m_Params.pParent = m_pCharacter;

			// �ł��Ԃ��C�x���g
			m_pEvent->HitBall(false);
		}
	}
}


// �J�E���^�[�ł���{�[����T��
bool CharacterCounter::SerchCounterBall()
{
	bool result =  DefBallMgr.GetCounterBall(
		&m_pCounterBall,
		m_pCharacter->m_Params.pos,
		&m_CounterPos,
		m_CounterParams.CanCounterArea,
		m_CounterParams.CounterMoveFrame
		);

	if (result == false)
	{
		m_pCounterBallOwner = nullptr;
		m_pCounterBall = nullptr;
		m_CounterPos = m_pCharacter->m_Params.pos;
		return false;
	}

	m_Step |= cs_move_to_ball;
	m_pCounterBallOwner = m_pCounterBall->m_Params.pParent;
	m_pEvent->BallEnter();
	return true;
}


