#include "GameState.h"
#include "../character/CharacterManager.h"

#include<D3D10.h>
//*********************************************************
//	�Q�[����ԑJ�ڊǗ��N���X
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
//	�J�n�J�E���g�_�E���X�e�[�g�N���X
//*********************************************************

void GameStateStartCountdown::Enter(GameStateManager* ptr)
{
	m_Timer = 0;
}

void GameStateStartCountdown::Execute(GameStateManager* ptr)
{
	//�^�C���A�b�v�̏ꍇ�^�C���A�b�v�X�e�[�g��
	if (++m_Timer > 60)
	{
		ptr->SetNewState(new GameStatePlay());
	}
}


void GameStateStartCountdown::Exit(GameStateManager* ptr)
{

}

//*********************************************************
//	�Q�[���v���C�N���X
//*********************************************************

void GameStatePlay::Enter(GameStateManager* ptr)
{
	m_Timer = 0;
	m_MatchTime = 60 * 60;
}

void GameStatePlay::Execute(GameStateManager* ptr)
{
	//�J�E���g��i�߂�
	++m_Timer;

	//�L�����N�^�̐����l�����擾
	const UINT chr_live_count = DefCharacterMgr.GetCharacterLiveCount();


	//�L�����N�^�̐����l�����O�l�Ȃ���������X�e�[�g��
	if (chr_live_count == 0)
	{
		ptr->SetNewState(new GameStateDraw());
	}

	//�L�����N�^�̐����l�����P�l�Ȃ炻�̃L�����N�^�[�̏����X�e�[�g��
	if (chr_live_count == 1)
	{
		ptr->SetNewState(new GameStatePlayerWin());
	}

	//�^�C���A�b�v�̏ꍇ�^�C���A�b�v�X�e�[�g��
	if (m_Timer > m_MatchTime)
	{
		ptr->SetNewState(new GameStateTimeUp());
	}
}


void GameStatePlay::Exit(GameStateManager* ptr)
{

}

//*********************************************************
//	���������X�e�[�g�N���X
//*********************************************************

void GameStateDraw::Enter(GameStateManager* ptr)
{
	m_Timer = 0;
}

void GameStateDraw::Execute(GameStateManager* ptr)
{
	//�^�C���A�b�v�̏ꍇ�^�C���A�b�v�X�e�[�g��
	if (++m_Timer > 60)
	{
		ptr->SetNewState(new GameStateCharacterInitPos());
	}
}


void GameStateDraw::Exit(GameStateManager* ptr)
{

}

//*********************************************************
//	�ʏ폟���X�e�[�g�N���X
//*********************************************************

void GameStatePlayerWin::Enter(GameStateManager* ptr)
{
	m_Timer = 0;
}

void GameStatePlayerWin::Execute(GameStateManager* ptr)
{
	//�^�C���A�b�v�̏ꍇ�^�C���A�b�v�X�e�[�g��
	if (++m_Timer > 60)
	{
		ptr->SetNewState(new GameStateCharacterInitPos());
	}
}


void GameStatePlayerWin::Exit(GameStateManager* ptr)
{

}



//*********************************************************
//	�^�C���A�b�v�I���X�e�[�g
//*********************************************************

void GameStateTimeUp::Enter(GameStateManager* ptr)
{
	m_Timer = 0;
}

void GameStateTimeUp::Execute(GameStateManager* ptr)
{
	//�^�C���A�b�v�̏ꍇ�^�C���A�b�v�X�e�[�g��
	if (++m_Timer > 60)
	{
		ptr->SetNewState(new GameStateCharacterInitPos());
	}
}

void GameStateTimeUp::Exit(GameStateManager* ptr)
{
	
}


//*********************************************************
//	�L�����N�^�������ʒu�Ɉړ�������X�e�[�g
//*********************************************************

void GameStateCharacterInitPos::Enter(GameStateManager* ptr)
{
	m_Timer = 0;
}

void GameStateCharacterInitPos::Execute(GameStateManager* ptr)
{
	//�^�C���A�b�v�̏ꍇ�^�C���A�b�v�X�e�[�g��
	if (++m_Timer > 60)
	{
		ptr->SetNewState(new GameStateStartCountdown());
	}
}

void GameStateCharacterInitPos::Exit(GameStateManager* ptr)
{

}

