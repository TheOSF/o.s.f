#ifndef __BASEBALL_PLAYER_H__
#define __BASEBALL_PLAYER_H__

#include "../CharacterBase.h"
#include "../CharacterRenderer.h"
#include "../CharacterStateTemplate.h"	

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

		_mt_CounterPose,
		_mt_Counter,
		_mt_Evasion = 5,  // 回避
	};
}

class BaseballPlayer :public CharacterBase
{
protected:
	bool batterflg;//　(true:バッター,false:投手)
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
public:
	//　ゲッター
	bool getBatterFlg(){ return batterflg; }


};
#endif