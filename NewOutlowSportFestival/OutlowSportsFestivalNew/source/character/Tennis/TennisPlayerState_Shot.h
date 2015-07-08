#ifndef __TENNIS_PLAYER_STATE_H__
#define __TENNIS_PLAYER_STATE_H__

#include "TennisPlayer.h"
#include "../../GameSystem/ForwardDecl.h"

//****************************************************
//	テニス_プレイヤー操作の遠距離攻撃クラス
//****************************************************
class TennisState_PlayerControll_Shot :public TennisState
{
private:
	CharacterShotAttack*	m_pShotClass;
public:
	void Enter(TennisPlayer* t)override;
	void Execute(TennisPlayer* t)override;
	void Exit(TennisPlayer* t)override;
};


#endif