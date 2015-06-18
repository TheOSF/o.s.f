#pragma once

#include "iextreme.h"
#include <vector>

class CharacterBase;
//***************************************************
//		�L�����N�^�[���� �J�E���^�[�\���N���X
//***************************************************
class CharacterCounterPose
{
public:
	// �J�E���^�[�\���p�����[�^
	struct CounterPoseParams
	{
		int MaxPoseFrame;       // �ő�^�������t���[��
		int LevelUpFrame;        // ���x���A�b�v����t���[��
		float MoveDownSpeed; // ��������
	};

	// �J�E���^�[�\���C�x���g
	class Event
	{
	public:
		virtual~Event(){}
		virtual void Update() = 0;              // �X�V
		virtual void PoseStart() = 0;          // �\���J�n
		virtual void PoseEnd() = 0;            // �\���I��
		virtual void LevelUp(int level) = 0; // ���x���A�b�v
	};

	// �R���X�g���N�^
	CharacterCounterPose(
		const int MaxLevel,
		const CounterPoseParams& counterPoseParams,
		CharacterBase* pCharacter,
		Event* pEvent
		);

	// �f�X�g���N�^
	~CharacterCounterPose();

	// �X�V
	bool Update();

	// �X�e�B�b�N�̒l�Z�b�g
	void SetStickValue(CrVector2 stickValue);

	// �ő僌�x�����ǂ���
	bool IsMaxLevel(int level)const;

private:
	const int                              m_MaxLevel;                  // ���x���A�b�v�p�����[�^
	int                                       m_Timer;                        // �^�C�}�[
	int                                       m_NowLevel;                  // ���݂̃��x��
	const CounterPoseParams  m_CounterPoseParams; // �J�E���^�[�\���p�����[�^
	Vector2                               m_StickValue;                 // �X�e�B�b�N�̓��͏��
	CharacterBase*                  m_pCharacter;                // �L�����N�^�[
	Event*                                m_pEvent;                      // �J�E���^�[�\���C�x���g
};

