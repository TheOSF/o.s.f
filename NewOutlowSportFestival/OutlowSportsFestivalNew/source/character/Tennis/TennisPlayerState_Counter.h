#ifndef __TENNIS_PLAYER_STATE_COUNTER_H__
#define __TENNIS_PLAYER_STATE_COUNTER_H__

#include "TennisPlayer.h"
#include "../../GameSystem/ForwardDecl.h"

//***************************************************
//		プレイヤー操作の カウンタークラス
//***************************************************
class TennisState_PlayerControll_Counter : public TennisState
{
public:
	// ステート開始
	void Enter(TennisPlayer* t)override;

	// ステート実行
	void Execute(TennisPlayer* t)override;

	// ステート終了
	void Exit(TennisPlayer* t)override;

private:
	// カウンタークラス作成
	CharacterCounter* CreateCounterClass(TennisPlayer* t);

	CharacterCounter* m_pCounter; // カウンタークラス
};

#endif