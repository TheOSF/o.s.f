#include "UsualBall.h"
#include "../character/CharacterBase.h"
#include "../Render/MeshRenderer.h"


UsualBall::UsualBall(
	BallBase::Params	params,			//ボールパラメータ
	DamageBase::Type	damage_type,	//ダメージ判定のタイプ
	float				damage_val		//ダメージ量
	) :
	m_FreezeCount(0),
	m_FreezeDeleteFrame(60)
{

	LPIEXMESH		pBallMesh;

	//パラメータ代入
	m_BallBase.m_Params = params;

	//ダメージ判定のパラメータを代入
	m_Damage.pBall = &m_BallBase;
	m_Damage.pParent = params.pParent;
	m_Damage.m_Param.size = 1;	//大きさはボールによって異なる可能性がある
	m_Damage.type = damage_type;
	m_Damage.Value = damage_val;
	UpdateDamageClass();

	//ボールのメッシュを作成
	GetBallMesh(params.pParent->m_PlayerInfo.chr_type, &pBallMesh);

	//メッシュのレンダラー作成(最終的にメッシュを使いまわして描画するべき)
	m_pMeshRenderer = new MeshRenderer(
		pBallMesh,
		true
		);

	D3DXQuaternionIdentity(&m_Ballrot);
}

UsualBall::~UsualBall()
{
	delete	m_pMeshRenderer;
}

bool UsualBall::GetBallMesh(
	CharacterType::Value	type,
	LPIEXMESH*				ppOut)
{
	*ppOut = nullptr;

	switch (type)
	{
	case CharacterType::_Tennis:
		*ppOut = new iexMesh("DATA\\CHR\\Tennis_ball\\Tennis_ball.imo");
		break;
	case CharacterType::_Baseball:
		*ppOut = new iexMesh("DATA\\CHR\\golf_ball\\golf_ball.imo");
		break;
	case CharacterType::_Americanfootball:
		*ppOut = new iexMesh("DATA\\CHR\\Soccer_ball\\soccer_ball.imo");
		break;
	case CharacterType::_Soccer:
		*ppOut = new iexMesh("DATA\\CHR\\Soccer_ball\\soccer_ball.imo");
		break;
	case CharacterType::_Lacrosse:
		*ppOut = new iexMesh("DATA\\CHR\\Tennis_ball\\Tennis_ball.imo");
		break;
	case CharacterType::_Volleyball:
		*ppOut = new iexMesh("DATA\\CHR\\Soccer_ball\\soccer_ball.imo");
	default:
		break;
	}

	return (*ppOut != nullptr);
}


bool UsualBall::Update()
{
	m_BallBase.m_Params.pos += m_BallBase.m_Params.move;

	if (isOutofField())
	{
		m_FreezeCount = m_FreezeDeleteFrame;
	}

	UpdateMesh();
	UpdateDamageClass();

	return m_FreezeCount < m_FreezeDeleteFrame;
}


bool UsualBall::Msg(MsgType mt)
{

	return false;
}


bool UsualBall::isOutofField()const
{
	return Vector3Length(m_BallBase.m_Params.pos) > 100;
}


void UsualBall::UpdateDamageClass()
{
	m_Damage.vec = m_BallBase.m_Params.move;
	m_Damage.m_Param.pos = m_BallBase.m_Params.pos;
}

void UsualBall::UpdateMesh()
{
	//メッシュのワールド変換行列を更新する

	Matrix m;

	D3DXMatrixScaling(&m, 0.01f, 0.01f, 0.01f);	//大きさはボールによって変える必要がある

	m._41 = m_BallBase.m_Params.pos.x;
	m._42 = m_BallBase.m_Params.pos.y;
	m._43 = m_BallBase.m_Params.pos.z;

	m_pMeshRenderer->SetMatrix(m);
}