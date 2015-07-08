#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include "../utillity/StateTemplate.h"
#include "GameObject.h"


class GameStateManager;

typedef State<GameStateManager, void> GameState, *LpGameState;

//*********************************************************
//	ゲーム状態遷移管理クラス
//*********************************************************

class GameStateManager :public GameObjectBase
{
public:
	GameStateManager();
	~GameStateManager();

	//新しいステートをセット
	void SetNewState(LpGameState newState);

	bool Update();
	bool Msg(MsgType mt);

private:
	typedef StateMachine<GameStateManager, void> GameStateMachine;

	GameStateMachine* m_pGameStateMachine;
};


//*********************************************************
//	開始カウントダウンステートクラス
//*********************************************************

class GameStateStartCountdown :public GameState
{
public:
	void Enter(GameStateManager* ptr);
	void Execute(GameStateManager* ptr);
	void Exit(GameStateManager* ptr);
private:
	UINT	m_Timer;
};


//*********************************************************
//	ゲームプレイクラス
//*********************************************************

class GameStatePlay :public GameState
{
public:
	void Enter(GameStateManager* ptr);
	void Execute(GameStateManager* ptr);
	void Exit(GameStateManager* ptr);
private:
	UINT	m_Timer;
	UINT	m_MatchTime;
};

//*********************************************************
//	引き分けステートクラス
//*********************************************************

class GameStateDraw :public GameState
{
public:
	void Enter(GameStateManager* ptr);
	void Execute(GameStateManager* ptr);
	void Exit(GameStateManager* ptr);
private:
	UINT	m_Timer;
};

//*********************************************************
//	通常勝利ステートクラス
//*********************************************************

class GameStatePlayerWin :public GameState
{
public:
	void Enter(GameStateManager* ptr);
	void Execute(GameStateManager* ptr);
	void Exit(GameStateManager* ptr);
private:
	UINT	m_Timer;
};

//*********************************************************
//	タイムアップ終了ステート
//*********************************************************

class GameStateTimeUp :public GameState
{
public:
	void Enter(GameStateManager* ptr);
	void Execute(GameStateManager* ptr);
	void Exit(GameStateManager* ptr);
private:
	UINT	m_Timer;
};

//*********************************************************
//	キャラクタを初期位置に移動させるステート
//*********************************************************

class GameStateCharacterInitPos :public GameState
{
public:
	void Enter(GameStateManager* ptr);
	void Execute(GameStateManager* ptr);
	void Exit(GameStateManager* ptr);
private:
	UINT	m_Timer;
};

#endif