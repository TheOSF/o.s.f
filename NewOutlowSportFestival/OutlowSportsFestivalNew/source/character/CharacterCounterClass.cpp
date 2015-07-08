
#include "CharacterCounterClass.h"
#include "CharacterBase.h"
#include "CharacterFunction.h"

#include "CharacterMoveClass.h"

#include "../Ball/Ball.h"


//***************************************************
//		�L�����N�^�[���� �J�E���^�[�N���X
//***************************************************

// �R���X�g���N�^
CharacterCounter::CharacterCounter(
	CharacterBase*                             pParent,                          // �����������L�����N�^�[
	const CounterParams&                  counterParams,               // �J�E���^�[�p�����[�^
	CounterEvent*                               pCounterEvent                // �J�E���^�[�C�x���g
	) :
	m_CounterParams(counterParams),
	m_StickValue(0, 0),
	m_ButtonState(controller::button::bs_down),
	m_NowLevel(0),
	m_Step(_cs_pose),
	m_IsJust(false),
	m_Timer({ 0 }),
	m_pParent(pParent),
	m_pCounterEvent(pCounterEvent),
	m_pCounterBall(nullptr),
	m_pCounterBallParent(nullptr),
	m_CounterPos(m_pParent->m_Params.pos)
{

}


// �f�X�g���N�^
CharacterCounter::~CharacterCounter()
{
	delete m_pCounterEvent;
}


// �X�V
void CharacterCounter::Update()
{
	// �ړ��X�V
	UpdateUsualMove();

	// �X�V
	m_pCounterEvent->Update();

	// �\����
	if (m_Step & _cs_pose)
	{
		UpdateLevelUp();
		UpdatePose();
	}

	// �{�[���Ɍ������Ĉړ���
	if (m_Step & _cs_move_to_ball)
	{
		UpdateMoveToBall();
	}

	// �X�C���O��
	if (m_Step & _cs_swing)
	{
		UpdateSwing();
	}

}


// ���x���A�b�v�̍X�V
void CharacterCounter::UpdateLevelUp()
{
	if (m_NowLevel < m_CounterParams.MaxCounterLevel)
	{
		if (m_Timer.LevelUp == m_CounterParams.LevelUpFrame)
		{
			m_Timer.LevelUp = 0;
			m_NowLevel++;
			m_Timer.Pose = 0;

			// ���x���A�b�v�C�x���g
			m_pCounterEvent->LevelUp(m_NowLevel);
		}
	}

	// �^�C�}�[�X�V
	m_Timer.LevelUp++;
}


// �\�����̍X�V
void CharacterCounter::UpdatePose()
{
	// �\���I��?
	bool is_pose_end = false;

	if (m_Timer.Pose == 0)
	{
		if (m_NowLevel == 0)
		{
			// �\���J�n�C�x���g
			m_pCounterEvent->PoseStart();
		}
	}

	if (m_ButtonState == controller::button::bs_up)
	{
		is_pose_end = true;
	}

	if (m_NowLevel == m_CounterParams.MaxCounterLevel)
	{
		if (m_Timer.Pose == m_CounterParams.MaxPoseFrame)
		{
			is_pose_end = true;
		}
	}

	if (is_pose_end == true)
	{
		// �\���I��
		m_Step &= ~_cs_pose;
		m_Step |= _cs_move_to_ball;
		m_pCounterEvent->PoseEnd();

		// �{�[���T��
		SerchCounterBall();

		// �^�C�~���O����
		if (IsCanCounter() == true)
		{
			CalcHitTiming();
		}
	}
	else
	{
		// �^�C�}�[�X�V
		m_Timer.Pose++;
	}

	
}


// �ړ����̍X�V
void CharacterCounter::UpdateUsualMove()
{
	chr_func::XZMoveDown(m_pParent, m_CounterParams.MoveDownSpeed);

	chr_func::PositionUpdate(m_pParent);
}


