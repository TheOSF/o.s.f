#ifndef __TENNIS_PLAYER_STATE_DAMAGEMOTION_WEAK_H__
#define __TENNIS_PLAYER_STATE_DAMAGEMOTION_WEAK_H__

#include "TennisPlayer.h"
#include "../CharacterDamageMotion.h"

//***************************************************
//		�e�j�X�L�����N�^�̎�Ђ�݃X�e�[�g
//***************************************************
class TennisState_DamageMotion_Weak : public TennisState
{
public:
	TennisState_DamageMotion_Weak(
		TennisPlayer*  pTennis,
		const Vector3& Damage_vec  //�_���[�W���󂯂�����
		);

	// �X�e�[�g�J�n
	void Enter(TennisPlayer* t)override;

	// �X�e�[�g���s
	void Execute(TennisPlayer* t)override;

	// �X�e�[�g�I��
	void Exit(TennisPlayer* t)override;

private:
	CharacterDamageMotion*   m_pDamageMotionClass;	//�Ђ�ݍX�V�N���X
	TennisPlayer*            m_pTennis;
	Vector3                  m_Damage_vec;
};

#endif