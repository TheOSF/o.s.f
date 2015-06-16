#pragma once

#include "iextreme.h"


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
	// 攻撃イベントクラス
	class Event
	{
	public:
		virtual~Event(){}
		virtual void Update() = 0;
		virtual void AttackStart() = 0;
		virtual void AttackEnd() = 0;
	};


	// コンストラクタ
	LacrosseAttackClose(
		LacrossePlayer* pLacrossePlayer,
		Event* pEvent
		);

	// デストラクタ
	~LacrosseAttackClose();

	// 更新
	void Update();

	// スティックの値セット
	void SetStickValue(CrVector2 StickValue);


private:
	Vector2              m_StickValue;             // スティック入力状態
	LacrossePlayer* m_pLacrossePlayer;   // ラクロスプレイヤー
	int                      m_Timer;                   // タイマー
	Event*                m_pEvent;                 // 攻撃イベントクラス
};


