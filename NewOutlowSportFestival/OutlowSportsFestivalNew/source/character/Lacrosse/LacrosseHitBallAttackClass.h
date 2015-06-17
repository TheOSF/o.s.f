#pragma once

#include "iextreme.h"

class LacrossePlayer;

//***************************************************
//		ラクロス用 遠距離攻撃 (ボール打ち出し) クラス
//***************************************************
class LacrosseHitBallAttack
{
public:
	// 攻撃パラメータ
	struct AttackParams
	{
		int AllFrame;                         // 全フレーム
		int DamageOutbreakFrame; // ボール＆ダメージ判定発生フレーム
		float MaxTurnRadian;           // 向き補正の角度制限
		float AttackPower;               // 攻撃力
		float MoveDownSpeed;        // 減速割合
	};

	// 攻撃イベントクラス
	class Event
	{
	public:
		virtual~Event(){}
		virtual void Update() = 0;           // 更新
		virtual void DamageStart() = 0;  // ダメージ判定開始
		virtual void AttackStart() = 0;     // 攻撃開始
		virtual void AttackEnd() = 0;      // 攻撃終了
	};

	// コンストラクタ
	LacrosseHitBallAttack(
		LacrossePlayer* pLacrossePlayer, 
		Event* pEvent,
		const AttackParams& attack_params
		);

	// デストラクタ
	~LacrosseHitBallAttack();

	// 更新
	bool Update();

	// スティックの値セット
	void SetStickValue(CrVector2 stickValue);

private:
	const AttackParams m_AttackParams;      // 攻撃パラメータ
	Vector2                    m_StickValue;           // スティックの入力状態
	LacrossePlayer*       m_pLacrossePlayer;  // ラクロスプレイヤー
	int                            m_Timer;                  // タイマー
	Event*                     m_pEvent;                // 攻撃イベント
};

