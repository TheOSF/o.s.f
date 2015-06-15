#ifndef __DAMAGE_H__
#define __DAMAGE_H__

#include "iextreme.h"
#include "ForwardDecl.h"
#include <map>

//*************************************************************
//		ダメージ判定クラスヘッダ
//*************************************************************


//球の構造体
struct ShpereParam
{
	Vector3		pos;
	float		size;
};


//ダメージクラス(コンストラクタ・デストラクタで自動的に登録・削除をする)
class DamageBase
{
public:
	enum Type
	{
		_WeekDamage,	//怯みのみのダメージ
		_VanishDamage,	//吹き飛びダメージ
		_UpDamage,		//上に吹き飛ぶ(バレーとか)追撃可能
	};

	LpCharacter		pParent;	//このダメージ判定の元のキャラクタ
	LpBallBase		pBall;		//この判定についているボール(ボールでなければnull)
	Type			type;		//このダメージのタイプ
	float			Value;		//値
	Vector3			vec;		//ひるむ方向ベクトル

	DamageBase();
	virtual ~DamageBase();
	virtual bool HitCheckSphere(const ShpereParam* sp) = 0;
};


//ダメージクラス(球)
class DamageShpere :public DamageBase
{
public:
	bool			m_Enable;	//このダメージが有効かどうか
	ShpereParam		m_Param;	//このダメージの球の構造体
private:
	bool HitCheckSphere(const ShpereParam* sp);
};

//*************************************************************
//		ダメージ判定マネージャ
//*************************************************************

class DamageManager
{
public:
	//インスタンスゲッタ
	static DamageManager& GetInstance();
	static void Release();

	//あたり判定条件のデリゲーター
	class HitEventBase
	{
	public:
		virtual ~HitEventBase(){}
		virtual void Hit(DamageBase* pDmg) = 0;	//当たった時に呼ばれる関数
	};

	//球のダメージ判定をとる
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