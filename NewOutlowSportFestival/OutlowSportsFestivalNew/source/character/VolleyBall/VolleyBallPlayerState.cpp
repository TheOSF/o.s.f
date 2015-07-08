#include "VolleyBallPlayerState.h"
#include "../../GameSystem/GameController.h"
#include "../CharacterFunction.h"
#include "../CharacterBase.h"

void VolleyBallState_PlayerControll_Move::Enter(VolleyBallPlayer* v)
{
	class VolleyBallMoveEvent : public CharacterUsualMove::MoveEvent
	{
		VolleyBallPlayer* m_pVolley;
	public:
		VolleyBallMoveEvent(VolleyBallPlayer* pVolley)
		{
			m_pVolley = pVolley;
		}
		void Update(bool isRun, RATIO speed_ratio)
		{
			m_pVolley->m_Renderer.Update(1);
		}

		void RunStart()
		{
			m_pVolley->m_Renderer.SetMotion(VolleyBallPlayer::_ms_Run);
		}

		void StandStart()
		{
			m_pVolley->m_Renderer.SetMotion(VolleyBallPlayer::_ms_Stand);
		}

	};
	CharacterUsualMove::Params p;

	p.Acceleration = 0.2f;
	p.MaxSpeed = 0.2f;
	p.TurnSpeed = 0.3f;
	p.DownSpeed = 0.2f;

	m_pMoveClass = new CharacterUsualMove(v, p, new VolleyBallMoveEvent(v), new DamageManager::HitEventBase());
}
void VolleyBallState_PlayerControll_Move::Execute(VolleyBallPlayer* v)
{
	Vector2 st = controller::GetStickValue(controller::stick::left, v->m_PlayerInfo.number);
	// [~] ‚Å ‰ñ”ð
	if (controller::GetTRG(controller::button::batu, v->m_PlayerInfo.number))
	{
		v->SetState(new VolleyBallState_PlayerControll_Avoid);
	}
	m_pMoveClass->SetStickValue(st);
	m_pMoveClass->Update();

	chr_func::CreateTransMatrix(v, 0.05f, &v->m_Renderer.m_TransMatrix);
}
void VolleyBallState_PlayerControll_Move::Exit(VolleyBallPlayer* v)
{
	delete m_pMoveClass;
}
void VolleyBallState_PlayerControll_Avoid::Enter(VolleyBallPlayer* v)
{
	class VolleyBallAvoidEvent : public CharacterEvasion::Event
	{
		VolleyBallPlayer* m_pVolley;
	public:
		VolleyBallAvoidEvent(VolleyBallPlayer* pVolley)
		{
			m_pVolley = pVolley;
		}
		void Update()
		{
			m_pVolley->m_Renderer.Update(1);
		}

		void EvasionStart()
		{
			m_pVolley->m_Renderer.SetMotion(VolleyBallPlayer::_ms_Rolling);
		}

		void EvasionEnd()
		{
			m_pVolley->m_Renderer.SetMotion(VolleyBallPlayer::_ms_Stand);
		}

	};
	CharacterEvasion::EvasionParams p;
	p.AllFrame = 40;
	p.MaxTurnRadian = 0.2f;
	p.MoveDownSpeed = 0.2f;
	p.MoveSpeed = 0.2f;
	p.NoDamageStartFrame = 10;
	p.NoDamageEndFrame = 35;

	m_pAvoidClass = new CharacterEvasion(v, new VolleyBallAvoidEvent(v), p);
	
}
void VolleyBallState_PlayerControll_Avoid::Execute(VolleyBallPlayer* v)
{
	Vector2 st = controller::GetStickValue(controller::stick::left, v->m_PlayerInfo.number);
	m_pAvoidClass->SetStickValue(st);

	if (!m_pAvoidClass->Update())
	{
		v->SetState(new VolleyBallState_PlayerControll_Move);
	}
	chr_func::CreateTransMatrix(v, 0.05f, &v->m_Renderer.m_TransMatrix);
}
void VolleyBallState_PlayerControll_Avoid::Exit(VolleyBallPlayer* v)
{
	delete m_pAvoidClass;
}
void VolleyBallState_PlayerControll_Attack::Enter(VolleyBallPlayer* v)
{

	class VolleyBallAttackEvent :public CharacterNearAttack::AttackEvent
	{
		VolleyBallPlayer* m_pVolley;
		DamageShpere m_damage;
	public:
		VolleyBallAttackEvent(VolleyBallPlayer* pVolley) :
			m_pVolley(pVolley){

			m_damage.pParent = m_pVolley;
			m_damage.pBall = NULL;
			m_damage.type = DamageBase::_WeekDamage;
			m_damage.Value = 20.0f;
			m_damage.m_Enable = false;
		}

		void Update()
		{
			m_pVolley->m_Renderer.Update(1);
		}

		void AttackStart()
		{
			m_pVolley->m_Renderer.SetMotion(VolleyBallPlayer::_ms_Atk1);
		}

		void AttackEnd()
		{
			m_pVolley->m_Renderer.SetMotion(VolleyBallPlayer::_ms_Stand);
		}
		void Assault()
		{
			m_damage.m_Enable = true;
		}
	};



	p.TurnSpeed = 0.1f;
	p.AttackFrame = 15;
	p.EndFrame = 35;
	p.damage = 20;
	p.speed = 0.2f;

	timer = 0;

	m_pAttackClass = new CharacterNearAttack(v, p, new VolleyBallAttackEvent(v));
}