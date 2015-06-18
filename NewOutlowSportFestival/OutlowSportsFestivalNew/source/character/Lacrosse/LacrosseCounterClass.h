#pragma once

#include "iextreme.h"


class LacrossePlayer;

//***************************************************
//		���N���X�p �J�E���^�[�ł� �N���X
//***************************************************
class LacrosseCounter
{
public:
	// �J�E���^�[�p�����[�^
	struct CounterParams
	{
		int CounterFrame;                // �J�E���^�[�S�t���[��
		int DamageOutbreakFrame; // �_���[�W���蔭���t���[��(�{�[�����˃t���[��)
		float MaxTurnRadian;           // �����␳�̊p�x����
		float CounterAttackPower;   // �J�E���^�[�������̍U����
		float CounterSpeed;             // �J�E���^�[(�{�[��)�̃X�s�[�h
	};

	// �\���p�����[�^
	struct CounterPoseParams
	{
		int PoseFrame;              // �ő�^�������t���[��
		float MoveDownSpeed; // ��������
	};

	// ���x���A�b�v�p�����[�^
	struct LevelUpParams
	{
		int LevelUpFrame;  // ���x���A�b�v����t���[��
		float AddPower;     // �ǉ�����U����
		float AddSpeed;     // �ǉ�����(�{�[����)�X�s�[�h
	};

	class Event
	{
	public:
		virtual~Event(){}
		virtual void Update() = 0;           // �X�V
		virtual void PoseStart() = 0;       // �\���J�n
		virtual void PoseEnd() = 0;         // �\���I��
		virtual void CounterStart() = 0;  // �J�E���^�[�J�n
		virtual void CounterEnd() = 0;    // �J�E���^�[�I��
		virtual void LevelUp() = 0;          // ���x���A�b�v
		virtual void DamageStart() = 0;  // �_���[�W����
	};




};

