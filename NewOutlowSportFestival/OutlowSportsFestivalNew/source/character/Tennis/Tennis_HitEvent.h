#ifndef __TENNIS_HITEVENT_H__
#define __TENNIS_HITEVENT_H__

#include "../../Damage/Damage.h"
#include "TennisPlayer.h"

//************************************************************
//	�e�j�X�̃_���[�W���󂯂����̔����N���X
//************************************************************

class TennisHitEvent :public DamageManager::HitEventBase
{
public:
	TennisHitEvent(TennisPlayer* pt);
	
	bool Hit(DamageBase* pDmg);//�����������ɌĂ΂��֐�(�߂�l�F�����������ǂ���)
private:
	TennisPlayer* m_pTennis;
};

#endif