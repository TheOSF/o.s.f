#ifndef __TENNIS_PLAYER_STATE_H__
#define __TENNIS_PLAYER_STATE_H__

#include "TennisPlayer.h"
#include "CharacterMoveClass.h"


//****************************************************
//	テニスプレイヤーの操作クラスヘッダー
//****************************************************

//プレイヤー操作の移動クラス
class TennisState_PlayerControll_Move :public TennisState
{
private:
	CharacterUsualMove*		m_pMoveClass;
public:
	void Enter(TennisPlayer* t);
	void Execute(TennisPlayer* t);
	void Exit(TennisPlayer* t);
};

#endif