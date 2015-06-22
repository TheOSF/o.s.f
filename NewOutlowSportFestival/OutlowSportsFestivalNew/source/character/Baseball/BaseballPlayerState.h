#ifndef __BASEBALL_PLAYER_STATE_H__
#define __BASEBALL_PLAYER_STATE_H__

#include "BaseballPlayer.h"

#include "../CharacterMoveClass.h"

//****************************************************
//	�싅�v���C���[�̑���N���X�w�b�_�[
//****************************************************

//�v���C���[����̈ړ��N���X
class BaseballState_PlayerControll_Move :public BaseballState
{
private:
	CharacterUsualMove* m_pMoveClass;
public:
	//�@�X�e�[�g�J�n
	void Enter(BaseballPlayer* b)override;
	//�@�X�e�[�g���s
	void Execute(BaseballPlayer* b)override;
	//�@�X�e�[�g�I��
	void Exit(BaseballPlayer* b)override;
};


//�v���C���[����̉���N���X
class CharacterEvasion;
class BaseballState_PlayerControll_Evasion :public BaseballState
{

public:
	//�@�R���X�g���N�^
	BaseballState_PlayerControll_Evasion();
	//�@�X�e�[�g�J�n
	void Enter(BaseballPlayer* b)override;
	//�@�X�e�[�g���s
	void Execute(BaseballPlayer* b)override;
	//�@�X�e�[�g�I��
	void Exit(BaseballPlayer* b)override;

private:
	// ����N���X�쐬
	CharacterEvasion* CreateEvasionClass(BaseballPlayer* b);
private:
	// ����N���X
	CharacterEvasion* m_pEvasionClass;
};
#endif