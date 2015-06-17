#include "LacrossePlayer.h"
#include "LacrosseHitBallAttackClass.h"
#include "../CharacterFunction.h"


//***************************************************
//		ラクロス用 遠距離攻撃 (ボール打ち出し) クラス
//***************************************************

// コンストラクタ
LacrosseHitBallAttack::LacrosseHitBallAttack(
	LacrossePlayer* pLacrossePlayer,
	Event* pEvent,
	const AttackParams& attack_params
	) :
	m_AttackParams(attack_params),
	m_StickValue(0, 0),
	m_pLacrossePlayer(pLacrossePlayer),
	m_Timer(0),
	m_pEvent(pEvent)
{

}


// デストラクタ
LacrosseHitBallAttack::~LacrosseHitBallAttack()
{
	delete m_pEvent;
}


// 更新
bool LacrosseHitBallAttack::Update()
{
	if (m_Timer == 0)
	{// 攻撃開始
		m_pEvent->AttackStart();

		// 向き補正
		chr_func::AngleControll(
			m_pLacrossePlayer,
			m_pLacrossePlayer->m_Params.pos + Vector3(m_StickValue.x, 0, m_StickValue.y) ,
			m_AttackParams.MaxTurnRadian
			);
	}

	// 座標更新
	chr_func::PositionUpdate(m_pLacrossePlayer);

	// 減速
	chr_func::XZMoveDown(
		m_pLacrossePlayer,
		m_AttackParams.MoveDownSpeed);

	// 更新
	m_pEvent->Update();

	if (m_Timer == m_AttackParams.DamageOutbreakFrame)
	{// ダメージ発生フレーム
		m_pEvent->DamageStart();
	}

	if (m_Timer >= m_AttackParams.AllFrame)
	{// 攻撃終了
		m_pEvent->AttackEnd();
		return false;
	}

	// タイマー更新
	m_Timer++;

	return true;
}


// スティックの値セット
void LacrosseHitBallAttack::SetStickValue(CrVector2 stickValue)
{
	m_StickValue = stickValue;
}

