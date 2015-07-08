#include "GameState.h"
#include "../character/Template/CharacterManager.h"

#include<D3D10.h>
//*********************************************************
//	ゲーム状態遷移管理クラス
//*********************************************************

GameStateManager::GameStateManager()
{
	m_pGameStateMachine = new GameStateMachine(this);
}

GameStateManager::~GameStateManager()
{
	delete m_pGameStateMachine;
}

void GameStateManager::SetNewState(LpGameState newState)
{
	m_pGameStateMachine->set_state(newState);
}

bool GameStateManager::Update()
{
	m_pGameStateMachine->state_execute();

	return true;
}

bool GameStateManager::Msg(MsgType mt)
{
	return false;
}

//*********************************************************
//	開始カウントダウンステートクラス
//*********************************************************

void GameStateStartCountdown::Enter(GameStateManager* ptr)
{
	m_Timer = 0;
}

void GameStateStartCountdown::Execute(GameStateManager* ptr)
{
	//タイムアップの場合タイムアップステートへ
	if (++m_Timer > 60)
	{
		ptr->SetNewState(new GameStatePlay());
	}
}


void GameStateStartCountdown::Exit(GameStateManager* ptr)
{

}

//*********************************************************
//	ゲームプレイクラス
//*********************************************************

void GameStatePlay::Enter(GameStateManager* ptr)
{
	m_Timer = 0;
	m_MatchTime = 60 * 60;
}

void GameStatePlay::Execute(GameStateManager* ptr)
{
	//カウントを進める
	++m_Timer;

	//キャラクタの生存人数を取得
	const UINT chr_live_count = DefCharacterMgr.GetCharacterLiveCount();


	//キャラクタの生存人数が０人なら引き分けステートへ
	if (chr_live_count == 0)
	{
		ptr->SetNewState(new GameStateDraw());
	}

	//キャラクタの生存人数が１人ならそのキャラクターの勝ちステートへ
	if (chr_live_count == 1)
	{
		ptr->SetNewState(new GameStatePlayerWin());
	}

	//タイムアップの場合タイムアップステートへ
	if (m_Timer > m_MatchTime)
	{
		ptr->SetNewState(new GameStateTimeUp());
	}
}


void GameStatePlay::Exit(GameStateManager* ptr)
{

}

//*********************************************************
//	引き分けステートクラス
//*********************************************************

void GameStateDraw::Enter(GameStateManager* ptr)
{
	m_Timer = 0;
}

void GameStateDraw::Execute(GameStateManager* ptr)
{
	//タイムアップの場合タイムアップステートへ
	if (++m_Timer > 60)
	{
		ptr->SetNewState(new GameStateCharacterInitPos());
	}
}


void GameStateDraw::Exit(GameStateManager* ptr)
{

}

//*********************************************************
//	通常勝利ステートクラス
//*********************************************************

void GameStatePlayerWin::Enter(GameStateManager* ptr)
{
	m_Timer = 0;
}

void GameStatePlayerWin::Execute(GameStateManager* ptr)
{
	//タイムアップの場合タイムアップステートへ
	if (++m_Timer > 60)
	{
		ptr->SetNewState(new GameStateCharacterInitPos());
	}
}


void GameStatePlayerWin::Exit(GameStateManager* ptr)
{

}



//*********************************************************
//	タイムアップ終了ステート
//*********************************************************

void GameStateTimeUp::Enter(GameStateManager* ptr)
{
	m_Timer = 0;
}

void GameStateTimeUp::Execute(GameStateManager* ptr)
{
	//タイムアップの場合タイムアップステートへ
	if (++m_Timer > 60)
	{
		ptr->SetNewState(new GameStateCharacterInitPos());
	}
}

void GameStateTimeUp::Exit(GameStateManager* ptr)
{
	
}


//*********************************************************
//	キャラクタを初期位置に移動させるステート
//*********************************************************

void GameStateCharacterInitPos::Enter(GameStateManager* ptr)
{
	m_Timer = 0;
}

void GameStateCharacterInitPos::Execute(GameStateManager* ptr)
{
	//タイムアップの場合タイムアップステートへ
	if (++m_Timer > 60)
	{
		ptr->SetNewState(new GameStateStartCountdown());
	}
}

void GameStateCharacterInitPos::Exit(GameStateManager* ptr)
{

}

