#ifndef __MESH_COLLIDER_H__
#define __MESH_COLLIDER_H__

#include "Collision.h"


//************************************************************
//	���b�V���̂����蔻��N���X
//************************************************************
class MeshCollider :public CollisionBase
{
public:
	class HitEvent
	{
	public:
		virtual void Hit(
			CrVector3	hit_pos,
			int			hit_material) = 0;
	};

	MeshCollider(
		LPIEXMESH		pMesh,		//�f�X�g���N�^��delete���Ȃ�
		HitEvent*		pHitEvent	//�f�X�g���N�^��delete����
		);
	~MeshCollider();

	bool RayPick(
		LPVECTOR3	pOut,		//���C�����������ꍇ���̏ꏊ���i�[����
		LPVECTOR3	pPos,		//���C��ł��n�߂�ꏊ
		LPVECTOR3	pVec,		//���C��ł���
		float*		pDist,		//���C�̒���
		int*		pMaterial,	//���C�����������ꍇ���̃|���S���̍ގ��ԍ����i�[����
		RayType		type		//���C�̃^�C�v(�����𕪂���\�������邽��)
		);

	void Hit(
		CrVector3	hit_pos,
		int			hit_material
		);
private:
	LPIEXMESH		m_pMesh;
	HitEvent*		m_pHitEvent;
};

#endif