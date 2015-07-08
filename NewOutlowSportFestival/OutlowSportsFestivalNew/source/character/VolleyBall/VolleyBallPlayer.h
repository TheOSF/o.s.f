#ifndef __VOLLEYBALL_PLAYER_H__
#define __VOLLEYBALL_PLAYER_H__

#include "../CharacterBase.h"
#include "../CharacterRenderer.h"
#include "../CharacterStateTemplate.h"	

class VolleyBallPlayer;

//ステートマシン型名付け

typedef ChrStateMachine<VolleyBallPlayer, CharacterBase::MsgType> VolleyBallStateMachine;
typedef ChrState<VolleyBallPlayer, CharacterBase::MsgType>VolleyBallState;

//*************************************************************
//		サッカープレイヤークラス
//*************************************************************

class VolleyBallPlayer :public CharacterBase
{
public:
	enum MotionType
	{
		_ms_Stand,
		_ms_Run,
		_ms_Atk1,
		_ms_Shot,
		_ms_Guard,
		_ms_Rolling,
		_ms_Damage,
		_ms_Blowing,
		_ms_Scrub,
		_ms_GetUp,
		_ms_Shot2,
		_ms_Win,
		_ms_Lose,
		_ms_Command,
		_ms_Atk2,
		_ms_Atk3,
		_ms_Counter,
		_ms_Crap
	};

	VolleyBallPlayer(const CharacterBase::PlayerInfo& info);
	~VolleyBallPlayer();

	CharacterRenderer	m_Renderer;

	void SetState(VolleyBallState* state);
	bool Update();
	bool Msg(MsgType mt);

private:
	VolleyBallStateMachine*		m_pStateMachine;
};


#endif