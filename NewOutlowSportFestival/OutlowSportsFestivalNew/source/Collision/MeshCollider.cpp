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
	LPVECTOR3	pOut,		//���C�����������ꍇ���̏ꏊ���i�[����
	LPVECTOR3	pPos,		//���C��ł��n�߂�ꏊ
	LPVECTOR3	pVec,		//���C��ł���
	float*		pDist,		//���C�̒���
	int*		pMaterial,	//���C�����������ꍇ���̃|���S���̍ގ��ԍ����i�[����
	RayType		type		//���C�̃^�C�v(�����𕪂���\�������邽��)
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