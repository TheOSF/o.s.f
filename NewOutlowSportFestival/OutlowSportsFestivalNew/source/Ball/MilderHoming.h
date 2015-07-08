#ifndef __MILDERHOMIG_H__
#define __MILDERHOMIG_H__

#include "Ball.h"
#include "../GameSystem/GameObject.h"
#include "../GameSystem/ForwardDecl.h"
#include "../GameSystem/GameSystem.h"
#include "../Damage/Damage.h"

#include "../character/Baseball/BaseballPlayer.h"

//*****************************************************
//		通常玉クラス
//*****************************************************

class MilderHoming :public GameObjectBase
{
private:
	
	
public:
	BaseballPlayer* pBaseball;
	Vector3 target;
public:
	//コンストラクタ
	MilderHoming(
		BaseballPlayer*		b,
		BallBase::Params	params,			//ボールパラメータ
		Vector3		        t,				//ボールターゲット
		DamageBase::Type	damage_type,	//ダメージ判定のタイプ
		float				damage_val		//ダメージ量
		);
	~MilderHoming();

	//ボールのメッシュを返すファクトリー関数
	static bool GetBallMesh(
		CharacterType::Value	type,	//ボールのキャラクタタイプ
		LPIEXMESH*				ppOut	//戻り値
		);

	bool Update();
	bool Msg(MsgType mt);
	//　セッター
	void setBallParamPos(BallBase::Params p){ m_BallBase.m_Params = p; }
private:
	BallBase			m_BallBase;
	LpMeshRenderer		m_pMeshRenderer;
	DamageShpere		m_Damage;
	const int			m_FreezeDeleteFrame;
	int					m_FreezeCount;
	D3DXQUATERNION		m_Ballrot;

	bool isOutofField()const;
	void UpdateDamageClass();
	void UpdateMesh();

};

#endif