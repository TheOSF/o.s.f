
#include "CharacterCounterClass.h"
#include "CharacterBase.h"
#include "CharacterFunction.h"

//***************************************************
//		キャラクター共通 カウンタークラス
//***************************************************

// コンストラクタ
CharacterCounter::CharacterCounter(
	const CounterParams& counterParams,  // カウンターパラメータ
	CharacterBase*            pCharacter,         // 動かしたいキャラクター
	Event*                          pEvent                // カウンターイベント
	) :
	m_Timer(0),
	m_StickValue(0, 0),
	m_CounterParams(counterParams),
	m_pCharacter(pCharacter),
	m_pEvent(pEvent)
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
	if (m_Timer == 0)
	{// カウンター開始
		m_pEvent->CounterStart(m_CounterParams.Level);
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

	if (m_Timer >= m_CounterParams.TotalFrame)
	{// カウンター終了
		m_pEvent->CounterEnd();
		return false;
	}

	// タイマー更新
	m_Timer++;

	return true;
}


// スティックの値セット
void CharacterCounter::SetStickValue(CrVector2 stickValue)
{
	m_StickValue = stickValue;
}

