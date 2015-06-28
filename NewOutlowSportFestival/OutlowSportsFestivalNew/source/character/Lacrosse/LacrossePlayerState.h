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


class CharacterEvasion;
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
	CharacterEvasion* CreateEvasionClass(LacrossePlayer* t);

private:
	CharacterEvasion* m_pEvasionClass; // ����N���X
};


class CharacterShotAttack;
//***************************************************
//		�v���C���[����� �������U�� (�{�[���ł��o��) �N���X
//***************************************************
class LacrosseState_PlayerControllShotAttack : public LacrosseState
{
public:
	// �R���X�g���N�^
	LacrosseState_PlayerControllShotAttack();

	// �X�e�[�g�J�n
	void Enter(LacrossePlayer* t)override;

	// �X�e�[�g���s
	void Execute(LacrossePlayer* t)override;

	// �X�e�[�g�I��
	void Exit(LacrossePlayer* t)override;

private:
	// �U���N���X�쐬
	CharacterShotAttack* CreateAttackClass(LacrossePlayer* t);

private:
	CharacterShotAttack* m_pAttackClass; // �U���N���X
};




