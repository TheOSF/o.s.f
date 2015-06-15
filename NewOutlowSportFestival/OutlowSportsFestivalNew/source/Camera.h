#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "iextreme.h"


class CameraMoveBase; 

//***********************************************
//	カメラクラス(シングルトン)
//***********************************************

class Camera
{
public:
	static Camera& GetInstance();
	static void Release();

	void Update();
	void Clear();
	void SetNewState(CameraMoveBase* pNewState);
	void SetShock(Vector2 power, float frame);
private:
	static Camera* m_pInstance;
	
};

#define DefCamera (Camera::GetInstance())

#endif