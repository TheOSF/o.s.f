#include "CharacterAttack.h"
#include "CharacterFunction.h"
#include "CharacterBase.h"


//****************************************************************
//		�L�����N�^���ʂ̓����N���X
//****************************************************************

CharacterAttack_A::CharacterAttack_A(
	CharacterBase*	pParent,
	const Params&	param,
	MoveEvent*		pMoveEvent) :
	m_StickValue(0, 0),
	m_pParent(pParent),
	m_isRun(false),
	m_pMoveEvent(pMoveEvent)
{
	m_Params = param;
}

void CharacterAttack_A::Update()
{
	bool now = true;

	m_pMoveEvent->Update(now, (m_Params.MaxSpeed > 0.0f) ? (Vector3XZLength(m_pParent->m_Params.move) / m_Params.MaxSpeed) : (0));

	if (now)
	{
		chr_func::AddMoveFront(m_pParent, m_Params.Acceleration, m_Params.MaxSpeed);
		chr_func::AngleControll(
			m_pParent,
			m_pParent->m_Params.pos + Vector3(m_StickValue.x, 0, m_StickValue.y),
			m_Params.TurnSpeed
			);
	}
	else
	{
		chr_func::XZMoveDown(m_pParent, m_Params.DownSpeed);
	}

	if (now != m_isRun)
	{
		m_isRun = now;
		if (now)
		{
			m_pMoveEvent->RunStart();
		}
		else
		{
			m_pMoveEvent->StandStart();
		}
	}

	chr_func::PositionUpdate(m_pParent);
}

void CharacterAttack_A::SetStickValue(CrVector2 StickValue)
{
	m_StickValue = StickValue;
}
CharacterAttack_B::CharacterAttack_B(CharacterBase*	pParent,
	const Params&	param,
	MoveEvent*		pMoveEvent):
	m_StickValue(0, 0),
	m_pParent(pParent),
	m_isRun(false),
	m_pMoveEvent(pMoveEvent)
{
	m_Params = param;
}

void CharacterAttack_B::Update()
{
	bool now = true;

	m_pMoveEvent->Update(now, (m_Params.MaxSpeed > 0.0f) ? (Vector3XZLength(m_pParent->m_Params.move) / m_Params.MaxSpeed) : (0));

	if (now)
	{
		chr_func::AddMoveFront(m_pParent, m_Params.Acceleration, m_Params.MaxSpeed);
		chr_func::AngleControll(
			m_pParent,
			m_pParent->m_Params.pos + Vector3(m_StickValue.x, 0, m_StickValue.y),
			m_Params.TurnSpeed
			);
	}
	else
	{
		chr_func::XZMoveDown(m_pParent, m_Params.DownSpeed);
	}

	if (now != m_isRun)
	{
		m_isRun = now;
		if (now)
		{
			m_pMoveEvent->RunStart();
		}
		else
		{
			m_pMoveEvent->StandStart();
		}
	}

	chr_func::PositionUpdate(m_pParent);
}

void CharacterAttack_B::SetStickValue(CrVector2 StickValue)
{
	m_StickValue = StickValue;
}