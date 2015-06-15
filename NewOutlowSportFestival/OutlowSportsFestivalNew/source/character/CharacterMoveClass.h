#ifndef __CHARACTER_MOVE_CLASS_H__
#define __CHARACTER_MOVE_CLASS_H__

class CharacterBase;

#include "iextreme.h"

//****************************************************************
//		キャラクタ共通の動きクラス
//****************************************************************


//通常移動クラス
class CharacterUsualMove
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
		virtual void Update(bool isRun,RATIO speed_ratio) = 0;	//毎フレーム実行される関数
		virtual void RunStart() = 0;			//走り開始時に呼ばれる関数
		virtual void StandStart() = 0;			//棒立ち開始時に呼ばれる関数
	};

	CharacterUsualMove(
		CharacterBase*	pParent,	//操るキャラクタのポインタ
		const Params&	param,
		MoveEvent*		pMoveEvent);

	void Update();	//更新
	void SetStickValue(CrVector2 StickValue);
private:
	CharacterBase*	m_pParent;
	MoveEvent*		m_pMoveEvent;
	Params			m_Params;
	Vector2			m_StickValue;
	bool			m_isRun;
};

#endif