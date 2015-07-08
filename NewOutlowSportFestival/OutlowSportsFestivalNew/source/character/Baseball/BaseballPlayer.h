#ifndef __BASEBALL_PLAYER_H__
#define __BASEBALL_PLAYER_H__

<<<<<<< HEAD
#include "../Template/CharacterBase.h"
#include "../Template/CharacterRenderer.h"
#include "../Template/CharacterStateTemplate.h"	
=======
#include "../CharacterBase.h"
#include "../CharacterRenderer.h"
#include "../CharacterStateTemplate.h"	
#include "../../Ball/UsualBall.h"
>>>>>>> c4abe03b37255dbd8036da53888bca9bc4e32b7e

class BaseballPlayer;

//ステートマシン型名付け
typedef ChrStateMachine< BaseballPlayer, CharacterBase::MsgType> BaseballStateMachine;
typedef ChrState< BaseballPlayer, CharacterBase::MsgType>BaseballState;

//*************************************************************
//		野球プレイヤークラス
//*************************************************************

namespace baseball_player{
	enum MotionType{
		_mt_Stand,
		_mt_Run,
		_mt_Shot,
		_mt_CounterPose,
		_mt_Counter,
		_mt_Evasion = 5,  // 回避
	};

	enum PositionMode
	{
		_pm_Butter,
		_pm_Pitcher,
	};
}

class BaseballPlayer :public CharacterBase
{
protected:
	bool batterflg;//　(true:バッター,false:投手)
	//　ボール
	BallBase::Params param;
	//　ターゲットのpos
	Vector3 target;

private:
	BaseballStateMachine*		m_pStateMachine;
public:


	BaseballPlayer(const CharacterBase::PlayerInfo& info);
	~BaseballPlayer();

	CharacterRenderer	m_Renderer;


	void SetState(BaseballState* state);
	bool Update();
	bool Msg(MsgType mt);
public:
	//　切り替え
	void Change();
	//　遠距離関数化
	BallBase::Params BaseballShot(BaseballPlayer* b, BallBase::Params p);
	//　遠距離ターゲット選定
	BallBase::Params TargetDecision( BallBase::Params p, Vector3 t);
public:
	//　ゲッター
	bool getBatterFlg(){ return batterflg; }
	BallBase::Params getBallParam(){ return param; }//　ボールのparam
	Vector3 getTarget(){ return target; }//　ターゲット
public:
	//　セッター
	void setBallParams(BallBase::Params p){ param = p; }//　ボールのparam
	void setBallTarget(Vector3 t){ target = t; }//　ボールのtarget

};
#endif