#ifndef __CHARACTER_MOVE_CLASS_H__
#define __CHARACTER_MOVE_CLASS_H__

class CharacterBase;

#include "iextreme.h"

//****************************************************************
//		�L�����N�^���ʂ̓����N���X
//****************************************************************


//�ʏ�ړ��N���X
class CharacterUsualMove
{
public:
	struct Params
	{
		float Acceleration;	//�����x
		float MaxSpeed;		//�ő呬�x
		float TurnSpeed;	//�p�x�ω��X�s�[�h
	};

	CharacterUsualMove(
		CharacterBase* pParent,	//����L�����N�^�̃|�C���^
		const Params& param);

	void Update();	//�X�V
	void SetStickValue(CrVector2 StickValue);

private:
	CharacterBase*	pParent;
	Params			m_Params;
	Vector2			m_StickValue;
};

#endif