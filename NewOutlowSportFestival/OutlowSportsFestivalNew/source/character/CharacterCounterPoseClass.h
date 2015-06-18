#pragma once

#include "iextreme.h"
#include <vector>

class CharacterBase;
//***************************************************
//		キャラクター共通 カウンター構えクラス
//***************************************************
class CharacterCounterPose
{
public:
	// カウンター構えパラメータ
	struct CounterPoseParams
	{
		int MaxPoseFrame;       // 最大タメ持続フレーム
		int LevelUpFrame;        // レベルアップするフレーム
		float MoveDownSpeed; // 減速割合
	};

	// カウンター構えイベント
	class Event
	{
	public:
		virtual~Event(){}
		virtual void Update() = 0;              // 更新
		virtual void PoseStart() = 0;          // 構え開始
		virtual void PoseEnd() = 0;            // 構え終了
		virtual void LevelUp(int level) = 0; // レベルアップ
	};

	// コンストラクタ
	CharacterCounterPose(
		const int MaxLevel,
		const CounterPoseParams& counterPoseParams,
		CharacterBase* pCharacter,
		Event* pEvent
		);

	// デストラクタ
	~CharacterCounterPose();

	// 更新
	bool Update();

	// スティックの値セット
	void SetStickValue(CrVector2 stickValue);

	// 最大レベルかどうか
	bool IsMaxLevel(int level)const;

private:
	const int                              m_MaxLevel;                  // レベルアップパラメータ
	int                                       m_Timer;                        // タイマー
	int                                       m_NowLevel;                  // 現在のレベル
	const CounterPoseParams  m_CounterPoseParams; // カウンター構えパラメータ
	Vector2                               m_StickValue;                 // スティックの入力状態
	CharacterBase*                  m_pCharacter;                // キャラクター
	Event*                                m_pEvent;                      // カウンター構えイベント
};

