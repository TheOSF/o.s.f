#pragma once

#include "iextreme.h"


class LacrossePlayer;


//***************************************************
//		���N���X�p �ߋ����U���N���X
//***************************************************
class LacrosseAttackClose
{
public:
	// �R���{�p�p�����[�^
	struct ComboParams
	{
		float MoveSpeed;                     // �ړ��X�s�[�h
		float MoveDownSpeed;            // ��������
		float MaxTurnRadian;               // �����␳�̊p�x����
		int    DamageOutbreakFrame;  // �_���[�W�����t���[��
		int    AllFrame;                         // �S�t���[��
		int    CanDoComboFrame;       // ���̃R���{���ł���t���[��
		int    GoNextComboFrame;      // �R���{�����s����t���[��
	};

	// �U���C�x���g�N���X
	class Event
	{
	public:
		virtual~Event(){}
		virtual void Update() = 0;          // �X�V
		virtual void DamageStart() = 0; // �_���[�W�J�n
		virtual void AttackStart() = 0;    // �U���J�n
		virtual void AttackEnd() = 0;      // �U���I��
	};

	// �R���X�g���N�^
	LacrosseAttackClose(
		LacrossePlayer* pLacrossePlayer,
		Event* pEvent,
		const ComboParams& combo_params
		);

	// �f�X�g���N�^
	~LacrosseAttackClose();

	// �X�V
	bool Update();

	// �X�e�B�b�N�̒l�Z�b�g
	void SetStickValue(CrVector2 stickValue);

	// �R���{�ł��邩�ǂ���
	bool CanDoCombo()const;

	// �R���{���s�ł��邩�ǂ���
	bool CanGoNextCombo()const;

private:
	const ComboParams m_ComboParams;       // �R���{�p�����[�^
	Vector2                     m_StickValue;              // �X�e�B�b�N���͏��
	LacrossePlayer*        m_pLacrossePlayer;    // ���N���X�v���C���[
	int                             m_Timer;                     // �^�C�}�[
	Event*                       m_pEvent;                  // �U���C�x���g�N���X
};


