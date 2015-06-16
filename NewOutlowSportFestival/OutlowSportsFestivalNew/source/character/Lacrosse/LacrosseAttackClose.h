#pragma once

#include "iextreme.h"


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
	// �U���C�x���g�N���X
	class Event
	{
	public:
		virtual~Event(){}
		virtual void Update() = 0;
		virtual void AttackStart() = 0;
		virtual void AttackEnd() = 0;
	};


	// �R���X�g���N�^
	LacrosseAttackClose(
		LacrossePlayer* pLacrossePlayer,
		Event* pEvent
		);

	// �f�X�g���N�^
	~LacrosseAttackClose();

	// �X�V
	void Update();

	// �X�e�B�b�N�̒l�Z�b�g
	void SetStickValue(CrVector2 StickValue);


private:
	Vector2              m_StickValue;             // �X�e�B�b�N���͏��
	LacrossePlayer* m_pLacrossePlayer;   // ���N���X�v���C���[
	int                      m_Timer;                   // �^�C�}�[
	Event*                m_pEvent;                 // �U���C�x���g�N���X
};


