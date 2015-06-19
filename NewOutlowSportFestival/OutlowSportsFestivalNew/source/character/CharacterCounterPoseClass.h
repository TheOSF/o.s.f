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
		const int                               maxLevel,                  // 最大レベル
		const CounterPoseParams& counterPoseParams,  // 構えパラメータ
		CharacterBase*                    pCharacter,                // 動かしたいキャラクター
		Event*                                  pEvent                       // 構えイベント
		);

	// デストラクタ
	~CharacterCounterPose();

	// 更新
	bool Update();

	// level が最大レベルかどうか
	bool IsMaxLevel(int level)const;
	bool IsMaxLevel()const;

	// レベル取得
	inline int GetLevel()const{ return m_NowLevel; }

private:
	const int                              m_MaxLevel;                  // レベルアップパラメータ
	int                                       m_NowLevel;                  // 現在のレベル
	int                                       m_Timer;                        // タイマー
	int                                       m_TotalFrame;                // 全フレーム
	const CounterPoseParams  m_CounterPoseParams; // カウンター構えパラメータ
	CharacterBase*                  m_pCharacter;                // キャラクター
	Event*                                m_pEvent;                      // カウンター構えイベント
};

