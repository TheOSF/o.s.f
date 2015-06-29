#ifndef __SOCCER_PLAYER_STATE_H__
#define __SOCCER_PLAYER_STATE_H__

#include "SoccerPlayer.h"
#include "../../Ball/UsualBall.h"
#include "../CharacterMoveClass.h"
#include "SoccerSliding.h"
#include "SoccerDash.h"
#include "../CharacterAttack.h"
#include "../CharacterShotAttackClass.h"
#include "../CharacterCounterClass.h"


//****************************************************
//	�T�b�J�[�v���C���[�̑���N���X�w�b�_�[
//****************************************************

//�v���C���[����̈ړ��N���X
class SoccerState_PlayerControll_Move :public SoccerState
{
private:
	CharacterUsualMove*		m_pMoveClass;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);
};
//�v���C���[����̉���N���X
class SoccerState_PlayerControll_Sliding :public SoccerState
{
private:
	SoccerSliding*		m_pSlidingClass;
	int timer = 0;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);
};
//�v���C���[����̍U���N���X
class SoccerState_PlayerControll_Attack :public SoccerState
{
private:
	CharacterNearAttack*		m_pMoveClass;
	CharacterNearAttack::Params p;
	
	int timer;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);
};
class SoccerState_PlayerControll_AttackCombo :public SoccerState
{
private:
	CharacterNearAttack*		m_pMoveClass;
	CharacterNearAttack::Params p;
	int timer;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);
};
class SoccerState_PlayerControll_AttackFinish :public SoccerState
{
private:
	CharacterNearAttack*		m_pMoveClass;
	CharacterNearAttack::Params p;
	int timer;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);
};
//�v���C���[����̎ˌ��N���X
class SoccerState_PlayerControll_Shot :public SoccerState
{
private:
	CharacterShotAttack*		m_pShotClass;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);
};
//�v���C���[����̃J�E���^�[�N���X
class SoccerState_PlayerControll_Counter : public SoccerState
{
private:
	CharacterCounter* CreateCounterClass(SoccerPlayer* t);
	CharacterCounter*		m_pCounterClass;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);

};
//�v���C���[����̌ŗL�Z(�_�b�V��)�N���X
class SoccerState_PlayerControll_Dash : public SoccerState
{
private:
	SoccerDash*		m_pMoveClass;
public:
	void Enter(SoccerPlayer* s);
	void Execute(SoccerPlayer* s);
	void Exit(SoccerPlayer* s);
};

#endif