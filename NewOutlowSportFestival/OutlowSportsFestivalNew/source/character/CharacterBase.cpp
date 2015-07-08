#include "CharacterBase.h"
#include "CharacterManager.h"

//***************************************************
//		キャラクタクラス
//***************************************************

CharacterBase::CharacterBase(const PlayerInfo& info):
m_PlayerInfo(info)
{
	m_Params.pos = Vector3Zero;
	m_Params.move = Vector3Zero;
	m_Params.hitScale = 1.5f;
	m_Params.angle = 0;
	m_Params.HP = 100;
	m_Params.SP = 0;

	//マネージャに登録
	DefCharacterMgr.Add(this);
}

CharacterBase::~CharacterBase()
{
	//マネージャから削除
	DefCharacterMgr.Erace(this);
}