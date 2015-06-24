#pragma once

#include "iextreme.h"

#include "../GameSystem/GameController.h"

class CharacterBase;
class BallBase;

//***************************************************
//		�L�����N�^�[���� �J�E���^�[�N���X
//***************************************************
class CharacterCounter
{
public:
	// ���݂Ƃ��Ă���s��
	enum CounterStep
	{
		cs_pose                = 1 << 0,
		cs_move_to_ball  = 1 << 1,
		cs_swing               = 1 << 2,
	};

	// �J�E���^�[�p�����[�^
	struct CounterParams
	{
		int MaxPoseFrame;          // �ő�^�������t���[��
		int LevelUpFrame;           // ���x���A�b�v����t���[��
		int SwingTotalFrame;      // �J�E���^�[�U��n�߂Ă���I���܂ł̃t���[��
		int CounterMoveFrame;  // �J�E���^�[�̈ړ��ɂ�����t���[����
		float MoveDownSpeed;   // ��������
		float CanCounterArea;    // �J�E���^�[�̂ł���͈�
	};

	// �J�E���^�[�C�x���g�N���X
	class Event
	{
	public:
		virtual~Event(){}
		virtual void Update() = 0;                   // �X�V
		virtual void PoseStart() = 0;               // �\���J�n
		virtual void PoseEnd() = 0;                 // �\���I��
		virtual void BallEnter() = 0;                // �J�E���^�[�ł���{�[�������ꂽ
		virtual void LevelUp(int level) = 0;     // ���x���A�b�v
		virtual void SwingStart() = 0;             // �X�C���O�J�n
		virtual void SwingEnd() = 0;               // �X�C���O�I��
		virtual void HitBall(bool is_just) = 0;  // �ł��Ԃ����Ƃ�
	};

	// �R���X�g���N�^
	CharacterCounter(
		const int                        maxLevel,           // �ő僌�x��
		const CounterParams& counterParams,  // �J�E���^�[�p�����[�^
		CharacterBase*            pCharacter,        // �����������L�����N�^�[
		Event*                          pEvent                // �J�E���^�[�C�x���g
		);

	// �f�X�g���N�^
	~CharacterCounter();

	// �X�V
	bool Update();

	// �g�p����{�^���̏�Ԃ��Z�b�g
	inline void SetButtonState(controller::button::button_state state){ m_ButtonState = state; }

	// �X�e�B�b�N�̒l�Z�b�g
	inline void SetStickValue(CrVector2 stickValue){ m_StickValue = stickValue; }

private:
	// ���x���A�b�v�̍X�V
	void UpdateLevelUp();

	// �\�����̍X�V
	void UpdatePose();

	// �ړ����̍X�V
	void UpdateMove();

	// �X�C���O���̍X�V
	void UpdateSwing();

	// �ʏ�̈ړ��X�V
	void UsualMoveUpdate();

	// �{�[���Ɍ������ē���
	void MoveToBall();

	// �{�[����ł��Ԃ�
	void HitBall();

	// �J�E���^�[�ł���{�[����T��
	bool SerchCounterBall();

private:
	// �p�����[�^
	controller::button::button_state m_ButtonState;
	Vector2                                         m_StickValue;
	int                                                 m_NowLevel;
	WORD                                           m_Step;

	// �f�[�^
	const CounterParams  m_CounterParams;
	const int                       m_MaxLevel;
	CharacterBase*           m_pCharacter;
	Event*                         m_pEvent;

	// �^�C�}�[
	int m_LevelUpTimer;
	int m_MoveTimer;
	int m_PoseTimer;
	int m_SwingTimer;


	// �J�E���^�[�p
	CharacterBase* m_pCounterBallOwner;
	BallBase*           m_pCounterBall;
	Vector3              m_CounterPos;

};
