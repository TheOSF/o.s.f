#pragma once

#include "iextreme.h"

#include "../GameSystem/GameController.h"

class CharacterBase;
class BallBase;

//***************************************************
//		キャラクター共通 カウンタークラス
//***************************************************
class CharacterCounter
{
public:
	// 現在とっている行動
	enum CounterStep
	{
		cs_pose                = 1 << 0,
		cs_move_to_ball  = 1 << 1,
		cs_swing               = 1 << 2,
	};

	// カウンターパラメータ
	struct CounterParams
	{
		int MaxPoseFrame;          // 最大タメ持続フレーム
		int LevelUpFrame;           // レベルアップするフレーム
		int SwingTotalFrame;      // カウンター振り始めてから終わるまでのフレーム
		int CounterMoveFrame;  // カウンターの移動にかけるフレーム数
		float MoveDownSpeed;   // 減速割合
		float CanCounterArea;    // カウンターのできる範囲
	};

	// カウンターイベントクラス
	class Event
	{
	public:
		virtual~Event(){}
		virtual void Update() = 0;                   // 更新
		virtual void PoseStart() = 0;               // 構え開始
		virtual void PoseEnd() = 0;                 // 構え終了
		virtual void BallEnter() = 0;                // カウンターできるボールが現れた
		virtual void LevelUp(int level) = 0;     // レベルアップ
		virtual void SwingStart() = 0;             // スイング開始
		virtual void SwingEnd() = 0;               // スイング終了
		virtual void HitBall(bool is_just) = 0;  // 打ち返したとき
	};

	// コンストラクタ
	CharacterCounter(
		const int                        maxLevel,           // 最大レベル
		const CounterParams& counterParams,  // カウンターパラメータ
		CharacterBase*            pCharacter,        // 動かしたいキャラクター
		Event*                          pEvent                // カウンターイベント
		);

	// デストラクタ
	~CharacterCounter();

	// 更新
	bool Update();

	// 使用するボタンの状態をセット
	inline void SetButtonState(controller::button::button_state state){ m_ButtonState = state; }

	// スティックの値セット
	inline void SetStickValue(CrVector2 stickValue){ m_StickValue = stickValue; }

private:
	// レベルアップの更新
	void UpdateLevelUp();

	// 構え中の更新
	void UpdatePose();

	// 移動中の更新
	void UpdateMove();

	// スイング中の更新
	void UpdateSwing();

	// 通常の移動更新
	void UsualMoveUpdate();

	// ボールに向かって動く
	void MoveToBall();

	// ボールを打ち返す
	void HitBall();

	// カウンターできるボールを探す
	bool SerchCounterBall();

private:
	// パラメータ
	controller::button::button_state m_ButtonState;
	Vector2                                         m_StickValue;
	int                                                 m_NowLevel;
	WORD                                           m_Step;

	// データ
	const CounterParams  m_CounterParams;
	const int                       m_MaxLevel;
	CharacterBase*           m_pCharacter;
	Event*                         m_pEvent;

	// タイマー
	int m_LevelUpTimer;
	int m_MoveTimer;
	int m_PoseTimer;
	int m_SwingTimer;


	// カウンター用
	CharacterBase* m_pCounterBallOwner;
	BallBase*           m_pCounterBall;
	Vector3              m_CounterPos;

};
