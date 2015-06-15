#include "Damage.h"


//�_���[�W�N���X
DamageBase::DamageBase() :
pParent(nullptr),
pBall(nullptr),
type(_WeekDamage),
Value(1),
vec(Vector3Zero)
{
	MyAssert(DefDamageMgr.AddDamage(this), "�_���[�W�o�^�̎��s");
}

DamageBase::~DamageBase()
{
	MyAssert(DefDamageMgr.EraceDamage(this), "�_���[�W�폜�̎��s");
}


//�_���[�W�N���X(��)
bool DamageShpere::HitCheckSphere(const ShpereParam* sp)
{
	const float L = Vector3Length(sp->pos - this->m_Param.pos);

	return L < (sp->size + this->m_Param.size);
}


//*************************************************************
//		�_���[�W����}�l�[�W��
//*************************************************************

DamageManager* DamageManager::m_pInstance = nullptr;

DamageManager& DamageManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new DamageManager();
	}

	return *m_pInstance;
}

void DamageManager::Release()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}


//���̃_���[�W������Ƃ�
void DamageManager::HitCheckSphere(
	const ShpereParam&	sp,
	HitEventBase&		HitEvent
	)
{
	for (auto it = m_DamageBaseMap.begin();
		it != m_DamageBaseMap.end();
		++it
		)
	{
		if (it->second->HitCheckSphere(&sp))
		{
			HitEvent.Hit(it->second);
		}
	}
}


DamageManager::DamageManager()
{

}

DamageManager::~DamageManager()
{

}


bool DamageManager::AddDamage(DamageBase* pDmg)
{
	if (m_DamageBaseMap.find(pDmg) != m_DamageBaseMap.end())
	{
		return false;
	}

	m_DamageBaseMap.insert(
		DamageBaseMap::value_type(pDmg, pDmg));

	return true;
}


bool DamageManager::EraceDamage(DamageBase* pDmg)
{
	auto it = m_DamageBaseMap.find(pDmg); 

	if (it == m_DamageBaseMap.end())
	{
		return false;
	}

	m_DamageBaseMap.erase(it);

	return true;
}