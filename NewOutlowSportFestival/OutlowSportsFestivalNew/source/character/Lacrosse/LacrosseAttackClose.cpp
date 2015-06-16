#include "LacrossePlayer.h"
#include "LacrosseAttackClose.h"
#include "../CharacterFunction.h"

namespace lacrosse_player
{
	// とりあえず定数
	static const int AttackCloseStartFrame = 0;
	static const int AttackCloseEndFrame = 60;
}

//***************************************************
//		ラクロス用近距離攻撃クラス
//***************************************************

// コンストラクタ
LacrosseAttackClose::LacrosseAttackClose(
	LacrossePlayer* pLacrossePlayer,
	Event* pEvent
	) :
	m_StickValue(0, 0),
	m_pLacrossePlayer(pLacrossePlayer),
	m_Timer(0),
	m_pEvent(pEvent)
{

}


// デストラクタ
LacrosseAttackClose::~LacrosseAttackClose()
{

}


// 更新
void LacrosseAttackClose::Update()
{
	// 動かないように
	chr_func::SetMaxXZspeed(m_pLacrossePlayer, 0.0f);

	if (m_Timer == lacrosse_player::AttackCloseStartFrame)
	{
		m_pEvent->AttackStart();
	}

	if (m_Timer == lacrosse_player::AttackCloseEndFrame)
	{
		m_pEvent->AttackEnd();
	}

	m_pEvent->Update();

	// タイマー更新
	m_Timer++;

}


// スティックの値セット
void LacrosseAttackClose::SetStickValue(CrVector2 StickValue)
{
	m_StickValue = StickValue;
}

