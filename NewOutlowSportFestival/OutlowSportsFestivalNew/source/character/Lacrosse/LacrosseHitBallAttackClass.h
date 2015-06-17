#pragma once

#include "iextreme.h"

class LacrossePlayer;

//***************************************************
//		���N���X�p �������U�� (�{�[���ł��o��) �N���X
//***************************************************
class LacrosseHitBallAttack
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
		virtual void DamageStart() = 0;  // �_���[�W����J�n
		virtual void AttackStart() = 0;     // �U���J�n
		virtual void AttackEnd() = 0;      // �U���I��
	};

	// �R���X�g���N�^
	LacrosseHitBallAttack(
		LacrossePlayer* pLacrossePlayer, 
		Event* pEvent,
		const AttackParams& attack_params
		);

	// �f�X�g���N�^
	~LacrosseHitBallAttack();

	// �X�V
	bool Update();

	// �X�e�B�b�N�̒l�Z�b�g
	void SetStickValue(CrVector2 stickValue);

private:
	const AttackParams m_AttackParams;      // �U���p�����[�^
	Vector2                    m_StickValue;           // �X�e�B�b�N�̓��͏��
	LacrossePlayer*       m_pLacrossePlayer;  // ���N���X�v���C���[
	int                            m_Timer;                  // �^�C�}�[
	Event*                     m_pEvent;                // �U���C�x���g
};

