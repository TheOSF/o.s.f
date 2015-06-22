#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "iextreme.h"
#include "../utillity/StateTemplate.h"

class Camera;
typedef StateMachine<Camera, void> CameraStateMachine;
typedef State<Camera, void> CameraState;

//***********************************************
//	�J�����N���X(�V���O���g��)
//***********************************************

class Camera
{
public:
	static Camera& GetInstance();
	static void Release();

	// ���t���[���̍X�V
	void Update();

	//��ʏ���
	void Clear(DWORD color = 0, bool clear_z = true);

	//�V���������N���X���Z�b�g
	void SetNewState(CameraState* pNewState);

	//�J�����̐U����^����
	void SetShock(Vector2 power, float frame);

	//���[���h���W���v���W�F�N�V������ԍ��W�ɕϊ�����
	bool WorldToProjection(Vector3* pOut, CrVector3 In);

	//�v���W�F�N�V������ԍ��W�����[���h���W�ɕϊ�����
	void ProjectionToWorld(Vector3* pOut, CrVector3 In);

	//�J�����̊e�����x�N�g���𓾂�
	CrVector3 GetRight()const;
	CrVector3 GetUp()const;
	CrVector3 GetForward()const;

	//�ʒu�ƌ������
	Vector3 m_Target;
	Vector3 m_Position;

private:
	Camera();
	Camera(const Camera&);
	~Camera();

	//�J�����s����X�V����
	void UpdateMatrix(Vector3 pos, Vector3 target);

	//�Ռ����X�V����
	void ShockUpdate(Vector3& ShockVector);

	static Camera*			m_pInstance;

	CameraStateMachine*		m_pStateMachine;
	iexView					m_IexView;
	Matrix					m_VP;
	Matrix					m_VP_inv;
	Vector3					m_Right, m_Up, m_Forward;
	
	struct
	{
		Vector2 power;
		float	time;
		float	max_time;
	}
	ShockParam;
};

#define DefCamera (Camera::GetInstance())

#endif