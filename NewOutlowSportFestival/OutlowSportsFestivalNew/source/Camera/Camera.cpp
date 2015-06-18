#include "Camera.h"
#include "CameraState.h"

Camera* Camera::m_pInstance = nullptr;

static float fRand(float fmin, float fmax)
{
	return ((float)rand() / RAND_MAX)*(fmax - fmin) + fmin;
}

Camera& Camera::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new Camera();
	}
	return *m_pInstance;
}

void Camera::Release()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

//�}�C�t���[���̍X�V
void Camera::Update()
{
	Vector3 shock_vec, temp_pos, temp_target;

	//�X�e�[�g�����s
	m_pStateMachine->state_execute();

	//�Ռ��ɂ��Y�����擾
	ShockUpdate(shock_vec);

	//���݂̍��W�ɏՌ��𑫂��čs����X�V
	temp_pos = m_Position + shock_vec;
	temp_target = m_Target + shock_vec;

	UpdateMatrix(temp_pos, temp_target);

}

//��ʏ���
void Camera::Clear(DWORD color, bool clear_z)
{
	m_IexView.Clear(color, clear_z);
}

//�V���������N���X���Z�b�g
void Camera::SetNewState(CameraState* pNewState)
{
	m_pStateMachine->set_state(pNewState);
}

//�J�����̐U����^����
void Camera::SetShock(Vector2 power, float frame)
{
	ShockParam.power = power;
	ShockParam.time  = frame;
	ShockParam.max_time = frame;
}


//���[���h���W���v���W�F�N�V������ԍ��W�ɕϊ�����
bool Camera::WorldToProjection(Vector3* pOut, CrVector3 In)
{
	*pOut = Vector3MulMatrix(In, m_VP);

	return true;
}

//�v���W�F�N�V������ԍ��W�����[���h���W�ɕϊ�����
void Camera::ProjectionToWorld(Vector3* pOut, CrVector3 In)
{
	*pOut = Vector3MulMatrix(In, m_VP_inv);
}

CrVector3 Camera::GetRight()const
{
	return m_Right;
}

CrVector3 Camera::GetUp()const
{
	return m_Up;
}

CrVector3 Camera::GetForward()const
{
	return m_Forward;
}

Camera::Camera()
{
	m_pStateMachine = new CameraStateMachine(this);
	m_pStateMachine->set_state(new CameraStateGamePlay());

	ShockParam.power = Vector2(0, 0);
	ShockParam.time = 0;
	ShockParam.max_time = 0;


}

Camera::~Camera()
{
	delete m_pStateMachine;
}

//�J�����s����X�V����
void Camera::UpdateMatrix(Vector3 pos, Vector3 target)
{
	m_IexView.Set(pos, target);
	m_IexView.Activate();

	m_VP = matView;
	m_VP *= matProjection;

	D3DXMatrixInverse(&m_VP_inv, 0, &m_VP);

	m_Right.x = matView._11;
	m_Right.y = matView._21;
	m_Right.z = matView._31;

	m_Up.x = matView._12;
	m_Up.y = matView._22;
	m_Up.z = matView._32;

	m_Forward.x = matView._13;
	m_Forward.y = matView._23;
	m_Forward.z = matView._33;


	m_Right.Normalize();
	m_Up.Normalize();
	m_Forward.Normalize();
}

//�Ռ����X�V����
void Camera::ShockUpdate(Vector3& ShockVector)
{
	//������
	ShockVector = Vector3Zero;

	//�U�����Ă��Ȃ��ꍇ��return
	if (ShockParam.max_time <= 0 || 
		ShockParam.time <= 0)
	{
		return;
	}

	//���Ԃ��i�ނɂ�Ďキ
	const float t = ShockParam.time / ShockParam.max_time;

	//�ړ�
	ShockVector += m_Right*ShockParam.power.x*t*fRand(-1, 1);
	ShockVector += m_Up*ShockParam.power.y*t*fRand(-1, 1);

	//���Ԍo��
	--ShockParam.time;
}