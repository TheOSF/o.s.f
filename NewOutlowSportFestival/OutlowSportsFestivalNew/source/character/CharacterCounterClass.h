#pragma once

#include "iextreme.h"

class CharacterBase;
//***************************************************
//		�L�����N�^�[���� �J�E���^�[�N���X
//***************************************************
class CharacterCounter
{
public:
	// �J�E���^�[�p�����[�^
	struct CounterParams
	{
		int TotalFrame;
		int Level;
		float MoveDownSpeed;
	};

	// �J�E���^�[�C�x���g�N���X
	class Event
	{
	public:
		virtual ~Event(){}
		virtual void Update() = 0;                       // �X�V
		virtual void CounterStart(int level) = 0;  // �J�E���^�[�J�n
		virtual void CounterEnd() = 0;                // �J�E���^�[�I��
	};

	// �R���X�g���N�^
	CharacterCounter(
		const CounterParams& counterParams,  // �J�E���^�[�p�����[�^
		CharacterBase*            pCharacter,         // �����������L�����N�^�[
		Event*                          pEvent                // �J�E���^�[�C�x���g
		);

	// �f�X�g���N�^
	~CharacterCounter();

	// �X�V
	bool Update();

	// �X�e�B�b�N�̒l�Z�b�g
	void SetStickValue(CrVector2 stickValue);

private:
	int                              m_Timer;                 // �^�C�}�[
	Vector2                      m_StickValue;          // �X�e�B�b�N�̓��͏��
	const CounterParams m_CounterParams; // �J�E���^�[�p�����[�^
	CharacterBase*          m_pCharacter;        // �����������L�����N�^�[
	Event*                        m_pEvent;              // �J�E���^�[�C�x���g


};
