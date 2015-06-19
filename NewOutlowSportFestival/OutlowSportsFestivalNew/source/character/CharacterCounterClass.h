#pragma once

#include "iextreme.h"

class CharacterBase;
//***************************************************
//		キャラクター共通 カウンタークラス
//***************************************************
class CharacterCounter
{
public:
	// カウンターパラメータ
	struct CounterParams
	{
		int TotalFrame;
		int Level;
		float MoveDownSpeed;
	};

	// カウンターイベントクラス
	class Event
	{
	public:
		virtual ~Event(){}
		virtual void Update() = 0;                       // 更新
		virtual void CounterStart(int level) = 0;  // カウンター開始
		virtual void CounterEnd() = 0;                // カウンター終了
	};

	// コンストラクタ
	CharacterCounter(
		const CounterParams& counterParams,  // カウンターパラメータ
		CharacterBase*            pCharacter,         // 動かしたいキャラクター
		Event*                          pEvent                // カウンターイベント
		);

	// デストラクタ
	~CharacterCounter();

	// 更新
	bool Update();

	// スティックの値セット
	void SetStickValue(CrVector2 stickValue);

private:
	int                              m_Timer;                 // タイマー
	Vector2                      m_StickValue;          // スティックの入力状態
	const CounterParams m_CounterParams; // カウンターパラメータ
	CharacterBase*          m_pCharacter;        // 動かしたいキャラクター
	Event*                        m_pEvent;              // カウンターイベント


};
