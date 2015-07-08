#ifndef __TENNIS_PLAYER_STATE_USUALMOVE_H__
#define __TENNIS_PLAYER_STATE_USUALMOVE_H__

#include "TennisPlayer.h"
#include "../../GameSystem/ForwardDecl.h"

//****************************************************
//	�e�j�X�v���C���[�̑���N���X�w�b�_�[
//****************************************************


//�v���C���[����̈ړ��N���X
class TennisState_PlayerControll_Move :public TennisState
{
private:
	CharacterUsualMove*		m_pMoveClass;
public:
	static TennisState* GetPlayerControllMove(TennisPlayer* pt);

	void Enter(TennisPlayer* t)override;
	void Execute(TennisPlayer* t)override;
	void Exit(TennisPlayer* t)override;
};


#endif