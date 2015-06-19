#ifndef __TENNIS_PLAYER_STATE_H__
#define __TENNIS_PLAYER_STATE_H__

#include "TennisPlayer.h"
#include "../CharacterMoveClass.h"


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

class CharacterCounterPose;
//***************************************************
//		�v���C���[����� �J�E���^�[�\���N���X
//***************************************************
class TennisState_PlayerControll_CounterPose : public TennisState
{
public:
	// �X�e�[�g�J�n
	void Enter(TennisPlayer* t)override;

	// �X�e�[�g���s
	void Execute(TennisPlayer* t)override;

	// �X�e�[�g�I��
	void Exit(TennisPlayer* t)override;

private:
	// �J�E���^�[�\���N���X�쐬
	CharacterCounterPose* CreateCounterPoseClass(TennisPlayer* t);

	CharacterCounterPose* m_pCounterPose; // �J�E���^�[�\���N���X
};


class CharacterCounter;
//***************************************************
//		�v���C���[����� �J�E���^�[�\���N���X
//***************************************************
class TennisState_PlayerControll_Counter : public TennisState
{
public:
	// �R���X�g���N�^
	TennisState_PlayerControll_Counter(int level);

	// �X�e�[�g�J�n
	void Enter(TennisPlayer* t)override;

	// �X�e�[�g���s
	void Execute(TennisPlayer* t)override;

	// �X�e�[�g�I��
	void Exit(TennisPlayer* t)override;

private:
	// �J�E���^�[�N���X�쐬
	CharacterCounter* CreateCounterClass(TennisPlayer* t, int level);

	int                           m_Level;        // �J�E���^�[���x��
	CharacterCounter*  m_pCounter; // �J�E���^�[�N���X
};

#endif