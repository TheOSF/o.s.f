#include "LacrossePlayer.h"
#include "LacrosseEvasionClass.h"
#include "../CharacterFunction.h"


//***************************************************
//		ラクロス用回避クラス
//***************************************************


// コンストラクタ
LacrosseEvasion::LacrosseEvasion(
	LacrossePlayer* pLacrossePlayer,
	Event* pEvent,
	const EvasionParams& evasion_params
	) :
	m_EvasionParams(evasion_params),
	m_StickValue(0, 0),
	m_pLacrossePlayer(pLacrossePlayer),
	m_Timer(0),
	m_pEvent(pEvent)
{

}


// デストラクタ
LacrosseEvasion::~LacrosseEvasion()
{
	delete m_pEvent;
}


// 更新
bool LacrosseEvasion::Update()
{
	// 移動
	chr_func::AddMoveFront(
		m_pLacrossePlayer,
		m_EvasionParams.MoveSpeed,
		m_EvasionParams.MoveSpeed);

	if (m_Timer == 0)
	{// 回避開始
		m_pEvent->EvasionStart();

		// 移動方向補正
		chr_func::AddXZMove(
			m_pLacrossePlayer,
			m_StickValue.x,
			m_StickValue.y,
			m_EvasionParams.MoveSpeed);

		// 向き補正
		chr_func::AngleControll(
			m_pLacrossePlayer,
			m_pLacrossePlayer->m_Params.pos + m_pLacrossePlayer->m_Params.move,
			m_EvasionParams.MaxTurnRadian
			);
	}

	// 座標更新
	chr_func::PositionUpdate(m_pLacrossePlayer);

	// 減速
	chr_func::XZMoveDown(
		m_pLacrossePlayer,
		m_EvasionParams.MoveDownSpeed);

	// 更新
	m_pEvent->Update();

	if (m_Timer >= m_EvasionParams.AllFrame)
	{// 回避終了
		m_pEvent->EvasionEnd();
		return false;
	}

	// タイマー更新
	m_Timer++;
	
	return true;
}


// スティックの値セット
void LacrosseEvasion::SetStickValue(CrVector2 stickValue)
{
	m_StickValue = stickValue;
}


// ダメージを受けることができるかどうか
bool LacrosseEvasion::CanGetDamage()const
{
	return (
		m_Timer < m_EvasionParams.NoDamageStartFrame || 
		m_Timer >= m_EvasionParams.NoDamageEndFrame
		);
}
