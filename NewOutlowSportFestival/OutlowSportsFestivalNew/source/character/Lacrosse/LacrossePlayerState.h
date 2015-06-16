#pragma once


//*************************************************************
//
//		���N���X�̑���N���X�w�b�_�[
//
//*************************************************************


#include "LacrossePlayer.h"
#include "../CharacterMoveClass.h"
#include "LacrosseAttackClose.h"

//***************************************************
//		�v���C���[����̈ړ��N���X
//***************************************************
class LacrosseState_PlayerControllMove : public LacrosseState
{
private:
	CharacterUsualMove* m_pMoveClass;  // �L�����N�^�[���ʂ̈ړ��N���X

	// �ړ����̃C�x���g�N���X�쐬
	CharacterUsualMove::MoveEvent* CreateMoveEvent(LacrossePlayer* t);

public:
	// �X�e�[�g�J�n
	void Enter(LacrossePlayer* t)override;

	// �X�e�[�g���s
	void Execute(LacrossePlayer* t)override;

	// �X�e�[�g�I��
	void Exit(LacrossePlayer* t)override;

};


//***************************************************
//		�v���C���[����̋ߋ����U���N���X
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
	static const int            kComboMax;        // �ő�R���{��
	const int                     m_ComboCount;  // �R���{��
	LacrosseAttackClose* m_pAttackClass;  // �ߐڍU���N���X
	bool                            m_DoCombo;      // �R���{���邩�ǂ���

	// �ߐڍU���N���X�쐬
	LacrosseAttackClose* CreateAttackClass(LacrossePlayer* t, lacrosse_player::MotionType motion);
};
