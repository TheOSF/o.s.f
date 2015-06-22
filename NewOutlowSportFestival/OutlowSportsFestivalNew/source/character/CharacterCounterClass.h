#pragma once

#include "iextreme.h"

class CharacterBase;
class BallBase;

//***************************************************
//		キャラクター共通 カウンタークラス
//***************************************************
class CharacterCounter
{
public:
	// カウンターパラメータ
	struct CounterParams
	{
		int MaxPoseFrame;          // 最大タメ持続フレーム
		int LevelUpFrame;           // レベルアップするフレーム
		int CounterTotalFrame;   // カウンター振り始めてから終わるまでのフレーム
		int CounterMoveFrame;  // カウンターの移動にかけるフレーム数
		float MoveDownSpeed;   // 減速割合
		float CanCounterArea;    // カウンターのできる範囲
	};

	// カウンターイベントクラス
	class Event
	{
	public:
		virtual ~Event(){}
		virtual void Update() = 0;                       // 更新
		virtual void CounterPoseStart() = 0;       // 構えスタート
		virtual void CounterPoseEnd() = 0;        // 構え終了
		virtual void LevelUp(int level) = 0;          // レベルアップ
		virtual void CounterStart(int level) = 0;  // カウンター開始
		virtual void CounterEnd() = 0;                // カウンター終了
	};

	// コンストラクタ
	CharacterCounter(
		const int                       maxLevel,           // 最大レベル
		const CounterParams& counterParams, // カウンターパラメータ
		CharacterBase*            pCharacter,        // 動かしたいキャラクター
		Event*                          pEvent               // カウンターイベント
		);

	// デストラクタ
	~CharacterCounter();

	// 更新
	bool Update();

	// level が最大レベルかどうか
	bool IsMaxLevel(int level)const;

	// 現在最大レベルかどうか
	bool IsMaxLevel()const;

	// レベル取得
	inline int GetLevel()const{ return m_NowLevel; }

	// 溜めフラグセット
	void SetPoseEndFlg();

	// スティックの値セット
	inline void SetStickValue(CrVector2 stickValue){ m_StickValue = stickValue; }

private:
	const int                      m_MaxLevel;                   // レベルアップパラメータ
	int                               m_NowLevel;                   // 現在のレベル
	int                               m_Timer;                         // タイマー
	int                               m_TotalPoseFrame;         // 溜めが終わるまでの全フレーム
	bool                            m_PoseFlg;                      // 溜めフラグ
	Vector2                       m_StickValue;                 // スティックの入力状態
	const CounterParams m_CounterParams;         // カウンターパラメータ
	CharacterBase*          m_pCharacter;               // 動かしたいキャラクター
	Event*                        m_pEvent;                      // カウンターイベント
	BallBase*                   m_pCounterBall;             // カウンターする予定のボール
	CharacterBase*         m_pCounterBallOwner;  // カウンターしたいボールを打った人
	Vector3                      m_CounterPos;               // カウンターする位置

};
