#ifndef __SOCCER_PLAYER_STATE_H__
#define __SOCCER_PLAYER_STATE_H__

#include "SoccerPlayer.h"
#include "../../Ball/UsualBall.h"
#include "../Template/CharacterMoveClass.h"
#include "../Template/CharacterSliding.h"
#include "../Template/CharacterAttack.h"


//****************************************************
//	サッカープレイヤーの操作クラスヘッダー
//****************************************************

//プレイヤー操作の移動クラス
class SoccerState_PlayerControll_Move :public SoccerState
{
private:
	CharacterUsualMove*		m_pMoveClass;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);
};
//プレイヤー操作の回避クラス
class SoccerState_PlayerControll_Sliding :public SoccerState
{
private:
	CharacterSliding*		m_pMoveClass;
	int timer = 0;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);
};
//プレイヤー操作の攻撃クラス
class SoccerState_PlayerControll_Attack :public SoccerState
{
private:
	CharacterAttack_A*		m_pMoveClass;
	int timer = 0;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);
};
class SoccerState_PlayerControll_AttackCombo :public SoccerState
{
private:
	CharacterAttack_A*		m_pMoveClass;
	int timer = 0;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);
};
class SoccerState_PlayerControll_AttackFinish :public SoccerState
{
private:
	CharacterAttack_A*		m_pMoveClass;
	int timer = 0;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);
};
class SoccerState_PlayerControll_Shot :public SoccerState
{
private:
	CharacterSliding*		m_pMoveClass;
	int timer = 0;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);
};

#endif