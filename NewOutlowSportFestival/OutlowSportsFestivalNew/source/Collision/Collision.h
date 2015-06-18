#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "iextreme.h"
#include <map>

//*******************************************************
//	あたり判定オブジェクトベース
//*******************************************************
class CollisionBase
{
public:
	//レイのタイプ
	enum RayType
	{
		_Usual,
	};

	CollisionBase();
	virtual~CollisionBase();

	//線とのあたり判定
	virtual bool RayPick(
		LPVECTOR3	pOut,		//レイが当たった場合その場所を格納する
		LPVECTOR3	pPos,		//レイを打ち始める場所
		LPVECTOR3	pVec,		//レイを打つ方向
		float *		pDist,		//レイの長さ
		int*		pMaterial,	//レイが当たった場合そのポリゴンの材質番号を格納する
		RayType		type		//レイのタイプ(処理を分ける可能性があるため)
		) = 0;
	
	//当たったときの処理
	virtual void Hit(			
		CrVector3	hit_pos,
		int			hit_material
		) = 0;
};


//*******************************************************
//	あたり判定オブジェクトマネージャ
//*******************************************************
class CollisionManager
{
public:
	typedef CollisionBase::RayType RayType;

	static CollisionManager& GetInstance();
	static void Release();

	//レイピック
	bool RayPick(
		LPVECTOR3	pOut,		//レイが当たった場合その場所を格納する
		LPVECTOR3	pPos,		//レイを打ち始める場所
		LPVECTOR3	pVec,		//レイを打つ方向
		float *		pDist,		//レイの長さ(当たった場合その場所との距離を格納)
		int*		pMaterial,	//レイが当たった場合そのポリゴンの材質番号を格納する
		RayType		type		//レイのタイプ(処理を分ける可能性があるため)
		);

private:
	typedef std::map<CollisionBase*, CollisionBase*> CollisionMap;
	friend class CollisionBase;

	static CollisionManager*	m_pInstance;
	CollisionMap				m_CollisionMap;

	bool Add(CollisionBase* pIn);
	bool Erace(CollisionBase* pIn);
};

#define DefCollisionMgr (CollisionManager::GetInstance())

#endif