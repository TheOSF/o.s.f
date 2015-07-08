#include "TennisPlayer.h"
#include "../../Damage/Damage.h"


//*************************************************************
//		�e�j�X�v���C���[�N���X
//*************************************************************

TennisPlayer::TennisPlayer(const CharacterBase::PlayerInfo& info) :
CharacterBase(info),
m_Renderer(new BlendAnimationMesh("DATA\\CHR\\Tennis_player\\Player_T.iem")),
m_ModelSize(0.05f)
{
	m_pStateMachine = new TennisStateMachine(this);
}

TennisPlayer::~TennisPlayer()
{
	delete m_pStateMachine;
}

void TennisPlayer::SetState(TennisState* state)
{
	//�V�����X�e�[�g���Z�b�g
	m_pStateMachine->set_state(state);
}


bool TennisPlayer::Update()
{
	//�X�e�[�g���s
	m_pStateMachine->state_execute();

	return true;	//���true��Ԃ��Ə�������Ȃ�
}

bool TennisPlayer::Msg(MsgType mt)
{
	return m_pStateMachine->Msg(mt);
}


