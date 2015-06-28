
#include "CharacterCounterClass.h"
#include "CharacterBase.h"
#include "CharacterFunction.h"

#include "CharacterMoveClass.h"

#include "../Ball/Ball.h"


//***************************************************
//		キャラクター共通 カウンタークラス
//***************************************************

// コンストラクタ
CharacterCounter::CharacterCounter(
	CharacterBase*                             pParent,                          // 動かしたいキャラクター
	const CounterParams&                  counterParams,               // カウンターパラメータ
	CounterEvent*                               pCounterEvent                // カウンターイベント
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


// デストラクタ
CharacterCounter::~CharacterCounter()
{
	delete m_pCounterEvent;
}


// 更新
void CharacterCounter::Update()
{
	// 移動更新
	UpdateUsualMove();

	// 更新
	m_pCounterEvent->Update();

	// 構え中
	if (m_Step & _cs_pose)
	{
		// カウンターできるボールを探す
		SerchCounterBall();

		UpdateLevelUp();
		UpdatePose();
	}

	// ボールに向かって移動中
	if (m_Step & _cs_move_to_ball)
	{
		UpdateMoveToBall();
	}

	// スイング中
	if (m_Step & _cs_swing)
	{
		UpdateSwing();
	}

}


// レベルアップの更新
void CharacterCounter::UpdateLevelUp()
{
	if (m_NowLevel < m_CounterParams.MaxCounterLevel)
	{
		if (m_Timer.LevelUp == m_CounterParams.LevelUpFrame)
		{
			m_Timer.LevelUp = 0;
			m_NowLevel++;
			m_Timer.Pose = 0;

			// レベルアップイベント
			m_pCounterEvent->LevelUp(m_NowLevel);
		}
	}

	// タイマー更新
	m_Timer.LevelUp++;
}


// 構え中の更新
void CharacterCounter::UpdatePose()
{
	// 構え終了?
	bool is_pose_end = false;

	if (m_Timer.Pose == 0)
	{
		if (m_NowLevel == 0)
		{
			// 構え開始イベント
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
		// 構え終了
		m_Step &= ~_cs_pose;
		m_Step |= _cs_move_to_ball;
		m_pCounterEvent->PoseEnd();
	}
	else
	{
		// タイマー更新
		m_Timer.Pose++;
	}

	
}


// 移動中の更新
void CharacterCounter::UpdateUsualMove()
{
	chr_func::XZMoveDown(m_pParent, m_CounterParams.MoveDownSpeed);

	chr_func::PositionUpdate(m_pParent);
}


// スイング中の更新
void CharacterCounter::UpdateSwing()
{
	if (m_Timer.Swing == 0)
	{
		// スイング開始
		m_pCounterEvent->SwingStart();
	}


	if (m_Timer.Swing == m_CounterParams.SwingTotalFrame)
	{
		// スイング終了
		m_pCounterEvent->SwingEnd();
	}

	// タイマー更新
	m_Timer.Swing++;
}


// ボールに向かって移動する
void CharacterCounter::UpdateMoveToBall()
{
	// ボールに向かって移動
	if (IsCanCounter() == true)
	{
		Vector3& pos = m_pParent->m_Params.pos;
		float t = 1.0f / m_CounterParams.MoveToBallFrame;

		pos = pos*(1.0f - t) + m_CounterPos*t;
	}

	if (m_Timer.MoveToBall == m_CounterParams.MoveToBallFrame)
	{
		// 移動終了
		m_Step &= ~_cs_move_to_ball;
		m_Step |= _cs_swing;

		// 打ち返す
		HitBall();
	}

	// タイマー更新
	m_Timer.MoveToBall++;
}


// カウンターできるかどうか
bool CharacterCounter::IsCanCounter()
{
	// if 文のネストが...
	bool is_ball_params_ok = false;
	m_IsJust = false;

	if (m_pCounterBall &&
		BallBase::isCanCounter(m_pCounterBall) == true)
	{// カウンターできるボールかどうか

		if (m_pCounterBallParent &&
			m_pCounterBallParent != m_pParent &&
			m_pCounterBallParent == m_pCounterBall->m_Params.pParent
			)
		{// 打ったのが自分じゃない かつ 移動中にほかの人にカウンターされていない
			is_ball_params_ok = true;
		}
	}

	if (is_ball_params_ok == true)
	{
		Vector3 vec = m_pParent->m_Params.pos - m_pCounterBall->m_Params.pos;
		float length = vec.Length();
		vec.Normalize();

		float dot = Vector3Dot(vec, m_pCounterBall->m_Params.move);

		if (dot > 0.0f)
		{
			if (length >= m_CounterParams.DamageReceiveArea)
			{
				// ジャストかどうか
				m_IsJust = length <= m_CounterParams.JustCounterArea;

				return true;
			}
		}
	}

	return false;
}

// ボールを打ち返す
void CharacterCounter::HitBall()
{
	if (IsCanCounter() == true)
	{
		// とりあえずボール打った人のところへ返す
		Vector3 vec = m_pCounterBallParent->m_Params.pos - m_pParent->m_Params.pos;

		// 移動速度設定
		vec.Normalize();
		vec *= m_pCounterBall->m_Params.move.Length();

		// 移動方向転換
		m_pCounterBall->m_Params.move = vec;

		// 打った人変更
		m_pCounterBall->m_Params.pParent = m_pParent;

		// 打ち返しイベント
		m_pCounterEvent->HitBall(m_IsJust);
	}
}


// カウンターできるボールを探す
bool CharacterCounter::SerchCounterBall()
{
	bool result =  DefBallMgr.GetCounterBall(
		&m_pCounterBall,
		m_pParent->m_Params.pos,
		&m_CounterPos,
		m_CounterParams.NormalCounterArea,
		m_CounterParams.MoveToBallFrame
		);

	if (result == false)
	{
		// 見つからなかった
		m_pCounterBallParent = nullptr;
		m_pCounterBall = nullptr;
		m_CounterPos = m_pParent->m_Params.pos;
		return false;
	}

	if (~m_Step & _cs_move_to_ball)
	{
		m_Step |= _cs_move_to_ball;
		m_pCounterBallParent = m_pCounterBall->m_Params.pParent;
		m_pCounterEvent->BallEnter();
	}
	
	return true;
}


