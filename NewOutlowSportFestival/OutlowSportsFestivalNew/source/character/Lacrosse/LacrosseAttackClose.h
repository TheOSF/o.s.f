#pragma once

#include "iextreme.h"
#include <vector>


class LacrossePlayer;

// ダメージ(仮)
class DamageObject;
typedef DamageObject DamageObject;


//***************************************************
//		ラクロス用近距離攻撃クラス
//***************************************************
class LacrosseAttackClose
{
public:
	struct Params
	{
		float AttackPower;   // 攻撃力
		float StepPower;      // 踏み込み

		int DamageOutbreakFrame; // ダメージ発生フレーム(モーションではない)
		int EndFrame;                      // 攻撃終了フレーム
	};

	// 攻撃イベントクラス
	class AttackEvent
	{
	public:
		virtual~AttackEvent(){}
		virtual void Update() = 0;
		virtual void AttackStart() = 0;
		virtual void AttackEnd() = 0;
		virtual void DamageStart() = 0;
	};

	// コンストラクタ
	LacrosseAttackClose(
		LacrossePlayer* pLacrossePlayer,
		const Params& param,
		AttackEvent* pAttackEvent
		);

	// デストラクタ
	~LacrosseAttackClose();

	// 更新
	void Update();

	// スティックの値セット
	void SetStickValue(CrVector2 StickValue);

private:
	AttackEvent*     m_pAttackEvent;          // 攻撃イベント
	Vector2              m_StickValue;              // スティック入力状態
	LacrossePlayer* m_pLacrossePlayer;    // ラクロスプレイヤー
	int                      m_Timer;                    // タイマー
	const Params     m_Params;                 // パラメータ
};
