#pragma once

#include "iextreme.h"

#include "../../GameSystem/GameController.h"
#include "../../Damage/Damage.h"

class CharacterBase;
class BallBase;


//****************************************************************
//		キャラクタ共通のカウンタークラス
//****************************************************************
class CharacterCounter
{
public:
	// 行動状態
	enum CounterStep
	{
		_cs_pose = 1 << 0,
		_cs_swing = 1 << 1,
		_cs_move_to_ball = 1 << 2,
	};

	// パラメータ
	struct CounterParams
	{
		int MaxCounterLevel;            // カウンターの最大レベル
		int MaxPoseFrame;               // 最大タメ持続フレーム
		int LevelUpFrame;                 // レベルアップするフレーム
		int SwingTotalFrame;            // カウンター振り始めてから終わるまでのフレーム
		int MoveToBallFrame;           // ボールに向かって移動するフレーム
		float NormalCounterArea;    // カウンターのできる範囲
		float JustCounterArea;         // ジャストカウンターエリア
		float DamageReceiveArea;  // ボールがこの距離より近いとダメージ判定を優先する
		float MoveDownSpeed;        // 減速割合
	};

	// イベント
	class CounterEvent
	{
	public:
		virtual~CounterEvent(){}
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
		CharacterBase*                             pParent,                          // 動かしたいキャラクター
		const CounterParams&                  counterParams,               // カウンターパラメータ
		CounterEvent*                               pCounterEvent                // カウンターイベント
		);

	// デストラクタ
	~CharacterCounter();


	// 更新
	void Update();

	// スティックの値セット
	inline void SetStickValue(CrVector2 stickValue){ m_StickValue = stickValue; }

	// ボタンの値セット
	inline void SetButtonState(controller::button::button_state buttonState){ m_ButtonState = buttonState; }

private:
	// 移動更新
	void UpdateUsualMove();

	// レベルアップ更新
	void UpdateLevelUp();

	// 構え更新
	void UpdatePose();

	// スイング更新
	void UpdateSwing();

	// ボールに向かって移動する
	void UpdateMoveToBall();
	

	// カウンターできるかどうか
	bool IsCanCounter();

	// ボールを打ち返す
	void HitBall();

	// カウンターできるボールを探す
	bool SerchCounterBall();

	// タイミング判定
	void CalcHitTiming();

private:
	typedef controller::button::button_state button_state;

	// パラメータ
	const CounterParams m_CounterParams;
	Vector2                       m_StickValue;
	button_state               m_ButtonState;
	int                               m_NowLevel;
	int                               m_Step;
	bool                             m_IsJust;

	// タイマー
	struct Timer
	{
		int LevelUp;      // レベルアップ
		int Swing;         // スイング
		int Pose;           // 最大ため持続
		int MoveToBall; // ボールに向かって移動する
	} m_Timer;

	// データ
	CharacterBase*           m_pParent;
	CounterEvent*             m_pCounterEvent;

	// カウンター用
	BallBase*           m_pCounterBall;
	CharacterBase* m_pCounterBallParent;
	Vector3              m_CounterPos;
};



