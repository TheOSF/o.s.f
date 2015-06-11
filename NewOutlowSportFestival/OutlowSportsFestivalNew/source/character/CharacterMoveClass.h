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
		float MaxSpeed;		//最大速度
		float TurnSpeed;	//角度変化スピード
	};

	CharacterUsualMove(
		CharacterBase* pParent,	//操るキャラクタのポインタ
		const Params& param);

	void Update();	//更新
	void SetStickValue(CrVector2 StickValue);

private:
	CharacterBase*	pParent;
	Params			m_Params;
	Vector2			m_StickValue;
};

#endif