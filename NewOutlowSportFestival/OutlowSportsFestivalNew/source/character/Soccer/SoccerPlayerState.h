#ifndef __SOCCER_PLAYER_STATE_H__
#define __SOCCER_PLAYER_STATE_H__

#include "SoccerPlayer.h"
#include "../../Ball/UsualBall.h"
#include "../CharacterMoveClass.h"
#include "SoccerSliding.h"
#include "SoccerDash.h"
#include "../CharacterAttack.h"
#include "../CharacterShotAttackClass.h"
#include "../CharacterCounterClass.h"


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
	SoccerSliding*		m_pSlidingClass;
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
	CharacterNearAttack*		m_pMoveClass;
	CharacterNearAttack::Params p;
	
	int timer;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);
};
class SoccerState_PlayerControll_AttackCombo :public SoccerState
{
private:
	CharacterNearAttack*		m_pMoveClass;
	CharacterNearAttack::Params p;
	int timer;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);
};
class SoccerState_PlayerControll_AttackFinish :public SoccerState
{
private:
	CharacterNearAttack*		m_pMoveClass;
	CharacterNearAttack::Params p;
	int timer;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);
};
//プレイヤー操作の射撃クラス
class SoccerState_PlayerControll_Shot :public SoccerState
{
private:
	CharacterShotAttack*		m_pShotClass;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);
};
//プレイヤー操作のカウンタークラス
class SoccerState_PlayerControll_Counter : public SoccerState
{
private:
	CharacterCounter* CreateCounterClass(SoccerPlayer* t);
	CharacterCounter*		m_pCounterClass;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);

};
//プレイヤー操作の固有技(ダッシュ)クラス
class SoccerState_PlayerControll_Dash : public SoccerState
{
private:
	SoccerDash*		m_pMoveClass;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);
};

#endif