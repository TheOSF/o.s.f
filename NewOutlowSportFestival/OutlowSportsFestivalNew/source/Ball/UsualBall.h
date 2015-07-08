#ifndef __USUAL_BALL_H__
#define __USUAL_BALL_H__

#include "Ball.h"
#include "../GameSystem/GameObject.h"
#include "../GameSystem/ForwardDecl.h"
#include "../GameSystem/GameSystem.h"
#include "../Damage/Damage.h"

//*****************************************************
//		�ʏ�ʃN���X
//*****************************************************

class UsualBall :public GameObjectBase
{
public:
	//�R���X�g���N�^
	UsualBall(
		BallBase::Params	params,			//�{�[���p�����[�^
		DamageBase::Type	damage_type,	//�_���[�W����̃^�C�v
		float				damage_val		//�_���[�W��
		);
	~UsualBall();

	//�{�[���̃��b�V����Ԃ��t�@�N�g���[�֐�
	static bool GetBallMesh(
		CharacterType::Value	type,	//�{�[���̃L�����N�^�^�C�v
		LPIEXMESH*				ppOut	//�߂�l
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
	void UpdateDamageClass();
	void UpdateMesh();
};

#endif