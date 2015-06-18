#ifndef __CHARACTER_MOVE_CLASS_H__
#define __CHARACTER_MOVE_CLASS_H__

class CharacterBase;

#include "iextreme.h"
#include "../Damage/Damage.h"


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
		float DownSpeed;	//�������鑬�x
		float MaxSpeed;		//�ő呬�x
		float TurnSpeed;	//�p�x�ω��X�s�[�h
	};

	class MoveEvent
	{
	public:
		virtual~MoveEvent(){}
		virtual void Update(bool isRun,RATIO speed_ratio) = 0;	//���t���[�����s�����֐�
		virtual void RunStart() = 0;			//����J�n���ɌĂ΂��֐�
		virtual void StandStart() = 0;			//�_�����J�n���ɌĂ΂��֐�
	};

	CharacterUsualMove(
		CharacterBase*					pParent,	//����L�����N�^�̃|�C���^
		const Params&					param,		//�ړ��p�����[�^�\����
		MoveEvent*						pMoveEvent,	//�ړ��C�x���g�ɔ�������N���X
		DamageManager::HitEventBase*	pHitEventBase//�_���[�W���󂯂����ɔ�������N���X
		);

	~CharacterUsualMove();

	void Update();	//�X�V
	void SetStickValue(CrVector2 StickValue);
private:
	typedef DamageManager::HitEventBase HitEventBase;

	CharacterBase*	m_pParent;
	MoveEvent*		m_pMoveEvent;
	HitEventBase*	m_pHitEventBase;
	Params			m_Params;
	Vector2			m_StickValue;
	bool			m_isRun;
};

#endif