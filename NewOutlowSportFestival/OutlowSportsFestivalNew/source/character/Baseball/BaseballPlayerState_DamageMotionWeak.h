#ifndef __BASEBALL_PLAYER_STATE_DAMAGEMOTION_WEAK_H__
#define __BASEBALL_PLAYER_STATE_DAMAGEMOTION_WEAK_H__

#include "BaseballPlayer.h"
#include "../CharacterDamageMotion.h"

//***************************************************
//		テニスキャラクタの弱ひるみステート
//***************************************************
class BaseballState_DamageMotion_Weak : public BaseballState
{
public:
	BaseballState_DamageMotion_Weak(
		BaseballPlayer*  m_pBaseball,
		const Vector3& Damage_vec  //ダメージを受けた方向
		);

	// ステート開始
	void Enter(BaseballPlayer* t)override;

	// ステート実行
	void Execute(BaseballPlayer* t)override;

	// ステート終了
	void Exit(BaseballPlayer* t)override;

private:
	CharacterDamageMotion*   m_pDamageMotionClass;	//ひるみ更新クラス
	BaseballPlayer*          m_pBaseball;
	Vector3                  m_Damage_vec;
};

#endif