// �X�C���O���̍X�V
void CharacterCounter::UpdateSwing()
{
	if (m_Timer.Swing == 0)
	{
		// �X�C���O�J�n
		m_pCounterEvent->SwingStart();
	}


	if (m_Timer.Swing == m_CounterParams.SwingTotalFrame)
	{
		// �X�C���O�I��
		m_pCounterEvent->SwingEnd();
	}

	// �^�C�}�[�X�V
	m_Timer.Swing++;
}


// �{�[���Ɍ������Ĉړ�����
void CharacterCounter::UpdateMoveToBall()
{
	bool is_end = m_Timer.MoveToBall == m_CounterParams.MoveToBallFrame;

	if (is_end == true)
	{
		// �ړ��I��
		m_Step &= ~_cs_move_to_ball;
		m_Step |= _cs_swing;
	}

	if (IsCanCounter() == true)
	{
		// �{�[���Ɍ������Ĉړ�
		Vector3& pos = m_pParent->m_Params.pos;
		float t = 1.0f / m_CounterParams.MoveToBallFrame;

		pos = pos*(1.0f - t) + m_CounterPos*t;

		if (is_end == true)
		{
			HitBall();
		}
	}

	// �^�C�}�[�X�V
	m_Timer.MoveToBall++;
}


// �J�E���^�[�ł��邩�ǂ���
bool CharacterCounter::IsCanCounter()
{
	if (m_pCounterBall &&
		BallBase::isCanCounter(m_pCounterBall) == true)
	{// �J�E���^�[�ł���{�[�����ǂ���

		if (m_pCounterBallParent &&
			m_pCounterBallParent != m_pParent &&
			m_pCounterBallParent == m_pCounterBall->m_Params.pParent
			)
		{// �ł����̂���������Ȃ� ���� �ړ����ɂق��̐l�ɃJ�E���^�[����Ă��Ȃ�
			return true;
		}
	}

	return false;
}


// �{�[����ł��Ԃ�
void CharacterCounter::HitBall()
{
	// �Ƃ肠�����{�[���ł����l�̂Ƃ���֕Ԃ�
	Vector3 vec = m_pCounterBallParent->m_Params.pos - m_pParent->m_Params.pos;

	// �ړ����x�ݒ�
	vec.Normalize();
	vec *= m_pCounterBall->m_Params.move.Length();

	// �ړ������]��
	m_pCounterBall->m_Params.move = vec;

	// �ł����l�ύX
	m_pCounterBall->m_Params.pParent = m_pParent;

	// �ł��Ԃ��C�x���g
	m_pCounterEvent->HitBall(m_IsJust);

}


// �J�E���^�[�ł���{�[����T��
bool CharacterCounter::SerchCounterBall()
{
	bool result =  DefBallMgr.GetCounterBall(
		&m_pCounterBall,
		m_pParent->m_Params.pos,
		&m_CounterPos,
		m_CounterParams.NormalCounterArea+5.0f,
		m_CounterParams.MoveToBallFrame
		);

	if (result == false)
	{
		// ������Ȃ�����
		m_pCounterBallParent = nullptr;
		m_pCounterBall = nullptr;
		m_CounterPos = m_pParent->m_Params.pos;
		return false;
	}

	m_pCounterBallParent = m_pCounterBall->m_Params.pParent;
	m_pCounterEvent->BallEnter();
	
	return true;
}


// �^�C�~���O����
void CharacterCounter::CalcHitTiming()
{
	Vector3 vec = m_pParent->m_Params.pos - m_pCounterBall->m_Params.pos;
	float length = vec.Length();

	float dot = Vector3Dot(m_pCounterBall->m_Params.move, vec);

	if (dot >= 0.0f)
	{
		if (length >= m_CounterParams.DamageReceiveArea && length <= m_CounterParams.NormalCounterArea)
		{
			if (length <= m_CounterParams.JustCounterArea)
			{
				m_IsJust = true;
			}
		}
	}
}

