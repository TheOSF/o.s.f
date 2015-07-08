#pragma once

#include "iextreme.h"

class CharacterBase;

//***************************************************
//		キャラクター共通 回避クラス
//***************************************************
class CharacterEvasion
{
public:
	// 回避用パラメータ
	struct EvasionParams
	{
		int AllFrame;                          // 全フレーム
		int NoDamageStartFrame;     // 無敵開始フレーム
		int NoDamageEndFrame;      // 無敵終了フレーム
		float MoveDownSpeed;          // 減速割合
		float MoveSpeed;                   // 移動スピード
		float MaxTurnRadian;             // 向き補正の角度制限
	};

	// 回避イベントクラス
	class Event
	{
	public:
		virtual~Event(){}
		virtual void Update() = 0;                // 更新
		virtual void EvasionStart() = 0;       // 回避行動開始s
		virtual void EvasionEnd() = 0;         // 回避行動終了
	};

	// コンストラクタ
	CharacterEvasion(
		CharacterBase* pCharacterBase,
		Event* pEvent,
		const EvasionParams& evasion_params
		);

	// デストラクタ
	~CharacterEvasion();

	// 更新
	bool Update();

	// スティックの値セット
	void SetStickValue(CrVector2 stickValue);

	// ダメージを受けることができるかどうか
	bool CanGetDamage()const;

private:
	const EvasionParams m_EvasionParams;   // 回避パラメータ
	Vector2                      m_StickValue;           // スティック入力状態
	CharacterBase*         m_pCharacterBase;  // キャラクター
	int                              m_Timer;                  // タイマー
	Event*                       m_pEvent;                // 回避イベント


};
