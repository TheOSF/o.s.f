#ifndef __TENNIS_PLAYER_STATE_H__
#define __TENNIS_PLAYER_STATE_H__

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
	void Enter(TennisPlayer* t)override;
	void Execute(TennisPlayer* t)override;
	void Exit(TennisPlayer* t)override;
};

class CharacterCounter;
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


//****************************************************
//	�e�j�X_�v���C���[����̉������U���N���X
//****************************************************
class TennisState_PlayerControll_Shot :public TennisState
{
private:
	CharacterShotAttack*	m_pShotClass;
public:
	void Enter(TennisPlayer* t)override;
	void Execute(TennisPlayer* t)override;
	void Exit(TennisPlayer* t)override;
};


#endif