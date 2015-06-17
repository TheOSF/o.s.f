#include "TennisPlayerState.h"
#include "../../GameSystem/GameController.h"
#include "../CharacterFunction.h"
#include "../../Ball/UsualBall.h"
#include "../../Damage/Damage.h"

class TennisUsualMoveDamageEvent :public DamageManager::HitEventBase
{
public:
	TennisUsualMoveDamageEvent(TennisPlayer* t) :
		m_pTennis(t)
	{
	}

	void Hit(DamageBase*	pDmg)
	{
		if (pDmg->pParent != (LpCharacterBase)m_pTennis)
		{
			m_pTennis->m_Params.pos.x -= 0.5f;
		}
	}
private:
	TennisPlayer* m_pTennis;
};

void TennisState_PlayerControll_Move::Enter(TennisPlayer* t)
{
	class TennisMoveEvent :public CharacterUsualMove::MoveEvent
	{
		TennisPlayer* m_pTennis;
	public:
		TennisMoveEvent(TennisPlayer* pTennis) :
			m_pTennis(pTennis){}

		void Update(bool isRun, RATIO speed_ratio)
		{
			m_pTennis->m_Renderer.Update(1);
		}

		void RunStart()
		{
			m_pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_Run);
		}

		void StandStart()
		{
			m_pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_Stand);
		}
	};
	
	CharacterUsualMove::Params p;

	p.Acceleration = 0.2f;
	p.MaxSpeed = 0.2f;
	p.TurnSpeed = 0.3f;
	p.DownSpeed = 0.2f;

	m_pMoveClass = new CharacterUsualMove(t, p, new TennisMoveEvent(t));
}


void TennisState_PlayerControll_Move::Execute(TennisPlayer* t)
{

	Vector2 st = controller::GetStickValue(controller::stick::left, t->m_PlayerInfo.number);
	
	m_pMoveClass->SetStickValue(st);
	m_pMoveClass->Update();

	chr_func::CreateTransMatrix(t, 0.05f, &t->m_Renderer.m_TransMatrix);
	
	ShpereParam sp;
	sp.pos = t->m_Params.pos;
	sp.size = 3;

	TennisUsualMoveDamageEvent damage_event(t);
	DefDamageMgr.HitCheckSphere(sp, damage_event);

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
