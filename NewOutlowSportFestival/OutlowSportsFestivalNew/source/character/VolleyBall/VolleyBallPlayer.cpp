#include "VolleyBallPlayer.h"


//*************************************************************
//		�T�b�J�[�v���C���[�N���X
//*************************************************************

VolleyBallPlayer::VolleyBallPlayer(const CharacterBase::PlayerInfo& info) :
CharacterBase(info),
m_Renderer(new BlendAnimationMesh("DATA\\CHR\\Soccer\\Player_S.iem"))
{
	m_pStateMachine = new VolleyBallStateMachine(this);
	m_Renderer.SetMotion(0);
}

VolleyBallPlayer::~VolleyBallPlayer()
{
	delete m_pStateMachine;
}

void VolleyBallPlayer::SetState(VolleyBallState* state)
{
	//�V�����X�e�[�g���Z�b�g
	m_pStateMachine->set_state(state);
}


bool VolleyBallPlayer::Update()
{
	//�X�e�[�g���s
	m_pStateMachine->state_execute();

	return true;	//���true��Ԃ��Ə�������Ȃ�
}

bool VolleyBallPlayer::Msg(MsgType mt)
{
	return m_pStateMachine->Msg(mt);
}


