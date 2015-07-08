#include "BaseballPlayer.h"
#include "../../Damage/Damage.h"
#include "../../GameSystem/GameController.h"
#include "../../Ball/UsualBall.h"

#include "../CharacterFunction.h"
#include "../CharacterManager.h"

//*************************************************************
//		野球プレイヤークラス
//*************************************************************

//　コンストラクタ
BaseballPlayer::BaseballPlayer(const CharacterBase::PlayerInfo& info) :
CharacterBase(info), batterflg(true), target(0,0,0),
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

//　遠距離関数化
BallBase::Params BaseballPlayer::BaseballShot(BaseballPlayer* b, BallBase::Params p){
	//移動は前向き
	chr_func::GetFront(b, &p.move);
	//スピードは適当
	p.move *= 0.45f;
	//キャラの場所に(最終的に腕の位置に？)
	p.pos = b->m_Params.pos;
	//高さをキャラ共通ボール発射のYに
	p.pos.y = BallBase::UsualBallShotY;
	//親を自分に
	p.pParent = b;
	//通常タイプ
	p.type = BallBase::Type::_Usual;

	return p;
}

//　遠距離ターゲット選定
BallBase::Params BaseballPlayer::TargetDecision( BallBase::Params p, Vector3 t){

	//　map代入
	const CharacterManager::CharacterMap& chr_map = DefCharacterMgr.GetCharacterMap();

	//　距離関係
	Vector3 v(0, 0, 0);
	float len = 2000.0f;
	float templen = 0.0f;

	//　pos一時保存用
	Vector3 temppos(0, 0, 0);

	//キャラクタ座標を算出
	for (auto it = chr_map.begin(); it != chr_map.end(); ++it){
		//　死んでたらcontinue
		if (chr_func::isDie(it->first) || it->first->m_PlayerInfo.number == m_PlayerInfo.number){
			continue;
		}
		//　距離判断
		t = m_Params.pos - it->first->m_Params.pos;
		templen = t.LengthSq();
		//　一番近い距離・位置算出
		if (len > templen){
			len = templen;
			temppos = it->first->m_Params.pos;
		}
	}

	//　ホーミング計算
	t = temppos - param.pos;
	t.Normalize();
	v.x += t.x*0.4f;
	v.z += t.z*0.4f;
	p.pos.x += v.x;
	p.pos.z += v.z;
	p.move = v;
	//　param・targetを保存
	param = p;
	target = t;

	return p;
}