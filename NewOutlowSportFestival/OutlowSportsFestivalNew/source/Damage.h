#ifndef __DAMAGE_H__
#define __DAMAGE_H__

#include "iextreme.h"
#include "ForwardDecl.h"
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


//�_���[�W�N���X(�R���X�g���N�^�E�f�X�g���N�^�Ŏ����I�ɓo�^�E�폜������)
class DamageBase
{
public:
	enum Type
	{
		_WeekDamage,	//���݂݂̂̃_���[�W
		_VanishDamage,	//������у_���[�W
		_UpDamage,		//��ɐ������(�o���[�Ƃ�)�ǌ��\
	};

	LpCharacter		pParent;	//���̃_���[�W����̌��̃L�����N�^
	LpBallBase		pBall;		//���̔���ɂ��Ă���{�[��(�{�[���łȂ����null)
	Type			type;		//���̃_���[�W�̃^�C�v
	float			Value;		//�l
	Vector3			vec;		//�Ђ�ޕ����x�N�g��

	DamageBase();
	virtual ~DamageBase();
	virtual bool HitCheckSphere(const ShpereParam* sp) = 0;
};


//�_���[�W�N���X(��)
class DamageShpere :public DamageBase
{
public:
	bool			m_Enable;	//���̃_���[�W���L�����ǂ���
	ShpereParam		m_Param;	//���̃_���[�W�̋��̍\����
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

	//�����蔻������̃f���Q�[�^�[
	class HitEventBase
	{
	public:
		virtual ~HitEventBase(){}
		virtual void Hit(DamageBase* pDmg) = 0;	//�����������ɌĂ΂��֐�
	};

	//���̃_���[�W������Ƃ�
	void HitCheckSphere(
		const ShpereParam&	sp,
		HitEventBase&		HitEvent
		);

private:
	typedef std::map<DamageBase*, DamageBase*> DamageBaseMap;
	
	static DamageManager*	m_pInstance;
	DamageBaseMap			m_DamageBaseMap;
	
	DamageManager();
	~DamageManager();

	bool AddDamage(DamageBase* pDmg);
	bool EraceDamage(DamageBase* pDmg);
};


#define DefDamageMgr (DamageManager::GetInstance());

#endif