#ifndef __TENNIS_PLAYER_STATE_ATTACK_H__
#define __TENNIS_PLAYER_STATE_ATTACK_H__

#include "TennisPlayer.h"

//***************************************************
//		�v���C���[����� �J�E���^�[�N���X
//***************************************************
class TennisState_PlayerControll_Attack : public TennisState
{
public:
	// �X�e�[�g�J�n
	void Enter(TennisPlayer* t)override;

	// �X�e�[�g���s
	void Execute(TennisPlayer* t)override;

	// �X�e�[�g�I��
	void Exit(TennisPlayer* t)override;
};

#endif