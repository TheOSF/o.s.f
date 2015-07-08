#include "TennisPlayer.h"
#include "../../Damage/Damage.h"


//*************************************************************
//		テニスプレイヤークラス
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
	//新しいステートをセット
	m_pStateMachine->set_state(state);
}


bool TennisPlayer::Update()
{
	//ステート実行
	m_pStateMachine->state_execute();

	return true;	//常にtrueを返すと消去されない
}

bool TennisPlayer::Msg(MsgType mt)
{
	return m_pStateMachine->Msg(mt);
}


