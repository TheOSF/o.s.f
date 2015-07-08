#include "CharacterBase.h"
#include "CharacterShotAttackClass.h"
#include "CharacterFunction.h"


//***************************************************
//		ラクロス用 遠距離攻撃 (ボール打ち出し) クラス
//***************************************************

// コンストラクタ
CharacterShotAttack::CharacterShotAttack(
	CharacterBase* pCharacter,
	Event* pEvent,
	const AttackParams& attack_params,
	HitEventBase*    pHitEventBase
	) :
	m_AttackParams(attack_params),
	m_StickValue(0, 0),
	m_pCharacter(pCharacter),
	m_Timer(0),
	m_pEvent(pEvent),
	m_pHitEventBase(pHitEventBase)
{

}


// デストラクタ
CharacterShotAttack::~CharacterShotAttack()
{
	delete m_pEvent;
	delete m_pHitEventBase;
}


// 更新
bool CharacterShotAttack::Update()
{
	if (m_Timer == 0)
	{// 攻撃開始
		m_pEvent->AttackStart();

		// 向き補正
		chr_func::AngleControll(
			m_pCharacter,
			m_pCharacter->m_Params.pos + Vector3(m_StickValue.x, 0, m_StickValue.y),
			m_AttackParams.MaxTurnRadian
			);
	}

	// 座標更新
	chr_func::PositionUpdate(m_pCharacter);

	// 減速
	chr_func::XZMoveDown(
		m_pCharacter,
		m_AttackParams.MoveDownSpeed);

	// 更新
	m_pEvent->Update();

	if (m_Timer == m_AttackParams.ShotFrame)
	{// ダメージ発生フレーム
		m_pEvent->Shot();
	}

	if (m_Timer >= m_AttackParams.AllFrame)
	{// 攻撃終了
		m_pEvent->AttackEnd();
		return false;
	}

	// タイマー更新
	m_Timer++;

	// ダメージ判定をとる
	chr_func::DamageCheck(m_pCharacter, m_pHitEventBase);

	return true;
}


// スティックの値セット
void CharacterShotAttack::SetStickValue(CrVector2 stickValue)
{
	m_StickValue = stickValue;
}

