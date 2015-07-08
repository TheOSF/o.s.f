#include "Tennis_HitEvent.h"
#include "TennisPlayerState_DamageMotionWeak.h"

TennisHitEvent::TennisHitEvent(TennisPlayer* pt) :
m_pTennis(pt)
{

}

bool TennisHitEvent::Hit(DamageBase* pDmg)
{
	//当たった時にそのダメージの種類から、それぞれのステートに派生させる
	switch (pDmg->type)
	{
	case DamageBase::Type::_WeekDamage:
		//弱攻撃
		m_pTennis->SetState(new TennisState_DamageMotion_Weak(m_pTennis, pDmg->vec));
		return true;
	//case DamageBase::Type::_VanishDamage:
	//	//吹き飛びダメージ
	//	m_pTennis->SetState(new TennisState_DamageMotion_Weak(m_pTennis));
	//	return true;
	//case DamageBase::Type::_UpDamage:
	//	//上に吹き飛び
	//	m_pTennis->SetState(new TennisState_DamageMotion_Weak(m_pTennis));
	//	return true;

	default:break;
	}

	return false;
}