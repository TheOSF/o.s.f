#ifndef __SOCCER_PLAYER_H__
#define __SOCCER_PLAYER_H__

#include "../CharacterBase.h"
#include "../CharacterRenderer.h"
#include "../CharacterStateTemplate.h"	

class SoccerPlayer;

//ステートマシン型名付け

typedef ChrStateMachine<SoccerPlayer, CharacterBase::MsgType> SoccerStateMachine;
typedef ChrState<SoccerPlayer, CharacterBase::MsgType>SoccerState;

//*************************************************************
//		サッカープレイヤークラス
//*************************************************************

class SoccerPlayer :public CharacterBase
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
		_ms_Shot2,
		_ms_Win,
		_ms_Lose,
		_ms_Counter,
		_ms_Dammy,
		_ms_Atk2,
		_ms_Atk3,
	};

	SoccerPlayer(const CharacterBase::PlayerInfo& info);
	~SoccerPlayer();

	CharacterRenderer	m_Renderer;

	void SetState(SoccerState* state);
	bool Update();
	bool Msg(MsgType mt);

private:
	SoccerStateMachine*		m_pStateMachine;
};


#endif