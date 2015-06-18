#pragma once

//***************************************************
//		LacrossePlayer.h
//***************************************************

#include "../CharacterBase.h"
#include "../CharacterStateTemplate.h"
#include "../CharacterRenderer.h"


// �X�e�[�g�}�V���^���t��
class LacrossePlayer;
typedef ChrStateMachine<LacrossePlayer, CharacterBase::MsgType> LacrosseStateMachine;
typedef ChrState<LacrossePlayer, CharacterBase::MsgType> LacrosseState;


namespace lacrosse_player
{
	// ���[�V�����^�C�v
	enum MotionType
	{
		mt_Stand,
		mt_Run,

		mt_AttackClose_1,  // �ߋ����P�i��
		mt_AttackClose_2 = 15,  // �ߋ����Q�i��
		mt_AttackClose_3 = 16,  // �ߋ����R�i��


		mt_Evasion = 5,  // ���

		mt_AttackHitBall = 3, // �������U��

		mt_CounterPose = 13,  // �J�E���^�[�\��
	};


#if 0
	// �ł���s���̃^�C�v
	enum StateType
	{
		st_UsualMove,  // �ʏ�ړ�

		st_AttackClose_1, // �ߋ����P�i��
		st_AttackClose_2, // �ߋ����Q�i��
		st_AttackClose_3, // �ߋ����R�i��
	};
#endif

}


//***************************************************
//		���N���X�v���C���[
//***************************************************
class LacrossePlayer : public CharacterBase
{
private:
	LacrosseStateMachine* m_pStateMachine;  // �X�e�[�g�}�V��
public:
	bool                         m_HaveBall;   // �{�[���������Ă��邩�ǂ���
	CharacterRenderer	m_Renderer;  // �����_��

public:
	LacrossePlayer(const CharacterBase::PlayerInfo& info);
	~LacrossePlayer();
	
	// �X�e�[�g�ύX
	void SetState(LacrosseState* state);

	// �X�V
	bool Update()override;

	// �X�e�[�g�Ƀ��b�Z�[�W�𑗐M
	bool Msg(MsgType msg)override;

};
