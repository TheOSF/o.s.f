#ifndef __CHARACTER_SHOT_H__
#define __CHARACTER_SHOT_H__


class CharacterBase;

#include "iextreme.h"

//****************************************************************
//		キャラクタ共通の玉を発射するクラス
//****************************************************************


//玉を発射するクラス
class CharacterShot
{
public:
	struct Params
	{
		int shot_frame;
		
	};

	class ShotEvent
	{
	public:
		virtual~ShotEvent(){}
		virtual void Update() = 0;	//毎フレーム実行される関数
	};

	CharacterShot(
		CharacterBase*	pParent,	//操るキャラクタのポインタ
		const Params&	param,		//行動パラメータ
		ShotEvent*		pMoveEvent	//移動イベントクラス
		);

	void Update();	//更新
private:

};

#endif 