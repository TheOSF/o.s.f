#include "CharacterMoveClass.h"
#include "CharacterFunction.h"
#include "CharacterBase.h"


//****************************************************************
//		キャラクタ共通の動きクラス
//****************************************************************

CharacterUsualMove::CharacterUsualMove(
	CharacterBase* pParent,	
	const Params& param):
	m_StickValue(0,0),
	pParent(pParent)
{
	m_Params = param;
}

void CharacterUsualMove::Update()
{
	bool isRun = Vector2Length(m_StickValue) > 0.1f;

	if (isRun)
	{
	//	chr_func::PositionUpdate(pParent);
		chr_func::AddMoveFront(pParent, m_Params.Acceleration, m_Params.MaxSpeed);
		chr_func::AngleControll(
			pParent,
			pParent->m_Params.pos + Vector3(m_StickValue.x, 0, m_StickValue.y),
			m_Params.TurnSpeed
			);
	}
	else
	{
		chr_func::XZMoveDown(pParent, 0.05f);
	}
}

void CharacterUsualMove::SetStickValue(CrVector2 StickValue)
{
	m_StickValue = StickValue;
}