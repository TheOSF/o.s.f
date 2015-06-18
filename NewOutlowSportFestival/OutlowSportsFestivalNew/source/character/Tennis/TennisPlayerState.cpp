#include "TennisPlayerState.h"
#include "../../GameSystem/GameController.h"
#include "../CharacterFunction.h"
#include "../../Ball/UsualBall.h"
#include "../../Damage/Damage.h"


//�X�e�[�g�J�n
void TennisState_PlayerControll_Move::Enter(TennisPlayer* t)
{
	//�ړ��C�x���g�N���X
	class TennisMoveEvent :public CharacterUsualMove::MoveEvent
	{
		TennisPlayer* m_pTennis;
	public:
		TennisMoveEvent(TennisPlayer* pTennis) :
			m_pTennis(pTennis){}
		
		//�A�j���[�V�����̍X�V
		void Update(bool isRun, RATIO speed_ratio)
		{
			m_pTennis->m_Renderer.Update(1);
		}
		//����n�߂Ƀ��[�V�������Z�b�g
		void RunStart()
		{
			m_pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_Run);
		}
		//�����͂��߂Ƀ��[�V�������Z�b�g
		void StandStart()
		{
			m_pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_Stand);
		}
	};

	//�_���[�W�C�x���g�N���X�̍쐬
	class TennisDamageHitEvent :public DamageManager::HitEventBase
	{
		TennisPlayer* m_pTennis;
	public:
		TennisDamageHitEvent(TennisPlayer* pTennis) :
			m_pTennis(pTennis){}

		//�����������ɂ��̃_���[�W�̎�ނ���A���ꂼ��̃X�e�[�g�ɔh��������
		bool Hit(DamageBase* pDmg)
		{
			bool ret = true;

			switch (pDmg->type)
			{
			case DamageBase::Type::_WeekDamage:
				//m_pTennis->SetState();	�X�e�[�g���ł��Ă��Ȃ�����
				break;
			case DamageBase::Type::_VanishDamage:
				//m_pTennis->SetState();
				break;
			case DamageBase::Type::_UpDamage:
				//m_pTennis->SetState();
				break;
			default:
				ret = false;
				break;
			}

			return ret;
		}
	};

	//�ړ��p�����[�^����
	CharacterUsualMove::Params p;

	p.Acceleration = 0.2f;
	p.MaxSpeed = 0.2f;
	p.TurnSpeed = 0.3f;
	p.DownSpeed = 0.2f;

	//�ړ��N���X�̍쐬
	m_pMoveClass = new CharacterUsualMove(
		t,
		p,
		new TennisMoveEvent(t),
		new TennisDamageHitEvent(t)
		);
}


void TennisState_PlayerControll_Move::Execute(TennisPlayer* t)
{
	//�X�e�B�b�N�̒l���擾
	Vector2 st = controller::GetStickValue(controller::stick::left, t->m_PlayerInfo.number);

	//�X�e�B�b�N�̒l�Z�b�g
	m_pMoveClass->SetStickValue(st);

	//�X�V
	m_pMoveClass->Update();

	//���f���̃��[���h�ϊ��s����X�V
	chr_func::CreateTransMatrix(t, 0.05f, &t->m_Renderer.m_TransMatrix);

	//�{�[������(��)
	if (controller::GetTRG(controller::button::sankaku, t->m_PlayerInfo.number))
	{
		BallBase::Params param;

		chr_func::GetFront(t, &param.move);
		param.move *= 0.5f;
		param.pos = t->m_Params.pos;
		param.pParent = t;
		param.type = BallBase::Type::_Usual;

		new UsualBall(param, DamageBase::Type::_WeekDamage, 1);
	}
}

void TennisState_PlayerControll_Move::Exit(TennisPlayer* t)
{
	delete m_pMoveClass;
}
