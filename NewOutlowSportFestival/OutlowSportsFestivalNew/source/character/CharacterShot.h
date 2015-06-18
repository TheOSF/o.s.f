#ifndef __CHARACTER_SHOT_H__
#define __CHARACTER_SHOT_H__


class CharacterBase;

#include "iextreme.h"

//****************************************************************
//		�L�����N�^���ʂ̋ʂ𔭎˂���N���X
//****************************************************************


//�ʂ𔭎˂���N���X
class CharacterShot
{
public:
	struct Params
	{
		int shot_frame;
		
	};

	class ShotEvent
	{
	public:
		virtual~ShotEvent(){}
		virtual void Update() = 0;	//���t���[�����s�����֐�
	};

	CharacterShot(
		CharacterBase*	pParent,	//����L�����N�^�̃|�C���^
		const Params&	param,		//�s���p�����[�^
		ShotEvent*		pMoveEvent	//�ړ��C�x���g�N���X
		);

	void Update();	//�X�V
private:

};

#endif 