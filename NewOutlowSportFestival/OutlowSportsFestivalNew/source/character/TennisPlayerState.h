#ifndef __TENNIS_PLAYER_STATE_H__
#define __TENNIS_PLAYER_STATE_H__

#include "TennisPlayer.h"
#include "CharacterMoveClass.h"


//****************************************************
//	�e�j�X�v���C���[�̑���N���X�w�b�_�[
//****************************************************

//�v���C���[����̈ړ��N���X
class TennisState_PlayerControll_Move :public TennisState
{
private:
	CharacterUsualMove*		m_pMoveClass;
public:
	void Enter(TennisPlayer* t);
	void Execute(TennisPlayer* t);
	void Exit(TennisPlayer* t);
};

#endif