#include "SoccerPlayer.h"


//*************************************************************
//		サッカープレイヤークラス
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
	//新しいステートをセット
	m_pStateMachine->set_state(state);
}


bool SoccerPlayer::Update()
{
	//ステート実行
	m_pStateMachine->state_execute();

	return true;	//常にtrueを返すと消去されない
}

bool SoccerPlayer::Msg(MsgType mt)
{
	return m_pStateMachine->Msg(mt);
}


