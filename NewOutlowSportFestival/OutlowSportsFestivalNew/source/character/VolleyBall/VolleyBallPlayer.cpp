#include "VolleyBallPlayer.h"


//*************************************************************
//		サッカープレイヤークラス
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
	//新しいステートをセット
	m_pStateMachine->set_state(state);
}


bool VolleyBallPlayer::Update()
{
	//ステート実行
	m_pStateMachine->state_execute();

	return true;	//常にtrueを返すと消去されない
}

bool VolleyBallPlayer::Msg(MsgType mt)
{
	return m_pStateMachine->Msg(mt);
}


