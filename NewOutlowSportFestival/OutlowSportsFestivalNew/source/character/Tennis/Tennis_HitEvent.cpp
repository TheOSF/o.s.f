#include "Tennis_HitEvent.h"
#include "TennisPlayerState_DamageMotionWeak.h"

TennisHitEvent::TennisHitEvent(TennisPlayer* pt) :
m_pTennis(pt)
{

}

bool TennisHitEvent::Hit(DamageBase* pDmg)
{

	//自分の作っているダメージだった場合は何もしない
	if (pDmg->pParent->m_PlayerInfo.number == m_pTennis->m_PlayerInfo.number)
	{
		return false;
	}

	//当たった時にそのダメージの種類から、それぞれのステートに派生させる
	switch (pDmg->type)
	{
	case DamageBase::Type::_WeekDamage:
		//弱ひるみ
		m_pTennis->SetState(new TennisState_DamageMotion_Weak(m_pTennis, pDmg->vec));
		return true;

	/*
	//未作成
	case DamageBase::Type::_VanishDamage:
		//吹き飛びダメージ
		m_pTennis->SetState(new TennisState_(m_pTennis));
		return true;
	case DamageBase::Type::_UpDamage:
		//上に吹き飛び
		m_pTennis->SetState(new TennisState_(m_pTennis));
		return true;
	*/

	default:break;
	}

	return false;
}