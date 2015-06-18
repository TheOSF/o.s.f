#include "Collision.h"


//*******************************************************
//	あたり判定オブジェクトベース
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
//	あたり判定オブジェクトマネージャ
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

//レイピック
bool CollisionManager::RayPick(
	LPVECTOR3	pOut,		//レイが当たった場合その場所を格納する
	LPVECTOR3	pPos,		//レイを打ち始める場所
	LPVECTOR3	pVec,		//レイを打つ方向
	float *		pDist,		//レイの長さ
	int*		pMaterial,	//レイが当たった場合そのポリゴンの材質番号を格納する
	RayType		type		//レイのタイプ(処理を分ける可能性があるため)
	)
{
	bool ret = false;

	const Vector3 fpos(*pPos), fvec(*pVec);
	const float fdist(1000000);	//スケール変換を無視したい

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

		//オブジェクトにレイが当たっていたら
		if (it->first->RayPick(
			&tout,
			&tpos,
			&tvec,
			&tdist,
			&tMaterial,
			type))
		{
			tlen = Vector3Distance(fpos, tout);
			
			//今までの最短距離より短いか
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