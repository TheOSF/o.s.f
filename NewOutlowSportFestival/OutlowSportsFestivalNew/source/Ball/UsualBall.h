#ifndef __USUAL_BALL_H__
#define __USUAL_BALL_H__

#include "Ball.h"
#include "../GameSystem/GameObject.h"
#include "../GameSystem/ForwardDecl.h"
#include "../GameSystem/GameSystem.h"
#include "../Damage/Damage.h"

//*****************************************************
//		通常玉クラス
//*****************************************************

class UsualBall :public GameObjectBase
{
public:
	//コンストラクタ
	UsualBall(
		BallBase::Params	params,			//ボールパラメータ
		DamageBase::Type	damage_type,	//ダメージ判定のタイプ
		float				damage_val		//ダメージ量
		);
	~UsualBall();

	//ボールのメッシュを返すファクトリー関数
	static bool GetBallMesh(
		CharacterType::Value	type,	//ボールのキャラクタタイプ
		LPIEXMESH*				ppOut	//戻り値
		);

	bool Update();
	bool Msg(MsgType mt);

private:
	BallBase			m_BallBase;
	LpMeshRenderer		m_pMeshRenderer;
	DamageShpere		m_Damage;
	const int			m_FreezeDeleteFrame;
	int					m_FreezeCount;
	D3DXQUATERNION		m_Ballrot;

	bool isOutofField()const;
	void UpdateMesh();
};

#endif