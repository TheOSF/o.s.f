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
		_mt_Shot,
		_mt_CounterPose,
		_mt_Counter,
		_mt_Evasion = 5,  // ���
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
	bool batterflg;//�@(true:�o�b�^�[,false:����)
	//�@�{�[��
	BallBase::Params param;
	//�@�^�[�Q�b�g��pos
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
	//�@�؂�ւ�
	void Change();
	//�@�������֐���
	BallBase::Params BaseballShot(BaseballPlayer* b, BallBase::Params p);
	//�@�������^�[�Q�b�g�I��
	BallBase::Params TargetDecision( BallBase::Params p, Vector3 t);
public:
	//�@�Q�b�^�[
	bool getBatterFlg(){ return batterflg; }
	BallBase::Params getBallParam(){ return param; }//�@�{�[����param
	Vector3 getTarget(){ return target; }//�@�^�[�Q�b�g
public:
	//�@�Z�b�^�[
	void setBallParams(BallBase::Params p){ param = p; }//�@�{�[����param
	void setBallTarget(Vector3 t){ target = t; }//�@�{�[����target

};
#endif