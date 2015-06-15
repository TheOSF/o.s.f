#pragma once


//*************************************************************
//
//		���N���X�̑���N���X�w�b�_�[
//
//*************************************************************


#include "LacrossePlayer.h"
#include "../CharacterMoveClass.h"

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
