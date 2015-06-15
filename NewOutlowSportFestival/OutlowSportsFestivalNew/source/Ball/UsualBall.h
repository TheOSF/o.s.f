#ifndef __USUAL_BALL_H__
#define __USUAL_BALL_H__

#include "Ball.h"
#include "GameObject.h"
#include "ForwardDecl.h"

//*****************************************************
//		í èÌã ÉNÉâÉX
//*****************************************************

class UsualBall :public GameObjectBase
{
public:
	UsualBall();
	~UsualBall();

	bool Update();
	bool Msg(MsgType mt);
private:
	BallBase	m_BallBase;
};

#endif