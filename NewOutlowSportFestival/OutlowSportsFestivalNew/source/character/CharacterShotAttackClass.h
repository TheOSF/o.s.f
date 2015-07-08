#pragma once

#include "iextreme.h"
#include "../Damage/Damage.h"

class CharacterBase;

//***************************************************
//		�L�����N�^�[���� �������U�� (�{�[���ł��o��) �N���X
//***************************************************
class CharacterShotAttack
{
public:
	// �U���p�����[�^
	struct AttackParams
	{
		int AllFrame;                 // �S�t���[��
		int ShotFrame;              // �{�[�����_���[�W���蔭���t���[��
		float MaxTurnRadian;    // �����␳�̊p�x����
		float AttackPower;        // �U����
		float MoveDownSpeed; // ��������
	};

	// �U���C�x���g�N���X
	class Event
	{
	public:
		virtual~Event(){}
		virtual void Update() = 0;           // �X�V
		virtual void Shot() = 0;               // �_���[�W����J�n & �{�[������
		virtual void AttackStart() = 0;     // �U���J�n
		virtual void AttackEnd() = 0;      // �U���I��
	};

	// �R���X�g���N�^
	CharacterShotAttack(
		CharacterBase* pCharacter,
		Event* pEvent,
		const AttackParams& attack_params,
		HitEventBase*    pHitEventBase
		);

	// �f�X�g���N�^
	~CharacterShotAttack();

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
	HitEventBase*    m_pHitEventBase;  //�_���[�W���󂯂����ɌĂяo�����C�x���g
};

