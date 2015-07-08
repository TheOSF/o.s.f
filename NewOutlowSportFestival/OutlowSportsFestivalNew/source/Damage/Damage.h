#ifndef __DAMAGE_H__
#define __DAMAGE_H__

#include "iextreme.h"
#include "../GameSystem/ForwardDecl.h"
#include <map>

//*************************************************************
//		�_���[�W����N���X�w�b�_
//*************************************************************


//���̍\����
struct ShpereParam
{
	Vector3		pos;
	float		size;
};

//**************************************************************************
//	�_���[�W�N���X(�R���X�g���N�^�E�f�X�g���N�^�Ŏ����I�ɓo�^�E�폜������)
//**************************************************************************
class DamageBase
{
public:
	enum Type
	{
		_WeekDamage,	//���݂݂̂̃_���[�W
		_VanishDamage,	//������у_���[�W
		_UpDamage,		//��ɐ������(�o���[�Ƃ�)�ǌ��\
	};

	LpCharacterBase	pParent;	//���̃_���[�W����̌��̃L�����N�^
	LpBallBase		pBall;		//���̔���ɂ��Ă���{�[��(�{�[���łȂ����null)
	Type			type;		//���̃_���[�W�̃^�C�v
	float			Value;		//�l
	Vector3			vec;		//�Ђ�ޕ����x�N�g��
	int				HitCount;	//����������

	DamageBase();
	virtual ~DamageBase();
	virtual bool HitCheckSphere(const ShpereParam* sp) = 0;

};


//*************************************************************
//	�_���[�W�N���X(��)
//*************************************************************
class DamageShpere :public DamageBase
{
public:
	bool			m_Enable;	//���̃_���[�W���L�����ǂ���
	ShpereParam		m_Param;	//���̃_���[�W�̋��̍\����

	DamageShpere();
private:
	bool HitCheckSphere(const ShpereParam* sp);
};

//*************************************************************
//		�_���[�W����}�l�[�W��
//*************************************************************

class DamageManager
{
public:
	//�C���X�^���X�Q�b�^
	static DamageManager& GetInstance();
	static void Release();

	//�_���[�W�q�b�g���̃C�x���g�N���X
	class HitEventBase
	{
	public:
		virtual ~HitEventBase(){}
		virtual bool Hit(DamageBase* pDmg){ return false; }	//�����������ɌĂ΂��֐�(�߂�l�F�����������ǂ���)
	};

	//���Ń_���[�W������擾����
	void HitCheckSphere(
		const ShpereParam&	sp,
		HitEventBase&		HitEvent
		);

private:
	friend class DamageBase;
	typedef std::map<DamageBase*, DamageBase*> DamageBaseMap;
	
	static DamageManager*	m_pInstance;
	DamageBaseMap			m_DamageBaseMap;
	
	DamageManager();
	~DamageManager();

	bool AddDamage(DamageBase* pDmg);
	bool EraceDamage(DamageBase* pDmg);
};

typedef DamageManager::HitEventBase HitEventBase;

#define DefDamageMgr (DamageManager::GetInstance())

#endif