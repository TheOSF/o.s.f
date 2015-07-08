#ifndef __BASEBALL_PLAYER_STATE_H__
#define __BASEBALL_PLAYER_STATE_H__

#include "BaseballPlayer.h"

#include "../CharacterMoveClass.h"
#include "../CharacterShotAttackClass.h"
//****************************************************
//	�싅�v���C���[�̑���N���X�w�b�_�[
//****************************************************

//�v���C���[����̈ړ��N���X
class BaseballState_PlayerControll_Move :public BaseballState
{
private:
	CharacterUsualMove* m_pMoveClass;

private:
	bool batterflg;//�@(true:�o�b�^�[,false:����)

public:
	//�@�R���X�g���N�^
	BaseballState_PlayerControll_Move() :batterflg(true){}
	//�@�X�e�[�g�J�n
	void Enter(BaseballPlayer* b)override;
	//�@�X�e�[�g���s
	void Execute(BaseballPlayer* b)override;
	//�@�X�e�[�g�I��
	void Exit(BaseballPlayer* b)override;
public:

	//�@�o�b�^�[�����s
	void Batter(BaseballPlayer* b);
	//�@���莞���s
	void Pitcher(BaseballPlayer* b);
	//�@�Z�b�^�[
	void SetBatterFlg(BaseballPlayer* b){ batterflg = b->getBatterFlg(); }
};


//�v���C���[����̉���N���X
class CharacterEvasion;
class BaseballState_PlayerControll_Evasion :public BaseballState{
private:
	float roolspeed;//�@������̑���
private:
	// ����N���X�쐬
	CharacterEvasion* CreateEvasionClass(BaseballPlayer* b);
private:
	// ����N���X
	CharacterEvasion* m_pEvasionClass;
public:
	//�@�R���X�g���N�^
	BaseballState_PlayerControll_Evasion(float speed);
	//�@�X�e�[�g�J�n
	void Enter(BaseballPlayer* b)override;
	//�@�X�e�[�g���s
	void Execute(BaseballPlayer* b)override;
	//�@�X�e�[�g�I��
	void Exit(BaseballPlayer* b)override;

};

//�v���C���[����̉������N���X(�o�b�^�[)
class CharacterShotAttack;
class BaseballState_PlayerControll_ShotAttack_B :public BaseballState{
private:
	//�@�������N���X�쐬(�o�b�^�[)
	CharacterShotAttack* CreateShotAttackClass_B(BaseballPlayer* b);
private:
	//�@�������N���X
	CharacterShotAttack* m_pShotAttackClass_B;
public:
	//�@�R���X�g���N�^
	BaseballState_PlayerControll_ShotAttack_B();
	//�@�X�e�[�g�J�n
	void Enter(BaseballPlayer* b)override;
	//�@�X�e�[�g���s
	void Execute(BaseballPlayer* b)override;
	//�@�X�e�[�g�I��
	void Exit(BaseballPlayer* b)override;
};

//�v���C���[����̉������N���X(�s�b�`���[)
class CharacterShotAttack;
class BaseballState_PlayerControll_ShotAttack_P :public BaseballState{
private:
	//�@�������N���X�쐬(�s�b�`���[)
	CharacterShotAttack* CreateShotAttackClass_P(BaseballPlayer* b);
private:
	//�@�������N���X
	CharacterShotAttack* m_pShotAttackClass_P;
public:
	
	//�@�R���X�g���N�^
	BaseballState_PlayerControll_ShotAttack_P();
	//�@�X�e�[�g�J�n
	void Enter(BaseballPlayer* b)override;
	//�@�X�e�[�g���s
	void Execute(BaseballPlayer* b)override;
	//�@�X�e�[�g�I��
	void Exit(BaseballPlayer* b)override;
	
};

#endif