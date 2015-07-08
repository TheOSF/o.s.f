#ifndef __CHARACTER_DASH_CLASS_H__
#define __CHARACTER_DASH_CLASS_H__

#include "iextreme.h"
#include "SoccerPlayer.h"

//****************************************************************
//		サッカーのダッシュクラス
//****************************************************************
//スライディングクラス
class SoccerDash
{
public:
	struct Params
	{
		float Acceleration;	//加速度
		float DownSpeed;	//減速する速度
		float MaxSpeed;		//最大速度
		float TurnSpeed;	//角度変化スピード
	};
	class MoveEvent
	{
	public:
		virtual~MoveEvent(){}
		virtual void Update(bool isRun, RATIO speed_ratio) = 0;	//毎フレーム実行される関数
		virtual void RunStart() = 0;			//走り開始時に呼ばれる関数
		virtual void StandStart() = 0;			//棒立ち開始時に呼ばれる関数
	};
	SoccerDash(CharacterBase*					pParent,	//操るキャラクタのポインタ
		const Params&					param,		//移動パラメータ構造体
		MoveEvent*						pMoveEvent,	//移動イベントに反応するクラス
		DamageManager::HitEventBase*	pHitEventBase//ダメージを受けた時に反応するクラス
		);


	~SoccerDash();

	Params Getparams()
	{
		return m_Params;
	}
	void Update();	//更新
	void SetStickValue(CrVector2 StickValue);
private:
	typedef DamageManager::HitEventBase HitEventBase;

	CharacterBase*	m_pParent;
	MoveEvent*		m_pMoveEvent;
	HitEventBase*	m_pHitEventBase;
	Params			m_Params;
	Vector2			m_StickValue;
	bool			m_isRun;
};
#endif