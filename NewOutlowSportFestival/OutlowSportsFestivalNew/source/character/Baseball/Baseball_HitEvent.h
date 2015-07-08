#ifndef __BASEBALL_HITEVENT_H__
#define __BASEBALL_HITEVENT_H__

#include "../../Damage/Damage.h"
#include "BaseballPlayer.h"

//************************************************************
//	�e�j�X�̃_���[�W���󂯂����̔����N���X
//************************************************************

class BaseballHitEvent :public DamageManager::HitEventBase
{
public:
	BaseballHitEvent(BaseballPlayer* pt);

	bool Hit(DamageBase* pDmg);//�����������ɌĂ΂��֐�(�߂�l�F�����������ǂ���)
private:
	BaseballPlayer* m_pBaseball;
};

#endif