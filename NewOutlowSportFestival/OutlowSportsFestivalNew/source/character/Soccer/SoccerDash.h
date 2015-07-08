#ifndef __CHARACTER_DASH_CLASS_H__
#define __CHARACTER_DASH_CLASS_H__

#include "iextreme.h"
#include "SoccerPlayer.h"

//****************************************************************
//		�T�b�J�[�̃_�b�V���N���X
//****************************************************************
//�X���C�f�B���O�N���X
class SoccerDash
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
	SoccerDash(CharacterBase*					pParent,	//����L�����N�^�̃|�C���^
		const Params&					param,		//�ړ��p�����[�^�\����
		MoveEvent*						pMoveEvent,	//�ړ��C�x���g�ɔ�������N���X
		DamageManager::HitEventBase*	pHitEventBase//�_���[�W���󂯂����ɔ�������N���X
		);


	~SoccerDash();

	Params Getparams()
	{
		return m_Params;
	}
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