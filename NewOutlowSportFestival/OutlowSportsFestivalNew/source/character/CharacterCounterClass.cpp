
#include "CharacterCounterClass.h"
#include "CharacterBase.h"
#include "CharacterFunction.h"


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
	m_MaxLevel(maxLevel),
	m_NowLevel(0),
	m_Timer(0),
	m_TotalPoseFrame(0),
	m_PoseFlg(true),
	m_StickValue(0, 0),
	m_CounterParams(counterParams),
	m_pCharacter(pCharacter),
	m_pEvent(pEvent)
{
	m_TotalPoseFrame = (m_MaxLevel*m_CounterParams.LevelUpFrame) + m_CounterParams.MaxPoseFrame;
}


// デストラクタ
CharacterCounter::~CharacterCounter()
{
	delete m_pEvent;
}


// 更新
bool CharacterCounter::Update()
{
	if (m_PoseFlg)
	{
		if (m_Timer == 0)
		{// 構え開始
			m_pEvent->CounterPoseStart();
		}

		if (m_Timer == ((m_NowLevel + 1)*m_CounterParams.LevelUpFrame))
		{// レベルアップ
			if (m_NowLevel < m_MaxLevel)
			{
				m_NowLevel++;
				m_pEvent->LevelUp(m_NowLevel);
			}
		}

		if (m_Timer == m_TotalPoseFrame)
		{// 構え終了
			m_PoseFlg = false;
			m_Timer = 0;
			m_pEvent->CounterPoseEnd();
		}
	}
	else
	{
		if (m_Timer == 0)
		{// カウンター開始
			m_pEvent->CounterStart(m_NowLevel);
		}

		if (m_Timer == m_CounterParams.CounterTotalFrame)
		{// カウンター終了
			m_pEvent->CounterEnd();
		}
	}

	// 座標更新
	chr_func::PositionUpdate(m_pCharacter);

	// 減速
	chr_func::XZMoveDown(
		m_pCharacter,
		m_CounterParams.MoveDownSpeed
		);

	// 更新
	m_pEvent->Update();

	// タイマー更新
	m_Timer++;

	return true;
}


// level が最大レベルかどうか
bool CharacterCounter::IsMaxLevel(int level)const
{
	return (level >= m_MaxLevel);
}


// 現在最大レベルかどうか
bool CharacterCounter::IsMaxLevel()const
{
	return (m_NowLevel >= m_MaxLevel);
}


// 溜めフラグセット
void CharacterCounter::SetPoseEndFlg()
{
	if (m_PoseFlg == true)
	{
		m_PoseFlg = false;
		m_Timer = 0;
	}
}