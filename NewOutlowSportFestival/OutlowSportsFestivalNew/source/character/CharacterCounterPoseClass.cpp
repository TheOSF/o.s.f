#include "CharacterBase.h"
#include "CharacterCounterPoseClass.h"
#include "CharacterFunction.h"


//***************************************************
//		キャラクター共通 カウンター構えクラス
//***************************************************


// コンストラクタ
CharacterCounterPose::CharacterCounterPose(
	const int                               maxLevel,                  // 最大レベル
	const CounterPoseParams& counterPoseParams, // 構えパラメータ
	CharacterBase*                    pCharacter,               // 動かしたいキャラクター
	Event*                                  pEvent	                      // 構えイベント
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


// デストラクタ
CharacterCounterPose::~CharacterCounterPose()
{
	delete m_pEvent;
}


// 更新
bool CharacterCounterPose::Update()
{
	if (m_Timer == 0)
	{// 構え開始
		m_pEvent->PoseStart();
	}

	
	if (m_Timer == ((m_NowLevel + 1)* m_CounterPoseParams.LevelUpFrame))
	{// レベルアップ
		if (m_NowLevel < m_MaxLevel)
		{
			m_NowLevel++;
			m_pEvent->LevelUp(m_NowLevel);
		}
	}

	// 座標更新
	chr_func::PositionUpdate(m_pCharacter);

	// 減速
	chr_func::XZMoveDown(
		m_pCharacter,
		m_CounterPoseParams.MoveDownSpeed
		);

	// 更新
	m_pEvent->Update();

	if (m_Timer == m_TotalFrame)
	{// 構え終了
		m_pEvent->PoseEnd();
		return false;
	}

	// タイマー更新
	m_Timer++;

	return true;
}


// 最大レベルかどうか
bool CharacterCounterPose::IsMaxLevel(int level)const
{
	return (level >= m_MaxLevel);
}

bool CharacterCounterPose::IsMaxLevel()const
{
	return m_NowLevel >= m_MaxLevel;
}

