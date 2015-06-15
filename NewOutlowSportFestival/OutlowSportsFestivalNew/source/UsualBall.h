#ifndef __USUAL_BALL_H__
#define __USUAL_BALL_H__

#include "Ball.h"
#include "GameObject.h"
#include "ForwardDecl.h"

//*****************************************************
//		�ʏ�ʃN���X
//*****************************************************

class UsualBall :public GameObjectBase
{
public:
	struct Params
	{
		Character*	pParent;	//���˂����L�����N�^�ւ̃|�C���^

	};
	UsualBall();
	~UsualBall();

	bool Update();
	bool Msg(MsgType mt);
private:
	BallBase	m_BallBase;
};

#endif