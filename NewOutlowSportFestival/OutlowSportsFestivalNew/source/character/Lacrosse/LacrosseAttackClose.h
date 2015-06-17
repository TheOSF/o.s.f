#pragma once

#include "iextreme.h"


class LacrossePlayer;


//***************************************************
//		ラクロス用 近距離攻撃クラス
//***************************************************
class LacrosseAttackClose
{
public:
	// コンボ用パラメータ
	struct ComboParams
	{
		float MoveSpeed;                     // 移動スピード
		float MoveDownSpeed;            // 減速割合
		float MaxTurnRadian;               // 向き補正の角度制限
		int    DamageOutbreakFrame;  // ダメージ発生フレーム
		int    AllFrame;                         // 全フレーム
		int    CanDoComboFrame;       // 次のコンボができるフレーム
		int    GoNextComboFrame;      // コンボを実行するフレーム
	};

	// 攻撃イベントクラス
	class Event
	{
	public:
		virtual~Event(){}
		virtual void Update() = 0;           // 更新
		virtual void DamageStart() = 0; // ダメージ開始
		virtual void AttackStart() = 0;    // 攻撃開始
		virtual void AttackEnd() = 0;      // 攻撃終了
	};

	// コンストラクタ
	LacrosseAttackClose(
		LacrossePlayer* pLacrossePlayer,
		Event* pEvent,
		const ComboParams& combo_params
		);

	// デストラクタ
	~LacrosseAttackClose();

	// 更新
	bool Update();

	// スティックの値セット
	void SetStickValue(CrVector2 stickValue);

	// コンボできるかどうか
	bool CanDoCombo()const;

	// コンボ実行できるかどうか
	bool CanGoNextCombo()const;

private:
	const ComboParams m_ComboParams;       // コンボパラメータ
	Vector2                     m_StickValue;              // スティック入力状態
	LacrossePlayer*        m_pLacrossePlayer;    // ラクロスプレイヤー
	int                             m_Timer;                     // タイマー
	Event*                       m_pEvent;                  // 攻撃イベントクラス
};


