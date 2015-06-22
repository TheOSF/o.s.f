#ifndef __BASEBALL_PLAYER_H__
#define __BASEBALL_PLAYER_H__

#include "../CharacterBase.h"
#include "../CharacterRenderer.h"
#include "../CharacterStateTemplate.h"	

class BaseballPlayer;

//�X�e�[�g�}�V���^���t��
typedef ChrStateMachine< BaseballPlayer, CharacterBase::MsgType> BaseballStateMachine;
typedef ChrState< BaseballPlayer, CharacterBase::MsgType>BaseballState;

//*************************************************************
//		�싅�v���C���[�N���X
//*************************************************************

namespace baseball_player{
	enum MotionType{
		_mt_Stand,
		_mt_Run,

		_mt_CounterPose,
		_mt_Counter,
		_mt_Evasion = 5,  // ���
	};
}

class BaseballPlayer :public CharacterBase
{
public:


	BaseballPlayer(const CharacterBase::PlayerInfo& info);
	~BaseballPlayer();

	CharacterRenderer	m_Renderer;

	void SetState(BaseballState* state);
	bool Update();
	bool Msg(MsgType mt);

private:
	BaseballStateMachine*		m_pStateMachine;

};
#endif