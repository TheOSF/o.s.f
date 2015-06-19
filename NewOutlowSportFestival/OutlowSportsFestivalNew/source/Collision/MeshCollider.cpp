#include "MeshCollider.h"

MeshCollider::MeshCollider(
	LPIEXMESH		pMesh,
	HitEvent*		pHitEvent
	):
	m_pMesh(pMesh),
	m_pHitEvent(pHitEvent)
{

}

MeshCollider::~MeshCollider()
{
	delete m_pHitEvent;
}

bool MeshCollider::RayPick(
	LPVECTOR3	pOut,		//レイが当たった場合その場所を格納する
	LPVECTOR3	pPos,		//レイを打ち始める場所
	LPVECTOR3	pVec,		//レイを打つ方向
	float*		pDist,		//レイの長さ
	int*		pMaterial,	//レイが当たった場合そのポリゴンの材質番号を格納する
	RayType		type		//レイのタイプ(処理を分ける可能性があるため)
	)
{
	*pMaterial = 0;

	return m_pMesh->RayPickPlus(
		pOut,
		pPos,
		pVec,
		pDist
		) >= 0;
}

void MeshCollider::Hit(
	CrVector3	hit_pos,
	int			hit_material
	)
{
	m_pHitEvent->Hit(hit_pos, hit_material);
}