#pragma once

#include "iextreme.h"

class CharacterBase;

//***************************************************
//		�L�����N�^�[���� �������U�� (�{�[���ł��o��) �N���X
//***************************************************
class CharacterHitBallAttack
{
public:
	// �U���p�����[�^
	struct AttackParams
	{
		int AllFrame;                         // �S�t���[��
		int DamageOutbreakFrame; // �{�[�����_���[�W���蔭���t���[��
		float MaxTurnRadian;           // �����␳�̊p�x����
		float AttackPower;               // �U����
		float MoveDownSpeed;        // ��������
	};

	// �U���C�x���g�N���X
	class Event
	{
	public:
		virtual~Event(){}
		virtual void Update() = 0;           // �X�V
		virtual void DamageStart() = 0;  // �_���[�W����J�n & �{�[������
		virtual void AttackStart() = 0;     // �U���J�n
		virtual void AttackEnd() = 0;      // �U���I��
	};

	// �R���X�g���N�^
	CharacterHitBallAttack(
		CharacterBase* pCharacter,
		Event* pEvent,
		const AttackParams& attack_params
		);

	// �f�X�g���N�^
	~CharacterHitBallAttack();

	// �X�V
	bool Update();

	// �X�e�B�b�N�̒l�Z�b�g
	void SetStickValue(CrVector2 stickValue);

private:
	const AttackParams m_AttackParams;      // �U���p�����[�^
	Vector2                    m_StickValue;           // �X�e�B�b�N�̓��͏��
	CharacterBase*       m_pCharacter;          // �L�����N�^�[
	int                            m_Timer;                  // �^�C�}�[
	Event*                     m_pEvent;                // �U���C�x���g
};

