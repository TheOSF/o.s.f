#pragma once

#include "iextreme.h"

class LacrossePlayer;


//***************************************************
//		���N���X�p �J�E���^�[�\���N���X
//***************************************************
class LacrosseCounterPose
{
public:
	// �J�E���^�[�\���p �p�����[�^
	struct CounterPoseParams
	{
		int AllFrame;                 // �S�t���[��
		float MoveDownSpeed; // ��������
	};

	// �J�E���^�[�\���C�x���g�N���X
	class Event
	{
	public:
		virtual ~Event(){}
		virtual void Update() = 0;      // �X�V
		virtual void PoseStart() = 0;  // �\���J�n
		virtual void PoseEnd() = 0;    // �\���I��
	};

	// �R���X�g���N�^
	LacrosseCounterPose(
		LacrossePlayer* pLacrossePlayer,
		Event* pEvent,
		const CounterPoseParams& pose_params
		);
	
	// �f�X�g���N�^
	~LacrosseCounterPose();

	// �X�V
	bool Update();

	// �X�e�B�b�N�̒l�Z�b�g
	void SetStickValue(CrVector2 stickValue);

private:
	const CounterPoseParams m_PoseParams;         // �\���p�����[�^
	Vector2                              m_StickValue;            // �X�e�B�b�N���͏��
	LacrossePlayer*                 m_pLacrossePlayer;  // ���N���X�v���C���[
	int                                      m_Timer;                   // �^�C�}�[
	Event*                               m_pEvent;                 // �\���C�x���g�N���X
};


