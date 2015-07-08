#ifndef __TENNIS_PLAYER_STATE_DAMAGEMOTION_WEAK_H__
#define __TENNIS_PLAYER_STATE_DAMAGEMOTION_WEAK_H__

#include "TennisPlayer.h"
#include "../CharacterDamageMotion.h"

//***************************************************
//		テニスキャラクタの弱ひるみステート
//***************************************************
class TennisState_DamageMotion_Weak : public TennisState
{
public:
	TennisState_DamageMotion_Weak(
		TennisPlayer*  pTennis,
		const Vector3& Damage_vec  //ダメージを受けた方向
		);

	// ステート開始
	void Enter(TennisPlayer* t)override;

	// ステート実行
	void Execute(TennisPlayer* t)override;

	// ステート終了
	void Exit(TennisPlayer* t)override;

private:
	CharacterDamageMotion*   m_pDamageMotionClass;	//ひるみ更新クラス
	TennisPlayer*            m_pTennis;
	Vector3                  m_Damage_vec;
};

#endif