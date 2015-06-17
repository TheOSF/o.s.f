#pragma once

#include "iextreme.h"

class LacrossePlayer;


//***************************************************
//		ラクロス用 カウンター構えクラス
//***************************************************
class LacrosseCounterPose
{
public:
	// カウンター構え用 パラメータ
	struct CounterPoseParams
	{
		int AllFrame;                 // 全フレーム
		float TurnSpeed;           // 向き補正速度
		float MoveDownSpeed; // 減速割合
	};

	// カウンター構えイベントクラス
	class Event
	{
	public:
		virtual ~Event(){}
		virtual void Update() = 0;      // 更新
		virtual void PoseStart() = 0;  // 構え開始
		virtual void PoseEnd() = 0;    // 構え終了
	};

	// コンストラクタ
	LacrosseCounterPose(
		LacrossePlayer* pLacrossePlayer,
		Event* pEvent,
		const CounterPoseParams& pose_params
		);
	
	// デストラクタ
	~LacrosseCounterPose();

	// 更新
	bool Update();

	// スティックの値セット
	void SetStickValue(CrVector2 stickValue);

private:
	const CounterPoseParams m_PoseParams;         // 構えパラメータ
	Vector2                              m_StickValue;            // スティック入力状態
	LacrossePlayer*                 m_pLacrossePlayer;  // ラクロスプレイヤー
	int                                      m_Timer;                   // タイマー
	Event*                               m_pEvent;                 // 構えイベントクラス
};


