#ifndef __CHARACTER_SLIDING_CLASS_H__
#define __CHARACTER_SLIDING_CLASS_H__

class CharacterBase;

#include "iextreme.h"

//****************************************************************
//		�L�����N�^���ʂ̓����N���X
//****************************************************************


//�ʏ�ړ��N���X
class CharacterSliding
{
public:
	struct Params
	{
		float Acceleration;	//�����x
		float DownSpeed;	//�������鑬�x
		float MaxSpeed;		//�ő呬�x
		float TurnSpeed;	//�p�x�ω��X�s�[�h
	};

	class MoveEvent
	{
	public:
		virtual~MoveEvent(){}
		virtual void Update(bool isRun, RATIO speed_ratio) = 0;	//���t���[�����s�����֐�
		virtual void RunStart() = 0;			//����J�n���ɌĂ΂��֐�
		virtual void StandStart() = 0;			//�_�����J�n���ɌĂ΂��֐�
	};

	CharacterSliding(
		CharacterBase*	pParent,	//����L�����N�^�̃|�C���^
		const Params&	param,
		MoveEvent*		pMoveEvent);

	void Update();	//�X�V
	void SetStickValue(CrVector2 StickValue);
private:
	CharacterBase*	m_pParent;
	MoveEvent*		m_pMoveEvent;
	Params			m_Params;
	Vector2			m_StickValue;
	bool			m_isRun;
};

#endif