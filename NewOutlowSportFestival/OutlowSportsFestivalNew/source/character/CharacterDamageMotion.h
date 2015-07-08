#pragma once

#include "iextreme.h"
#include "../GameSystem/ForwardDecl.h"
#include "../Damage/Damage.h"

//***************************************************
//		キャラクター共通 ひるみクラス
//***************************************************
class CharacterDamageMotion
{
public:
	// パラメータ
	struct Params
	{
		int AllFrame;       // 全フレーム
		int NoDamageFrame;	//無敵フレーム
		int hitStopFrame;	//ヒットストップフレーム
		float hitBack;		//ヒットバック距離
		Vector3 damage_vec;	//ダメージの方向
	};

	// ひるみイベントクラス
	class Event
	{
	public:
		virtual~Event(){}
		virtual void Update(float speed) = 0;       // 更新(引数はモーションスピード)
		virtual void Start() = 0;     // ひるみ開始
		virtual void End() = 0;      // ひるみ終了
	};

	// コンストラクタ
	CharacterDamageMotion(
		CharacterBase* pCharacter,
		Event* pEvent,
		DamageManager::HitEventBase* pHitEvent, 
		const Params& params
		);

	// デストラクタ
	~CharacterDamageMotion();

	// 更新
	void Update();

private:
	bool				           m_Start;
	bool				           m_End;
	Params		                   m_Params;      // パラメータ
	CharacterBase*                 m_pCharacter;  // キャラクター
	int                            m_Timer;       // タイマー
	Event*                         m_pEvent;      // イベント
	DamageManager::HitEventBase*   m_pHitEvent;   //　ヒットイベント
};

