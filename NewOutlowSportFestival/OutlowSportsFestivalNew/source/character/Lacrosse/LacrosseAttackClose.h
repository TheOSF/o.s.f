#pragma once

#include "iextreme.h"
#include <vector>


class LacrossePlayer;

// �_���[�W(��)
class DamageObject;
typedef DamageObject DamageObject;


//***************************************************
//		���N���X�p�ߋ����U���N���X
//***************************************************
class LacrosseAttackClose
{
public:
	struct Params
	{
		float AttackPower;   // �U����
		float StepPower;      // ���ݍ���

		int DamageOutbreakFrame; // �_���[�W�����t���[��(���[�V�����ł͂Ȃ�)
		int EndFrame;                      // �U���I���t���[��
	};

	// �U���C�x���g�N���X
	class AttackEvent
	{
	public:
		virtual~AttackEvent(){}
		virtual void Update() = 0;
		virtual void AttackStart() = 0;
		virtual void AttackEnd() = 0;
		virtual void DamageStart() = 0;
	};

	// �R���X�g���N�^
	LacrosseAttackClose(
		LacrossePlayer* pLacrossePlayer,
		const Params& param,
		AttackEvent* pAttackEvent
		);

	// �f�X�g���N�^
	~LacrosseAttackClose();

	// �X�V
	void Update();

	// �X�e�B�b�N�̒l�Z�b�g
	void SetStickValue(CrVector2 StickValue);

private:
	AttackEvent*     m_pAttackEvent;          // �U���C�x���g
	Vector2              m_StickValue;              // �X�e�B�b�N���͏��
	LacrossePlayer* m_pLacrossePlayer;    // ���N���X�v���C���[
	int                      m_Timer;                    // �^�C�}�[
	const Params     m_Params;                 // �p�����[�^
};
