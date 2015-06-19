#include "LacrossePlayer.h"
#include "LacrosseCounterPoseClass.h"
#include "../CharacterFunction.h"

//***************************************************
//		���N���X�p �J�E���^�[�\���N���X
//***************************************************

// �R���X�g���N�^
LacrosseCounterPose::LacrosseCounterPose(
	LacrossePlayer* pLacrossePlayer,
	Event* pEvent,
	const CounterPoseParams& pose_params
	):
	m_PoseParams(pose_params),
	m_StickValue(0, 0),
	m_pLacrossePlayer(pLacrossePlayer),
	m_Timer(0),
	m_pEvent(pEvent)
{

}


// �f�X�g���N�^
LacrosseCounterPose::~LacrosseCounterPose()
{
	delete m_pEvent;
}


// �X�V
bool LacrosseCounterPose::Update()
{
	if (m_Timer == 0)
	{// �\���J�n
		m_pEvent->PoseStart();
	}

	// ���W�X�V
	chr_func::PositionUpdate(m_pLacrossePlayer);

	// ����
	chr_func::XZMoveDown(
		m_pLacrossePlayer,
		m_PoseParams.MoveDownSpeed
		);

	// �X�V
	m_pEvent->Update();

	if (m_Timer >= m_PoseParams.AllFrame)
	{// �\���I��
		m_pEvent->PoseEnd();
		return false;
	}

	// �^�C�}�[�X�V
	m_Timer++;

	return true;
}


// �X�e�B�b�N�̒l�Z�b�g
void LacrosseCounterPose::SetStickValue(CrVector2 stickValue)
{
	m_StickValue = stickValue;
}
