#ifndef __CAMERA_STATE_H__
#define __CAMERA_STATE_H__

#include "Camera.h"

//*********************************************************
//	�J�����̓����N���X�w�b�_
//*********************************************************

//�������̃J�����X�e�[�g
class CameraStateGamePlay :public CameraState
{
public:
	void Enter(Camera* c);
	void Execute(Camera* c);
	void Exit(Camera* c);

private:

};

#endif