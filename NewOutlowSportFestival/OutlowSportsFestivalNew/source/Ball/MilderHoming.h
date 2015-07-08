#ifndef __MILDERHOMIG_H__
#define __MILDERHOMIG_H__

#include "Ball.h"
#include "../GameSystem/GameObject.h"
#include "../GameSystem/ForwardDecl.h"
#include "../GameSystem/GameSystem.h"
#include "../Damage/Damage.h"

#include "../character/Baseball/BaseballPlayer.h"

//*****************************************************
//		�ʏ�ʃN���X
//*****************************************************

class MilderHoming :public GameObjectBase
{
private:
	
	
public:
	BaseballPlayer* pBaseball;
	Vector3 target;
public:
	//�R���X�g���N�^
	MilderHoming(
		BaseballPlayer*		b,
		BallBase::Params	params,			//�{�[���p�����[�^
		Vector3		        t,				//�{�[���^�[�Q�b�g
		DamageBase::Type	damage_type,	//�_���[�W����̃^�C�v
		float				damage_val		//�_���[�W��
		);
	~MilderHoming();

	//�{�[���̃��b�V����Ԃ��t�@�N�g���[�֐�
	static bool GetBallMesh(
		CharacterType::Value	type,	//�{�[���̃L�����N�^�^�C�v
		LPIEXMESH*				ppOut	//�߂�l
		);

	bool Update();
	bool Msg(MsgType mt);
	//�@�Z�b�^�[
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