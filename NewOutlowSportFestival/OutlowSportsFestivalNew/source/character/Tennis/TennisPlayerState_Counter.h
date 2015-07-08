#ifndef __TENNIS_PLAYER_STATE_COUNTER_H__
#define __TENNIS_PLAYER_STATE_COUNTER_H__

#include "TennisPlayer.h"
#include "../../GameSystem/ForwardDecl.h"

//***************************************************
//		�v���C���[����� �J�E���^�[�N���X
//***************************************************
class TennisState_PlayerControll_Counter : public TennisState
{
public:
	// �X�e�[�g�J�n
	void Enter(TennisPlayer* t)override;

	// �X�e�[�g���s
	void Execute(TennisPlayer* t)override;

	// �X�e�[�g�I��
	void Exit(TennisPlayer* t)override;

private:
	// �J�E���^�[�N���X�쐬
	CharacterCounter* CreateCounterClass(TennisPlayer* t);

	CharacterCounter* m_pCounter; // �J�E���^�[�N���X
};

#endif