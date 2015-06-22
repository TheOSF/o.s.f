#pragma once

#include "iextreme.h"

class CharacterBase;
class BallBase;

//***************************************************
//		�L�����N�^�[���� �J�E���^�[�N���X
//***************************************************
class CharacterCounter
{
public:
	// �J�E���^�[�p�����[�^
	struct CounterParams
	{
		int MaxPoseFrame;          // �ő�^�������t���[��
		int LevelUpFrame;           // ���x���A�b�v����t���[��
		int CounterTotalFrame;   // �J�E���^�[�U��n�߂Ă���I���܂ł̃t���[��
		int CounterMoveFrame;  // �J�E���^�[�̈ړ��ɂ�����t���[����
		float MoveDownSpeed;   // ��������
		float CanCounterArea;    // �J�E���^�[�̂ł���͈�
	};

	// �J�E���^�[�C�x���g�N���X
	class Event
	{
	public:
		virtual ~Event(){}
		virtual void Update() = 0;                       // �X�V
		virtual void CounterPoseStart() = 0;       // �\���X�^�[�g
		virtual void CounterPoseEnd() = 0;        // �\���I��
		virtual void LevelUp(int level) = 0;          // ���x���A�b�v
		virtual void CounterStart(int level) = 0;  // �J�E���^�[�J�n
		virtual void CounterEnd() = 0;                // �J�E���^�[�I��
	};

	// �R���X�g���N�^
	CharacterCounter(
		const int                       maxLevel,           // �ő僌�x��
		const CounterParams& counterParams, // �J�E���^�[�p�����[�^
		CharacterBase*            pCharacter,        // �����������L�����N�^�[
		Event*                          pEvent               // �J�E���^�[�C�x���g
		);

	// �f�X�g���N�^
	~CharacterCounter();

	// �X�V
	bool Update();

	// level ���ő僌�x�����ǂ���
	bool IsMaxLevel(int level)const;

	// ���ݍő僌�x�����ǂ���
	bool IsMaxLevel()const;

	// ���x���擾
	inline int GetLevel()const{ return m_NowLevel; }

	// ���߃t���O�Z�b�g
	void SetPoseEndFlg();

	// �X�e�B�b�N�̒l�Z�b�g
	inline void SetStickValue(CrVector2 stickValue){ m_StickValue = stickValue; }

private:
	const int                      m_MaxLevel;                   // ���x���A�b�v�p�����[�^
	int                               m_NowLevel;                   // ���݂̃��x��
	int                               m_Timer;                         // �^�C�}�[
	int                               m_TotalPoseFrame;         // ���߂��I���܂ł̑S�t���[��
	bool                            m_PoseFlg;                      // ���߃t���O
	Vector2                       m_StickValue;                 // �X�e�B�b�N�̓��͏��
	const CounterParams m_CounterParams;         // �J�E���^�[�p�����[�^
	CharacterBase*          m_pCharacter;               // �����������L�����N�^�[
	Event*                        m_pEvent;                      // �J�E���^�[�C�x���g
	BallBase*                   m_pCounterBall;             // �J�E���^�[����\��̃{�[��
	CharacterBase*         m_pCounterBallOwner;  // �J�E���^�[�������{�[����ł����l
	Vector3                      m_CounterPos;               // �J�E���^�[����ʒu

};
