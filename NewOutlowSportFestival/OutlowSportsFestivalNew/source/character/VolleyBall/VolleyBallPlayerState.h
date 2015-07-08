#ifndef __VOLLEYBALL_PLAYER_STATE_H__
#define __VOLLEYBALL_PLAYER_STATE_H__

#include "VolleyBallPlayer.h"
#include "../../Ball/UsualBall.h"
#include "../CharacterMoveClass.h"
#include "../CharacterAttack.h"
#include "../CharacterEvasionClass.h"
#include "../CharacterShotAttackClass.h"
#include "../CharacterCounterClass.h"
//****************************************************
//	バレーボールプレイヤーの操作クラスヘッダー
//****************************************************
//プレイヤー操作の移動クラス
class VolleyBallState_PlayerControll_Move :public VolleyBallState
{
private:
	CharacterUsualMove*		m_pMoveClass;
public:
	void Enter(VolleyBallPlayer* v);
	void Execute(VolleyBallPlayer* v);
	void Exit(VolleyBallPlayer* v);
};
//プレイヤー操作の回避クラス
class VolleyBallState_PlayerControll_Avoid :public VolleyBallState
{
private:
	CharacterEvasion*		m_pAvoidClass;
	int timer = 0;
public:
	void Enter(VolleyBallPlayer* v);
	void Execute(VolleyBallPlayer* v);
	void Exit(VolleyBallPlayer* v);
};
//プレイヤー操作の攻撃クラス
class VolleyBallState_PlayerControll_Attack :public VolleyBallState
{
private:
	CharacterNearAttack*		m_pAttackClass;
	CharacterNearAttack::Params p;

	int timer;
public:
	void Enter(VolleyBallPlayer* v);
	void Execute(VolleyBallPlayer* v);
	void Exit(VolleyBallPlayer* v);
};
#endif