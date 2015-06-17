#pragma once

#include "iextreme.h"

class LacrossePlayer;

//***************************************************
//		���N���X�p����N���X
//***************************************************
class LacrosseEvasion
{
public:
	// ���p�p�����[�^
	struct EvasionParams
	{
		int AllFrame;                          // �S�t���[��
		int NoDamageStartFrame;     // ���G�J�n�t���[��
		int NoDamageEndFrame;      // ���G�I���t���[��
		float MoveDownSpeed;          // ��������
		float MoveSpeed;                   // �ړ��X�s�[�h
		float MaxTurnRadian;             // �����␳�̊p�x����
	};

	// ����C�x���g�N���X
	class Event
	{
	public:
		virtual~Event(){}
		virtual void Update() = 0;                // �X�V
		virtual void EvasionStart() = 0;       // ����s���J�ns
		virtual void EvasionEnd() = 0;         // ����s���I��
	};

	// �R���X�g���N�^
	LacrosseEvasion(
		LacrossePlayer* pLacrossePlayer,
		Event* pEvent,
		const EvasionParams& evasion_params
		);

	// �f�X�g���N�^
	~LacrosseEvasion();

	// �X�V
	bool Update();

	// �X�e�B�b�N�̒l�Z�b�g
	void SetStickValue(CrVector2 stickValue);

	// �_���[�W���󂯂邱�Ƃ��ł��邩�ǂ���
	bool CanGetDamage()const;

private:
	const EvasionParams m_EvasionParams;   // ����p�����[�^
	Vector2                      m_StickValue;           // �X�e�B�b�N���͏��
	LacrossePlayer*         m_pLacrossePlayer; // ���N���X�v���C���[
	int                              m_Timer;                  // �^�C�}�[
	Event*                       m_pEvent;                // ����C�x���g


};
