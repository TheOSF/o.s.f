#ifndef __TENNIS_PLAYER_STATE_ATTACK_H__
#define __TENNIS_PLAYER_STATE_ATTACK_H__

#include "TennisPlayer.h"

//***************************************************
//		プレイヤー操作の カウンタークラス
//***************************************************
class TennisState_PlayerControll_Attack : public TennisState
{
public:
	// ステート開始
	void Enter(TennisPlayer* t)override;

	// ステート実行
	void Execute(TennisPlayer* t)override;

	// ステート終了
	void Exit(TennisPlayer* t)override;
};

#endif