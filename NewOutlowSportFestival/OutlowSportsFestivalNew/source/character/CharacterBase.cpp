#include "CharacterBase.h"

//***************************************************
//		キャラクタクラス
//***************************************************

CharacterBase::CharacterBase(const PlayerInfo& info):
m_PlayerInfo(info)
{
	m_Params.pos = Vector3Zero;
	m_Params.hitScale = 1;
	m_Params.angle = 0;
	m_Params.HP = 100;
	m_Params.SP = 0;
}