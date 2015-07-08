#ifndef __BASEBALL_PLAYER_STATE_DAMAGEMOTION_WEAK_H__
#define __BASEBALL_PLAYER_STATE_DAMAGEMOTION_WEAK_H__

#include "BaseballPlayer.h"
#include "../CharacterDamageMotion.h"

//***************************************************
//		�e�j�X�L�����N�^�̎�Ђ�݃X�e�[�g
//***************************************************
class BaseballState_DamageMotion_Weak : public BaseballState
{
public:
	BaseballState_DamageMotion_Weak(
		BaseballPlayer*  m_pBaseball,
		const Vector3& Damage_vec  //�_���[�W���󂯂�����
		);

	// �X�e�[�g�J�n
	void Enter(BaseballPlayer* t)override;

	// �X�e�[�g���s
	void Execute(BaseballPlayer* t)override;

	// �X�e�[�g�I��
	void Exit(BaseballPlayer* t)override;

private:
	CharacterDamageMotion*   m_pDamageMotionClass;	//�Ђ�ݍX�V�N���X
	BaseballPlayer*          m_pBaseball;
	Vector3                  m_Damage_vec;
};

#endif