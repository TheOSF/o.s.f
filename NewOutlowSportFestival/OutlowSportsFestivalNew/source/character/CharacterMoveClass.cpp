#include "CharacterMoveClass.h"
#include "CharacterFunction.h"
#include "CharacterBase.h"
#include "../Damage/Damage.h"
#include "../Ball/Ball.h"
#include "../Camera/Camera.h"

//****************************************************************
//		�L�����N�^���ʂ̓����N���X
//****************************************************************

CharacterUsualMove::CharacterUsualMove(
	CharacterBase*					pParent,	//����L�����N�^�̃|�C���^
	const Params&					param,		//�ړ��p�����[�^�\����
	MoveEvent*						pMoveEvent,	//�ړ��C�x���g�ɔ�������N���X
	DamageManager::HitEventBase*	pHitEventBase//�_���[�W���󂯂����ɔ�������N���X
	) :
	m_StickValue(0, 0),
	m_pParent(pParent),
	m_isRun(false),
	m_pMoveEvent(pMoveEvent),
	m_pHitEventBase(pHitEventBase)
{
	m_Params = param;
}

CharacterUsualMove:: ~CharacterUsualMove()
{
	delete m_pMoveEvent;
	delete m_pHitEventBase;
}

void CharacterUsualMove::Update()
{
	//�����Ă��邩�ǂ���
	bool now = Vector2Length(m_StickValue) > 0.1f;

	//�C�x���g�N���X�̍X�V
	m_pMoveEvent->Update(now, (m_Params.MaxSpeed > 0.0f) ? (Vector3XZLength(m_pParent->m_Params.move) / m_Params.MaxSpeed) : (0));

	//�����Ă���or���Ȃ������̎��s
	if (now)
	{
		//�O�ɉ������A�������X�e�B�b�N�̌�����
		chr_func::AddMoveFront(m_pParent, m_Params.Acceleration, m_Params.MaxSpeed);
		
		chr_func::AngleControll(
			m_pParent,
			m_pParent->m_Params.pos + DefCamera.GetRight()*m_StickValue.x + DefCamera.GetForward()*m_StickValue.y, 
			m_Params.TurnSpeed
			);
	}
	else
	{
		//����
		chr_func::XZMoveDown(m_pParent, m_Params.DownSpeed);
	}

	//�C�x���g�N���X�̊֐��̌Ăяo��
	if (now != m_isRun)
	{
		m_isRun = now;
		if (now)
		{
			m_pMoveEvent->RunStart();
		}
		else
		{
			m_pMoveEvent->StandStart();
		}
	}


	//�ʒu�̍X�V
	chr_func::PositionUpdate(m_pParent);

	//�_���[�W������Ƃ�
	chr_func::DamageCheck(m_pParent, m_pHitEventBase);
}

void CharacterUsualMove::SetStickValue(CrVector2 StickValue)
{
	m_StickValue = StickValue;
}