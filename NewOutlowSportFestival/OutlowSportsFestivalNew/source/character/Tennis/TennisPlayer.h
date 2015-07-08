#ifndef __TENNIS_PLAYER_H__
#define __TENNIS_PLAYER_H__

#include "../Template/CharacterBase.h"
#include "../Template/CharacterRenderer.h"
#include "../Template/CharacterStateTemplate.h"	

class TennisPlayer;

//ステートマシン型名付け

typedef ChrStateMachine<TennisPlayer, CharacterBase::MsgType> TennisStateMachine;
typedef ChrState<TennisPlayer, CharacterBase::MsgType>TennisState;

//*************************************************************
//		テニスプレイヤークラス
//*************************************************************

class TennisPlayer:public CharacterBase
{
public:
	enum MotionType
	{
		_mt_Stand,
		_mt_Run,

		_mt_Attack1,
		_mt_Shot,
		_mt_Counter,
		_mt_Smash,
		_mt_Guard,
		_mt_Rolling,
		_mt_Damage_Weak = 20, 

		_mt_Damage_Vanish_Fly=9,
		_mt_Damage_Vanish_Down,
		_mt_Damage_Vanish_StandUp,

		_mt_WinPose = 13,
		_mt_LosePose,

		_mt_Attack2 = 16,
		_mt_Attack3 = 17,

		_mt_CounterPose = 18, 
		_mt_Hakushu=21,

	};

	TennisPlayer(const CharacterBase::PlayerInfo& info);
	~TennisPlayer();

	
	CharacterRenderer	m_Renderer;
	const float m_ModelSize;

	void SetState(TennisState* state);
	bool Update();
	bool Msg(MsgType mt);

private:
	TennisStateMachine*		m_pStateMachine;
};




#endif