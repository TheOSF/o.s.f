#include "LacrossePlayer.h"
#include "LacrosseAttackClose.h"
#include "../CharacterFunction.h"


//***************************************************
//		ラクロス用近距離攻撃クラス
//***************************************************

// コンストラクタ
LacrosseAttackClose::LacrosseAttackClose(
	LacrossePlayer* pLacrossePlayer,
	Event* pEvent,
	const ComboParams& combo_params
	) :
	m_ComboParams(combo_params), 
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
bool LacrosseAttackClose::Update()
{
	if (m_Timer == 0)
	{// 攻撃開始
		m_pEvent->AttackStart();

		// 移動
		chr_func::AddMoveFront(
			m_pLacrossePlayer,
			m_ComboParams.MoveSpeed,
			m_ComboParams.MoveSpeed);

		// 移動方向補正
		chr_func::AddXZMove(
			m_pLacrossePlayer,
			m_StickValue.x,
			m_StickValue.y,
			m_ComboParams.MoveSpeed);

		// 向き補正
		chr_func::AngleControll(
			m_pLacrossePlayer,
			m_pLacrossePlayer->m_Params.pos + m_pLacrossePlayer->m_Params.move,
			m_ComboParams.MaxTurnRadian
			);
	}

	// 座標更新
	chr_func::PositionUpdate(m_pLacrossePlayer);

	// 減速
	chr_func::XZMoveDown(
		m_pLacrossePlayer,
		m_ComboParams.MoveDownSpeed);

	// 更新
	m_pEvent->Update();

	

	if (m_Timer == m_ComboParams.DamageOutbreakFrame)
	{// ダメージ発生フレーム
		m_pEvent->DamageStart();
	}

	if (m_Timer >= m_ComboParams.AllFrame)
	{// 攻撃終了
		m_pEvent->AttackEnd();
		return false;
	}

	// タイマー更新
	m_Timer++;

	return true;
}


// スティックの値セット
void LacrosseAttackClose::SetStickValue(CrVector2 stickValue)
{
	m_StickValue = stickValue;
}


// コンボできるかどうか
bool LacrosseAttackClose::CanDoCombo()const
{
	return (m_Timer >= m_ComboParams.CanDoComboFrame);
}


// コンボ実行できるかどうか
bool LacrosseAttackClose::CanGoNextCombo()const
{
	return (m_Timer >= m_ComboParams.GoNextComboFrame);
}

