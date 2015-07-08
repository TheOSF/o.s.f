#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include "../utillity/StateTemplate.h"
#include "GameObject.h"


class GameStateManager;

typedef State<GameStateManager, void> GameState, *LpGameState;

//*********************************************************
//	�Q�[����ԑJ�ڊǗ��N���X
//*********************************************************

class GameStateManager :public GameObjectBase
{
public:
	GameStateManager();
	~GameStateManager();

	//�V�����X�e�[�g���Z�b�g
	void SetNewState(LpGameState newState);

	bool Update();
	bool Msg(MsgType mt);

private:
	typedef StateMachine<GameStateManager, void> GameStateMachine;

	GameStateMachine* m_pGameStateMachine;
};


//*********************************************************
//	�J�n�J�E���g�_�E���X�e�[�g�N���X
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
//	�Q�[���v���C�N���X
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
//	���������X�e�[�g�N���X
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
//	�ʏ폟���X�e�[�g�N���X
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
//	�^�C���A�b�v�I���X�e�[�g
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
//	�L�����N�^�������ʒu�Ɉړ�������X�e�[�g
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