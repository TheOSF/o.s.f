#include "BaseballPlayer.h"
#include "../../Damage/Damage.h"
#include "../../GameSystem/GameController.h"


//*************************************************************
//		野球プレイヤークラス
//*************************************************************

//　コンストラクタ
BaseballPlayer::BaseballPlayer(const CharacterBase::PlayerInfo& info) :
CharacterBase(info), batterflg(true),
m_Renderer(new  BlendAnimationMesh("DATA\\CHR\\BaseBall\\player_B.iem"))
{
	m_pStateMachine = new BaseballStateMachine(this);
}

//　デストラクタ
BaseballPlayer::~BaseballPlayer(){
	delete m_pStateMachine;
}

//　ステートセット
void BaseballPlayer::SetState(BaseballState* state){
	//　新しいステートをセット
	m_pStateMachine->set_state(state);
}

//　更新
bool BaseballPlayer::Update(){
	//　切り替え
	Change();
	// ステート実行
	m_pStateMachine->state_execute();

	return true;	//常にtrueを返すと消去されない
}

bool  BaseballPlayer::Msg(MsgType mt){
	return m_pStateMachine->Msg(mt);
}

//　切り替え
void BaseballPlayer::Change(){
	if (controller::GetTRG(controller::button::_L1, m_PlayerInfo.number)){
		if (batterflg){
			batterflg = false;
		}
		else{
			batterflg = true;
		}
	}

}