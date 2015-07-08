#ifndef __CHARACTER_FUNCTION_H__
#define __CHARACTER_FUNCTION_H__

#include "iextreme.h"
#include "../GameSystem/ForwardDecl.h"
#include "../Damage/Damage.h"

class CharacterBase;

//�L�����N�^�p�֐��W

namespace chr_func
{
	//���W�Ɉړ��ʂ��X�V����
	void PositionUpdate(CharacterBase* p);
			
	//�w�y���ňړ��ʂ𑫂�(max_speed�𒴂��Ȃ��悤�ɐݒ肳���)
	void AddXZMove(CharacterBase*p, float x, float z, float max_speed);

	//�O�����Ɉړ��ʂ��^�X
	void AddMoveFront(CharacterBase*p, float speed, float max_speed);

	//���X�Ɍ�������(t���P�ɂ���ƈ�u�Ŏ~�܂�,0�Ō��ʂȂ�)
	void XZMoveDown(CharacterBase*p, float t);

	//�w�y�����̈ړ��ʂ�max_speed�𒴂��Ă�����Amax_speed�ɐݒ肷��
	void SetMaxXZspeed(CharacterBase*p, float max_speed);

	//�w�肵���ꏊ�Ɍ���
	void AngleControll(CharacterBase* p, CrVector3 view_pos, float speed);

	//�w�肵���ꏊ�Ɍ���(��u��)
	void AngleControll(CharacterBase* p, CrVector3 view_pos);

	//���݂̈ʒu�A���݂�angle�AScale�����Ƃɕϊ��s��𐶐�����
	void CreateTransMatrix(CharacterBase* p, float Scale, Matrix* pOutMatrix);

	//�O�����x�N�g���𓾂�
	void GetFront(CharacterBase* p, Vector3* pOut);

	//�L�����N�^������ł��邩�ǂ���
	bool isDie(CharacterBase* p);

	//�_���[�W������Ƃ�
	void DamageCheck(
		LpCharacterBase					pCharacter,	//������Ƃ�L�����N�^
		DamageManager::HitEventBase*	pHitEvent	//�C�x���g����
		);
}

#endif