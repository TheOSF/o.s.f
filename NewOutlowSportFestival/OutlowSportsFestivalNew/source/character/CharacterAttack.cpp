#include "CharacterAttack.h"
#include "CharacterFunction.h"
#include "CharacterBase.h"


//****************************************************************
//		キャラクタ共通の攻撃クラス
//****************************************************************

CharacterNearAttack::CharacterNearAttack(
	CharacterBase*	pParent,
	const Params&	param,
	AttackEvent*		pMoveEvent) :
	m_StickValue(0, 0),
	m_pCharacter(pParent),
	m_timer(0),
	m_pAttackEvent(pMoveEvent)
{
	m_Params = param;
}
CharacterNearAttack::~CharacterNearAttack()
{
	delete m_pAttackEvent;
}
bool CharacterNearAttack::Update()
{
	if (m_timer == 0)
	{
		// 攻撃開始
		m_pAttackEvent->AttackStart();

		// 移動
		chr_func::AddMoveFront(
			m_pCharacter,
			m_Params.speed,
			m_Params.speed
			);

		// 移動方向補正
		chr_func::AddXZMove(
			m_pCharacter,
			m_StickValue.x,
			m_StickValue.y,
			m_Params.speed
			);
		// 向き補正
		chr_func::AngleControll(
			m_pCharacter,
			m_pCharacter->m_Params.pos + Vector3(m_StickValue.x, 0, m_StickValue.y),
			m_Params.TurnSpeed
			);
	}
	// 座標更新
	chr_func::PositionUpdate(m_pCharacter);

	// 減速
	chr_func::XZMoveDown(
		m_pCharacter,
		m_Params.speed);

	// 更新
	m_pAttackEvent->Update();

	if (m_timer == m_Params.AttackFrame)
	{// ダメージ発生フレーム
		m_pAttackEvent->Assault();
	}
	if (m_timer >= m_Params.EndFrame)
	{// 攻撃終了
		m_pAttackEvent->AttackEnd();
		return false;
	}
	// タイマー更新
	m_timer++;

	return true;
}
void CharacterNearAttack::SetStickValue(CrVector2 StickValue)
{
	m_StickValue = StickValue;
}
// コンボできるかどうか
bool CharacterNearAttack::CanDoCombo()const
{
	return (m_timer >= m_Params.CanDoComboFrame);
}
// コンボ実行できるかどうか
bool CharacterNearAttack::CanGoNextCombo()const
{
	return (m_timer >= m_Params.GoNextComboFrame);
}