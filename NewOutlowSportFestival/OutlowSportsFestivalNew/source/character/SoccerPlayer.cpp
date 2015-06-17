#include "SoccerPlayer.h"


//*************************************************************
//		�T�b�J�[�v���C���[�N���X
//*************************************************************

SoccerPlayer::SoccerPlayer(const CharacterBase::PlayerInfo& info) :
CharacterBase(info),
m_Renderer(new BlendAnimationMesh("DATA\\CHR\\Soccer\\Player_S.iem"))
{
	m_pStateMachine = new SoccerStateMachine(this);
	m_Renderer.SetMotion(0);
}

SoccerPlayer::~SoccerPlayer()
{
	delete m_pStateMachine;
}

void SoccerPlayer::SetState(SoccerState* state)
{
	//�V�����X�e�[�g���Z�b�g
	m_pStateMachine->set_state(state);
}


bool SoccerPlayer::Update()
{
	//�X�e�[�g���s
	m_pStateMachine->state_execute();

	return true;	//���true��Ԃ��Ə�������Ȃ�
}

bool SoccerPlayer::Msg(MsgType mt)
{
	return m_pStateMachine->Msg(mt);
}


