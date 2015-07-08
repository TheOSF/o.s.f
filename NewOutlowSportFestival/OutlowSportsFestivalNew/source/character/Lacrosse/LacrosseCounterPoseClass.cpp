#include "LacrossePlayer.h"
#include "LacrosseCounterPoseClass.h"
#include "../Template/CharacterFunction.h"

//***************************************************
//		ラクロス用 カウンター構えクラス
//***************************************************

// コンストラクタ
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


// デストラクタ
LacrosseCounterPose::~LacrosseCounterPose()
{
	delete m_pEvent;
}


// 更新
bool LacrosseCounterPose::Update()
{
	if (m_Timer == 0)
	{// 構え開始
		m_pEvent->PoseStart();
	}

	// 座標更新
	chr_func::PositionUpdate(m_pLacrossePlayer);

	// 減速
	chr_func::XZMoveDown(
		m_pLacrossePlayer,
		m_PoseParams.MoveDownSpeed
		);

	// 更新
	m_pEvent->Update();

	if (m_Timer >= m_PoseParams.AllFrame)
	{// 構え終了
		m_pEvent->PoseEnd();
		return false;
	}

	// タイマー更新
	m_Timer++;

	return true;
}


// スティックの値セット
void LacrosseCounterPose::SetStickValue(CrVector2 stickValue)
{
	m_StickValue = stickValue;
}
