#include "Baseball_HitEvent.h"
#include "BaseballplayerState_DamageMotionWeak.h"

BaseballHitEvent::BaseballHitEvent(BaseballPlayer* pt) :
m_pBaseball(pt)
{

}

bool BaseballHitEvent::Hit(DamageBase* pDmg)
{

	//�����̍���Ă���_���[�W�������ꍇ�͉������Ȃ�
	if (pDmg->pParent->m_PlayerInfo.number == m_pBaseball->m_PlayerInfo.number)
	{
		return false;
	}

	//�����������ɂ��̃_���[�W�̎�ނ���A���ꂼ��̃X�e�[�g�ɔh��������
	switch (pDmg->type)
	{
	case DamageBase::Type::_WeekDamage:
		//��U��
		//m_pBaseball->SetState(new BaseballState_DamageMotion_Weak(m_pBaseball, pDmg->vec));
		return true;

		/*
		//���쐬
		case DamageBase::Type::_VanishDamage:
		//������у_���[�W
		m_pTennis->SetState(new TennisState_(m_pTennis));
		return true;
		case DamageBase::Type::_UpDamage:
		//��ɐ������
		m_pTennis->SetState(new TennisState_(m_pTennis));
		return true;
		*/

	default:break;
	}

	return false;
}