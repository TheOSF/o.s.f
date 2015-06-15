#include "LacrossePlayer.h"


//***************************************************
//		ラクロスプレイヤー
//***************************************************

//----------------------------------------------
//     コンストラクタ・デストラクタ
//----------------------------------------------

// コンストラクタ
LacrossePlayer::LacrossePlayer(const CharacterBase::PlayerInfo& info):
CharacterBase(info),
m_Renderer(new BlendAnimationMesh("DATA\\CHR\\Golfer\\Player_G.iem"))
{
	m_pStateMachine = new LacrosseStateMachine(this);
	m_Renderer.SetMotion(2);
}


// デストラクタ
LacrossePlayer::~LacrossePlayer()
{
	delete m_pStateMachine;
}


//----------------------------------------------
//     処理
//----------------------------------------------

// ステート変更
void LacrossePlayer::SetState(LacrosseState* state)
{
	// 新しいステートをセット
	m_pStateMachine->set_state(state);
}


// 更新
bool LacrossePlayer::Update()
{
	// ステートを実行
	m_pStateMachine->state_execute();

	return true;
}


// ステートにメッセージを送信
bool LacrossePlayer::Msg(MsgType msg)
{
	return m_pStateMachine->Msg(msg);
}

