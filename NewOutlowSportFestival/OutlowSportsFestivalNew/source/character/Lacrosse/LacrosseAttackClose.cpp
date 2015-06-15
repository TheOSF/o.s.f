
#include "LacrosseAttackClose.h"



//***************************************************
//		ラクロス用近距離攻撃クラス
//***************************************************

// コンストラクタ
LacrosseAttackClose::LacrosseAttackClose(
	LacrossePlayer* pLacrossePlayer,
	const Params& param,
	AttackEvent* pAttackEvent
	) :
	m_pAttackEvent(pAttackEvent),
	m_StickValue(0, 0),
	m_pLacrossePlayer(pLacrossePlayer),
	m_Timer(0),
	m_Params(param)
{

}


// デストラクタ
LacrosseAttackClose::~LacrosseAttackClose()
{
	delete m_pAttackEvent;
}


// 更新
void LacrosseAttackClose::Update()
{
	// タイマー更新
	m_Timer++;

	if (m_Timer == m_Params.DamageOutbreakFrame)
	{// ダメージ発生
		m_pAttackEvent->DamageStart();
	}

	if (m_Timer == m_Params.EndFrame)
	{// 攻撃終了
		m_pAttackEvent->AttackEnd();
	}

	// 更新
	m_pAttackEvent->Update();



}


// スティックの値セット
void LacrosseAttackClose::SetStickValue(CrVector2 StickValue)
{
	m_StickValue = StickValue;
}
