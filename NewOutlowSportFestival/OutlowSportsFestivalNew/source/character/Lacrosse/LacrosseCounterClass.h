#pragma once

#include "iextreme.h"


class LacrossePlayer;

//***************************************************
//		ラクロス用 カウンター打つ クラス
//***************************************************
class LacrosseCounter
{
public:
	// カウンターパラメータ
	struct CounterParams
	{
		int CounterFrame;                // カウンター全フレーム
		int DamageOutbreakFrame; // ダメージ判定発生フレーム(ボール発射フレーム)
		float MaxTurnRadian;           // 向き補正の角度制限
		float CounterAttackPower;   // カウンターした時の攻撃力
		float CounterSpeed;             // カウンター(ボール)のスピード
	};

	// 構えパラメータ
	struct CounterPoseParams
	{
		int PoseFrame;              // 最大タメ持続フレーム
		float MoveDownSpeed; // 減速割合
	};

	// レベルアップパラメータ
	struct LevelUpParams
	{
		int LevelUpFrame;  // レベルアップするフレーム
		float AddPower;     // 追加する攻撃力
		float AddSpeed;     // 追加する(ボールの)スピード
	};

	class Event
	{
	public:
		virtual~Event(){}
		virtual void Update() = 0;           // 更新
		virtual void PoseStart() = 0;       // 構え開始
		virtual void PoseEnd() = 0;         // 構え終了
		virtual void CounterStart() = 0;  // カウンター開始
		virtual void CounterEnd() = 0;    // カウンター終了
		virtual void LevelUp() = 0;          // レベルアップ
		virtual void DamageStart() = 0;  // ダメージ発生
	};




};

