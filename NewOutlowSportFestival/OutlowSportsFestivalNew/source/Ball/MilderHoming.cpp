#include "MilderHoming.h"
#include "../character/CharacterBase.h"
#include "../Render/MeshRenderer.h"


MilderHoming::MilderHoming(
	BaseballPlayer*		b,
	BallBase::Params	params,			//�{�[���p�����[�^
	Vector3		        t,				//�{�[���^�[�Q�b�g
	DamageBase::Type	damage_type,	//�_���[�W����̃^�C�v
	float				damage_val		//�_���[�W��
	) :
	m_FreezeCount(0),
	m_FreezeDeleteFrame(60),
	pBaseball(b)
{

	LPIEXMESH		pBallMesh;

	//�p�����[�^���
	m_BallBase.m_Params = params;
	//�^�[�Q�b�g���
	target = t;

	//�_���[�W����̃p�����[�^����
	m_Damage.pBall = &m_BallBase;
	m_Damage.pParent = params.pParent;
	m_Damage.m_Param.size = 1;	//�傫���̓{�[���ɂ���ĈقȂ�\��������
	m_Damage.type = damage_type;
	m_Damage.Value = damage_val;
	UpdateDamageClass();

	//�@�{�[����params�ۑ�
	//pBaseball->setBallParams(params);
	////�@�{�[����target�ۑ�
	//pBaseball->setBallTarget(t);

	//�{�[���̃��b�V�����쐬
	GetBallMesh(params.pParent->m_PlayerInfo.chr_type, &pBallMesh);

	//���b�V���̃����_���[�쐬(�ŏI�I�Ƀ��b�V�����g���܂킵�ĕ`�悷��ׂ�)
	m_pMeshRenderer = new MeshRenderer(
		pBallMesh,
		true
		);

	D3DXQuaternionIdentity(&m_Ballrot);
}

MilderHoming::~MilderHoming()
{
	delete	m_pMeshRenderer;
}

bool MilderHoming::GetBallMesh(
	CharacterType::Value	type,
	LPIEXMESH*				ppOut)
{
	*ppOut = nullptr;

	switch (type)
	{
	
	case CharacterType::_Baseball:
		*ppOut = new iexMesh("DATA\\CHR\\golf_ball\\golf_ball.imo");
		break;
	case CharacterType::_Americanfootball:
		*ppOut = new iexMesh("DATA\\CHR\\Soccer_ball\\soccer_ball.imo");
		break;
	default:
		break;
	}

	return (*ppOut != nullptr);
}


bool MilderHoming::Update()
{
	m_BallBase.m_Params=pBaseball->TargetDecision(m_BallBase.m_Params, target);

	m_BallBase.m_Params.pos += m_BallBase.m_Params.move;

	if (isOutofField())
	{
		m_FreezeCount = m_FreezeDeleteFrame;
	}

	UpdateMesh();
	UpdateDamageClass();

	return m_FreezeCount < m_FreezeDeleteFrame;
}


bool MilderHoming::Msg(MsgType mt)
{

	return false;
}


bool MilderHoming::isOutofField()const
{
	return Vector3Length(m_BallBase.m_Params.pos) > 100;
}


void MilderHoming::UpdateDamageClass()
{
	m_Damage.vec = m_BallBase.m_Params.move;
	m_Damage.m_Param.pos = m_BallBase.m_Params.pos;
}

void MilderHoming::UpdateMesh()
{
	//���b�V���̃��[���h�ϊ��s����X�V����

	Matrix m;

	D3DXMatrixScaling(&m, 0.009f, 0.009f, 0.009f);	//�傫���̓{�[���ɂ���ĕς���K�v������

	m._41 = m_BallBase.m_Params.pos.x;
	m._42 = m_BallBase.m_Params.pos.y;
	m._43 = m_BallBase.m_Params.pos.z;

	m_pMeshRenderer->SetMatrix(m);
}