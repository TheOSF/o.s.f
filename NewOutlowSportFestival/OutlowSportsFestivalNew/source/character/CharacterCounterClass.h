#pragma once

#include "iextreme.h"

#include "../GameSystem/GameController.h"
#include "../Damage/Damage.h"

class CharacterBase;
class BallBase;


//****************************************************************
//		�L�����N�^���ʂ̃J�E���^�[�N���X
//****************************************************************
class CharacterCounter
{
public:
	// �s�����
	enum CounterStep
	{
		_cs_pose = 1 << 0,
		_cs_swing = 1 << 1,
		_cs_move_to_ball = 1 << 2,
	};

	// �p�����[�^
	struct CounterParams
	{
		int MaxCounterLevel;            // �J�E���^�[�̍ő僌�x��
		int MaxPoseFrame;               // �ő�^�������t���[��
		int LevelUpFrame;                 // ���x���A�b�v����t���[��
		int SwingTotalFrame;            // �J�E���^�[�U��n�߂Ă���I���܂ł̃t���[��
		int MoveToBallFrame;           // �{�[���Ɍ������Ĉړ�����t���[��
		float NormalCounterArea;    // �J�E���^�[�̂ł���͈�
		float JustCounterArea;         // �W���X�g�J�E���^�[�G���A
		float DamageReceiveArea;  // �{�[�������̋������߂��ƃ_���[�W�����D�悷��
		float MoveDownSpeed;        // ��������
	};

	// �C�x���g
	class CounterEvent
	{
	public:
		virtual~CounterEvent(){}
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
		CharacterBase*                             pParent,                          // �����������L�����N�^�[
		const CounterParams&                  counterParams,               // �J�E���^�[�p�����[�^
		CounterEvent*                               pCounterEvent                // �J�E���^�[�C�x���g
		);

	// �f�X�g���N�^
	~CharacterCounter();


	// �X�V
	void Update();

	// �X�e�B�b�N�̒l�Z�b�g
	inline void SetStickValue(CrVector2 stickValue){ m_StickValue = stickValue; }

	// �{�^���̒l�Z�b�g
	inline void SetButtonState(controller::button::button_state buttonState){ m_ButtonState = buttonState; }

private:
	// �ړ��X�V
	void UpdateUsualMove();

	// ���x���A�b�v�X�V
	void UpdateLevelUp();

	// �\���X�V
	void UpdatePose();

	// �X�C���O�X�V
	void UpdateSwing();

	// �{�[���Ɍ������Ĉړ�����
	void UpdateMoveToBall();
	

	// �J�E���^�[�ł��邩�ǂ���
	bool IsCanCounter();

	// �{�[����ł��Ԃ�
	void HitBall();

	// �J�E���^�[�ł���{�[����T��
	bool SerchCounterBall();

	// �^�C�~���O����
	void CalcHitTiming();

private:
	typedef controller::button::button_state button_state;

	// �p�����[�^
	const CounterParams m_CounterParams;
	Vector2                       m_StickValue;
	button_state               m_ButtonState;
	int                               m_NowLevel;
	int                               m_Step;
	bool                             m_IsJust;

	// �^�C�}�[
	struct Timer
	{
		int LevelUp;      // ���x���A�b�v
		int Swing;         // �X�C���O
		int Pose;           // �ő傽�ߎ���
		int MoveToBall; // �{�[���Ɍ������Ĉړ�����
	} m_Timer;

	// �f�[�^
	CharacterBase*           m_pParent;
	CounterEvent*             m_pCounterEvent;

	// �J�E���^�[�p
	BallBase*           m_pCounterBall;
	CharacterBase* m_pCounterBallParent;
	Vector3              m_CounterPos;
};



