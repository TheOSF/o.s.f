#include "Camera.h"


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

//マイフレームの更新
void Camera::Update()
{
	Vector3 shock_vec, temp_pos, temp_target;

	//ステートを実行
	m_pStateMachine->state_execute();

	//衝撃によるズレを取得
	ShockUpdate(shock_vec);

	//現在の座標に衝撃を足して行列を更新
	temp_pos = m_Position + shock_vec;
	temp_target = m_Target + shock_vec;

	UpdateMatrix(temp_pos, temp_target);

}

//画面消去
void Camera::Clear(DWORD color, bool clear_z)
{
	m_IexView.Clear(color, clear_z);
}

//新しい動きクラスをセット
void Camera::SetNewState(CameraState* pNewState)
{
	m_pStateMachine->set_state(pNewState);
}

//カメラの振動を与える
void Camera::SetShock(Vector2 power, float frame)
{
	ShockParam.power = power;
	ShockParam.time  = frame;
	ShockParam.max_time = frame;
}


//ワールド座標をプロジェクション空間座標に変換する
bool Camera::WorldToProjection(Vector3* pOut, CrVector3 In)
{
	*pOut = Vector3MulMatrix(In, m_VP);

	return true;
}

//プロジェクション空間座標をワールド座標に変換する
void Camera::ProjectionToWorld(Vector3* pOut, CrVector3 In)
{
	*pOut = Vector3MulMatrix(In, m_VP_inv);
}

Camera::Camera()
{
	m_pStateMachine = new CameraStateMachine(this);

	ShockParam.power = Vector2(0, 0);
	ShockParam.time = 0;
	ShockParam.max_time = 0;
}

Camera::~Camera()
{
	delete m_pStateMachine;
}

//カメラ行列を更新する
void Camera::UpdateMatrix(Vector3 pos, Vector3 target)
{
	m_IexView.Set(pos, target);
	m_IexView.Activate();

	m_VP = matView;
	m_VP *= matProjection;

	D3DXMatrixInverse(&m_VP_inv, 0, &m_VP);

	m_Right.x = matView._11;
	m_Right.y = matView._12;
	m_Right.z = matView._13;

	m_Up.x = matView._21;
	m_Up.y = matView._22;
	m_Up.z = matView._23;

	m_Forward.x = matView._31;
	m_Forward.y = matView._32;
	m_Forward.z = matView._33;


	m_Right.Normalize();
	m_Up.Normalize();
	m_Forward.Normalize();
}

//衝撃を更新する
void Camera::ShockUpdate(Vector3& ShockVector)
{
	//初期化
	ShockVector = Vector3Zero;

	//振動していない場合はreturn
	if (ShockParam.max_time <= 0 || 
		ShockParam.time <= 0)
	{
		return;
	}

	//時間が進むにつれて弱く
	const float t = ShockParam.time / ShockParam.max_time;

	//移動
	ShockVector += m_Right*ShockParam.power.x*t*fRand(-1, 1);
	ShockVector += m_Up*ShockParam.power.y*t*fRand(-1, 1);

	//時間経過
	--ShockParam.time;
}