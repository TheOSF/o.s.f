#include "Collision.h"


//*******************************************************
//	�����蔻��I�u�W�F�N�g�x�[�X
//*******************************************************

CollisionBase::CollisionBase()
{
	DefCollisionMgr.Add(this);
}

CollisionBase::~CollisionBase()
{
	DefCollisionMgr.Erace(this);
}


//*******************************************************
//	�����蔻��I�u�W�F�N�g�}�l�[�W��
//*******************************************************

CollisionManager* CollisionManager::m_pInstance = nullptr;

CollisionManager& CollisionManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CollisionManager();
	}

	return *m_pInstance;
}

void CollisionManager::Release()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

//���C�s�b�N
bool CollisionManager::RayPick(
	LPVECTOR3	pOut,		//���C�����������ꍇ���̏ꏊ���i�[����
	LPVECTOR3	pPos,		//���C��ł��n�߂�ꏊ
	LPVECTOR3	pVec,		//���C��ł���
	float *		pDist,		//���C�̒���
	int*		pMaterial,	//���C�����������ꍇ���̃|���S���̍ގ��ԍ����i�[����
	RayType		type		//���C�̃^�C�v(�����𕪂���\�������邽��)
	)
{
	bool ret = false;

	const Vector3 fpos(*pPos), fvec(*pVec);
	const float fdist(1000000);	//�X�P�[���ϊ��𖳎�������

	Vector3 tout, tpos, tvec;
	float tdist;
	int tMaterial;

	float mostnear = *pDist;
	float tlen;

	for (auto it = m_CollisionMap.begin();
		it != m_CollisionMap.end();
		++it)
	{
		tpos = fpos;
		tvec = fvec;
		tdist = fdist;

		//�I�u�W�F�N�g�Ƀ��C���������Ă�����
		if (it->first->RayPick(
			&tout,
			&tpos,
			&tvec,
			&tdist,
			&tMaterial,
			type))
		{
			tlen = Vector3Distance(fpos, tout);
			
			//���܂ł̍ŒZ�������Z����
			if (tlen <= mostnear)
			{
				mostnear = tlen;

				*pOut = tout;
				*pVec = tvec;
				*pDist = mostnear;
				*pMaterial = tMaterial;

				ret = true;
			}
		}
	}

	return ret;
}


bool CollisionManager::Add(CollisionBase* pIn)
{
	if (m_CollisionMap.find(pIn)!= m_CollisionMap.end())
	{
		return false;
	}
	
	m_CollisionMap.insert(CollisionMap::value_type(pIn, pIn));

	return true;
}


bool CollisionManager::Erace(CollisionBase* pIn)
{
	auto it = m_CollisionMap.find(pIn);

	if (it == m_CollisionMap.end())
	{
		return false;
	}

	m_CollisionMap.erase(it);
	return true;
}