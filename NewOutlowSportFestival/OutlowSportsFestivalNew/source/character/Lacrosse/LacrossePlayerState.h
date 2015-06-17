#pragma once


//*************************************************************
//
//		���N���X�̑���N���X�w�b�_�[
//
//*************************************************************


#include "LacrossePlayer.h"

class CharacterUsualMove;
//***************************************************
//		�v���C���[����� �ړ��N���X
//***************************************************
class LacrosseState_PlayerControllMove : public LacrosseState
{
public:

	// �X�e�[�g�J�n
	void Enter(LacrossePlayer* t)override;

	// �X�e�[�g���s
	void Execute(LacrossePlayer* t)override;

	// �X�e�[�g�I��
	void Exit(LacrossePlayer* t)override;

private:
	// �ړ����̃C�x���g�N���X�쐬
	CharacterUsualMove* CreateMoveClass(LacrossePlayer* t);

private:
	CharacterUsualMove* m_pMoveClass;  // �L�����N�^�[���ʂ̈ړ��N���X
};


class LacrosseAttackClose;
//***************************************************
//		�v���C���[����� �ߋ����U���N���X
//***************************************************
class LacrosseState_PlayerControllAttackClose : public LacrosseState
{
public:
	// �R���X�g���N�^
	LacrosseState_PlayerControllAttackClose(int combo);

	// �X�e�[�g�J�n
	void Enter(LacrossePlayer* t)override;

	// �X�e�[�g���s
	void Execute(LacrossePlayer* t)override;

	// �X�e�[�g�I��
	void Exit(LacrossePlayer* t)override;

private:
	// �ߐڍU���N���X�쐬
	LacrosseAttackClose* CreateAttackClass(LacrossePlayer* t, lacrosse_player::MotionType motion);

private:
	static const int            kComboMax;        // �ő�R���{��
	const int                     m_ComboCount;  // �R���{��
	LacrosseAttackClose* m_pAttackClass;  // �ߐڍU���N���X
	bool                            m_DoCombo;      // �R���{���邩�ǂ���
};


class LacrosseEvasion;
//***************************************************
//		�v���C���[����� ����N���X
//***************************************************
class LacrosseState_PlayerControllEvasion : public LacrosseState
{
public:
	// �R���X�g���N�^
	LacrosseState_PlayerControllEvasion();

	// �X�e�[�g�J�n
	void Enter(LacrossePlayer* t)override;

	// �X�e�[�g���s
	void Execute(LacrossePlayer* t)override;

	// �X�e�[�g�I��
	void Exit(LacrossePlayer* t)override;

private:
	// ����N���X�쐬
	LacrosseEvasion* CreateEvasionClass(LacrossePlayer* t);

private:
	LacrosseEvasion* m_pEvasionClass; // ����N���X
};


class LacrosseHitBallAttack;
//***************************************************
//		�v���C���[����� �������U�� (�{�[���ł��o��) �N���X
//***************************************************
class LacrosseState_PlayerControllHitBallAttack : public LacrosseState
{
public:
	// �R���X�g���N�^
	LacrosseState_PlayerControllHitBallAttack();

	// �X�e�[�g�J�n
	void Enter(LacrossePlayer* t)override;

	// �X�e�[�g���s
	void Execute(LacrossePlayer* t)override;

	// �X�e�[�g�I��
	void Exit(LacrossePlayer* t)override;

private:
	// ����N���X�쐬
	LacrosseHitBallAttack* CreateAttackClass(LacrossePlayer* t);

private:
	LacrosseHitBallAttack* m_pAttackClass; // ����N���X
};



class LacrosseCounterPose;
//***************************************************
//		�v���C���[����� �J�E���^�[�\���N���X
//***************************************************
class LacrosseState_PlayerControllCounterPose : public LacrosseState
{
public:
	// �R���X�g���N�^
	LacrosseState_PlayerControllCounterPose();

	// �X�e�[�g�J�n
	void Enter(LacrossePlayer* t)override;

	// �X�e�[�g���s
	void Execute(LacrossePlayer* t)override;

	// �X�e�[�g�I��
	void Exit(LacrossePlayer* t)override;

private:
	// �J�E���^�[�\���N���X�쐬
	LacrosseCounterPose* CreateCounterPoseClass(LacrossePlayer* t);

private:
	LacrosseCounterPose* m_pCounterPose; // �J�E���^�[�\���N���X
};


#if 0
class LacrosseHitCounter;
//***************************************************
//		�v���C���[����� �J�E���^�[�N���X
//     ���̃X�e�[�g���͈ړ��ł���
//***************************************************
class LacrosseState_PlayerControllCounter : public LacrosseState
{
public:
	// �R���X�g���N�^
	LacrosseState_PlayerControllCounter();

	// �X�e�[�g�J�n
	void Enter(LacrossePlayer* t)override;

	// �X�e�[�g���s
	void Execute(LacrossePlayer* t)override;

	// �X�e�[�g�I��
	void Exit(LacrossePlayer* t)override;

private:
	// �J�E���^�[�łN���X�쐬
	LacrosseHitCounter* CreateHitCounterClass(LacrossePlayer* t);

	// �ړ��N���X�쐬
	CharacterUsualMove* CreateMoveClass(LacrossePlayer* t);

private:
	LacrosseHitCounter*  m_pHitCounter; // �J�E���^�[�łN���X
	CharacterUsualMove* m_pMove;          // �ړ��N���X
	
};

#endif