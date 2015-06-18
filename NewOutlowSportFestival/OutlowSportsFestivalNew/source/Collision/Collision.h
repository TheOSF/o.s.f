#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "iextreme.h"
#include <map>

//*******************************************************
//	�����蔻��I�u�W�F�N�g�x�[�X
//*******************************************************
class CollisionBase
{
public:
	//���C�̃^�C�v
	enum RayType
	{
		_Usual,
	};

	CollisionBase();
	virtual~CollisionBase();

	//���Ƃ̂����蔻��
	virtual bool RayPick(
		LPVECTOR3	pOut,		//���C�����������ꍇ���̏ꏊ���i�[����
		LPVECTOR3	pPos,		//���C��ł��n�߂�ꏊ
		LPVECTOR3	pVec,		//���C��ł���
		float *		pDist,		//���C�̒���
		int*		pMaterial,	//���C�����������ꍇ���̃|���S���̍ގ��ԍ����i�[����
		RayType		type		//���C�̃^�C�v(�����𕪂���\�������邽��)
		) = 0;
	
	//���������Ƃ��̏���
	virtual void Hit(			
		CrVector3	hit_pos,
		int			hit_material
		) = 0;
};


//*******************************************************
//	�����蔻��I�u�W�F�N�g�}�l�[�W��
//*******************************************************
class CollisionManager
{
public:
	typedef CollisionBase::RayType RayType;

	static CollisionManager& GetInstance();
	static void Release();

	//���C�s�b�N
	bool RayPick(
		LPVECTOR3	pOut,		//���C�����������ꍇ���̏ꏊ���i�[����
		LPVECTOR3	pPos,		//���C��ł��n�߂�ꏊ
		LPVECTOR3	pVec,		//���C��ł���
		float *		pDist,		//���C�̒���(���������ꍇ���̏ꏊ�Ƃ̋������i�[)
		int*		pMaterial,	//���C�����������ꍇ���̃|���S���̍ގ��ԍ����i�[����
		RayType		type		//���C�̃^�C�v(�����𕪂���\�������邽��)
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