#ifndef __TENNIS_PLAYER_H__
#define __TENNIS_PLAYER_H__

#include "CharacterBase.h"
#include "CharacterRenderer.h"
#include "CharacterStateTemplate.h"	

class TennisPlayer;

//�X�e�[�g�}�V���^���t��

typedef ChrStateMachine<TennisPlayer, CharacterBase::MsgType> TennisStateMachine;
typedef ChrState<TennisPlayer, CharacterBase::MsgType>TennisState;

//*************************************************************
//		�e�j�X�v���C���[�N���X
//*************************************************************

class TennisPlayer:public CharacterBase
{
public:
	enum MotionType
	{
		_mt_Stand,
		_mt_Run,
	};

	TennisPlayer(const CharacterBase::PlayerInfo& info);
	~TennisPlayer();

	CharacterRenderer	m_Renderer;

	void SetState(TennisState* state);
	bool Update();
	bool Msg(MsgType mt);

private:
	TennisStateMachine*		m_pStateMachine;
};




#endif