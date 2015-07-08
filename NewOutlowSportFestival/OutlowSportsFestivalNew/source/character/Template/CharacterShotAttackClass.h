#pragma once

#include "iextreme.h"
#include "../../Damage/Damage.h"

class CharacterBase;

//***************************************************
//		キャラクター共通 遠距離攻撃 (ボール打ち出し) クラス
//***************************************************
class CharacterShotAttack
{
public:
	// 攻撃パラメータ
	struct AttackParams
	{
		int AllFrame;                 // 全フレーム
		int ShotFrame;              // ボール＆ダメージ判定発生フレーム
		float MaxTurnRadian;    // 向き補正の角度制限
		float AttackPower;        // 攻撃力
		float MoveDownSpeed; // 減速割合
	};

	// 攻撃イベントクラス
	class Event
	{
	public:
		virtual~Event(){}
		virtual void Update() = 0;           // 更新
		virtual void Shot() = 0;               // ダメージ判定開始 & ボール発射
		virtual void AttackStart() = 0;     // 攻撃開始
		virtual void AttackEnd() = 0;      // 攻撃終了
	};

	// コンストラクタ
	CharacterShotAttack(
		CharacterBase* pCharacter,
		Event* pEvent,
		const AttackParams& attack_params,
		HitEventBase*    pHitEventBase
		);

	// デストラクタ
	~CharacterShotAttack();

	// 更新
	bool Update();

	// スティックの値セット
	void SetStickValue(CrVector2 stickValue);

private:
	const AttackParams m_AttackParams;      // 攻撃パラメータ
	Vector2                    m_StickValue;           // スティックの入力状態
	CharacterBase*       m_pCharacter;          // キャラクター
	int                            m_Timer;                  // タイマー
	Event*                     m_pEvent;                // 攻撃イベント
	HitEventBase*    m_pHitEventBase;  //ダメージを受けた時に呼び出されるイベント
};

