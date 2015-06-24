
#include "CharacterCounterClass.h"
#include "CharacterBase.h"
#include "CharacterFunction.h"

#include "../Ball/Ball.h"


//***************************************************
//		キャラクター共通 カウンタークラス
//***************************************************

// コンストラクタ
CharacterCounter::CharacterCounter(
	const int                       maxLevel,           // 最大レベル
	const CounterParams& counterParams, // カウンターパラメータ
	CharacterBase*            pCharacter,        // 動かしたいキャラクター
	Event*                          pEvent               // カウンターイベント
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


// デストラクタ
CharacterCounter::~CharacterCounter()
{
	delete m_pEvent;
}


// 更新
bool CharacterCounter::Update()
{
	// 通常移動更新
	UsualMoveUpdate();

	// 更新
	m_pEvent->Update();

	if (m_Step & cs_pose)
	{// 構え中

		// カウンターできるボールを探す
		this->SerchCounterBall();

		UpdatePose();
	}


	if (m_Step & cs_move_to_ball)
	{// 移動中
		UpdateMove();
	}


	if (m_Step & cs_swing)
	{// スイング中
		UpdateSwing();
	}

	return true;
}


// レベルアップの更新
void CharacterCounter::UpdateLevelUp()
{
	if ((m_NowLevel < m_MaxLevel) &&
		(m_Step & (cs_pose | cs_move_to_ball)))
	{
		if (m_LevelUpTimer == m_CounterParams.LevelUpFrame)
		{// レベルアップ
			m_LevelUpTimer = 0;
			m_NowLevel++;
			m_pEvent->LevelUp(m_NowLevel);
		}
	}
}


// 構え中の更新
void CharacterCounter::UpdatePose()
{
	if (m_PoseTimer == 0)
	{// 構え開始
		m_pEvent->PoseStart();
	}

	if (((m_NowLevel == m_MaxLevel) && m_PoseTimer == m_CounterParams.MaxPoseFrame) ||
		(m_ButtonState == controller::button::bs_up))
	{// 構え終了
		m_Step &= ~cs_pose;
		m_pEvent->PoseEnd();
	}

	if (m_ButtonState == controller::button::bs_up)
	{// 構え終了
		m_Step &= ~cs_pose;
		m_pEvent->PoseEnd();

		// ボタンが離されたらスイング
		m_Step |= cs_swing;
	}

	// タイマー更新
	m_PoseTimer++;
}


// 移動中の更新
void CharacterCounter::UpdateMove()
{
	if (m_MoveTimer == m_CounterParams.CounterMoveFrame)
	{// 移動終了
		m_Step &= ~cs_move_to_ball;

		// ボールを打つ
		this->HitBall();

		return;
	}

	// 移動
	MoveToBall();

	// タイマー更新
	m_MoveTimer++;
}


// スイング中の更新
void CharacterCounter::UpdateSwing()
{
	if (m_SwingTimer == 0)
	{// スイング開始

		m_pEvent->SwingStart();
	}


	if (m_SwingTimer == m_CounterParams.SwingTotalFrame)
	{// スイング終了

		m_pEvent->SwingEnd();
	}

	// タイマー更新
	m_SwingTimer++;
}


// 通常の移動更新
void CharacterCounter::UsualMoveUpdate()
{
	// 減速
	chr_func::XZMoveDown(m_pCharacter, m_CounterParams.MoveDownSpeed);

	// 座標更新
	chr_func::PositionUpdate(m_pCharacter);

}


// ボールに向かって動く
void CharacterCounter::MoveToBall()
{
	if (m_pCounterBall)
	{
		float t = 1.0f / m_CounterParams.CounterMoveFrame;

		Vector3 &pos = m_pCharacter->m_Params.pos;

		pos = pos * (1.0f - t) + m_CounterPos*t;
	}
}


// ボールを打ち返す
void CharacterCounter::HitBall()
{
	if (m_pCounterBall &&
		BallBase::isCanCounter(m_pCounterBall) == true)
	{// カウンターできるボールかどうか

		if (m_pCounterBallOwner &&
			m_pCounterBallOwner != m_pCharacter &&
			m_pCounterBallOwner == m_pCounterBall->m_Params.pParent
			)
		{// 打ったのが自分じゃない かつ 移動中にほかの人にカウンターされていない

			// とりあえずボール打った人のところへ返す
			Vector3 vec = m_pCounterBallOwner->m_Params.pos - m_pCharacter->m_Params.pos;

			// 移動速度設定
			vec.Normalize();
			vec *= m_pCounterBall->m_Params.move.Length();

			// 移動方向転換
			m_pCounterBall->m_Params.move = vec;

			// 打った人変更
			m_pCounterBall->m_Params.pParent = m_pCharacter;

			// 打ち返しイベント
			m_pEvent->HitBall(false);
		}
	}
}


// カウンターできるボールを探す
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


