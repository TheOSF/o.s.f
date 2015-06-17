#include "SoccerPlayerState.h"
#include "../system/GameController.h"
#include "CharacterFunction.h"
#include "CharacterBase.h"

void SoccerState_PlayerControll_Move::Enter(SoccerPlayer* s)
{
	class SoccerMoveEvent :public CharacterUsualMove::MoveEvent
	{
		SoccerPlayer* m_pSoccer;
	public:
		SoccerMoveEvent(SoccerPlayer* pSoccer) :
			m_pSoccer(pSoccer){}

		void Update(bool isRun, RATIO speed_ratio)
		{
			m_pSoccer->m_Renderer.Update(1);
		}

		void RunStart()
		{
			m_pSoccer->m_Renderer.SetMotion(SoccerPlayer::_ms_Run);
		}

		void StandStart()
		{
			m_pSoccer->m_Renderer.SetMotion(SoccerPlayer::_ms_Stand);
		}
	};

	CharacterUsualMove::Params p;

	p.Acceleration = 0.2f;
	p.MaxSpeed = 0.2f;
	p.TurnSpeed = 0.3f;
	p.DownSpeed = 0.2f;

	m_pMoveClass = new CharacterUsualMove(s, p, new SoccerMoveEvent(s));
}
void SoccerState_PlayerControll_Move::Execute(SoccerPlayer* s)
{
	Vector2 st = controller::GetStickValue(controller::stick::left, s->m_PlayerInfo.number);

	if (KEY_Get(KEY_A, 1))
	{
		s->SetState(new SoccerState_PlayerControll_Sliding);
	}
	if (KEY_Get(KEY_B, 1))
	{
		s->SetState(new SoccerState_PlayerControll_Attack);
	}

	m_pMoveClass->SetStickValue(st);
	m_pMoveClass->Update();

	chr_func::CreateTransMatrix(s, 0.05f, &s->m_Renderer.m_TransMatrix);
}
void SoccerState_PlayerControll_Move::Exit(SoccerPlayer* s)
{
	delete m_pMoveClass;
}
void SoccerState_PlayerControll_Sliding::Enter(SoccerPlayer* s)
{
	class SoccerMoveEvent :public CharacterSliding::MoveEvent
	{
		SoccerPlayer* m_pSoccer;
	public:
		SoccerMoveEvent(SoccerPlayer* pSoccer) :
			m_pSoccer(pSoccer){}

		void Update(bool isRun, RATIO speed_ratio)
		{
			m_pSoccer->m_Renderer.Update(1);
		}

		void RunStart()
		{
			m_pSoccer->m_Renderer.SetMotion(SoccerPlayer::_ms_Rolling);
		}

		void StandStart()
		{
			m_pSoccer->m_Renderer.SetMotion(SoccerPlayer::_ms_Stand);
		}
	};
	CharacterSliding::Params p;
	

	p.Acceleration = 0.2f;
	p.MaxSpeed = 0.2f;
	p.TurnSpeed = 0.3f;
	p.DownSpeed = 0.2f;

	m_pMoveClass = new CharacterSliding(s, p, new SoccerMoveEvent(s));
	

}
void SoccerState_PlayerControll_Sliding::Execute(SoccerPlayer* s)
{
	timer++;
	Vector2 st = controller::GetStickValue(controller::stick::left, s->m_PlayerInfo.number);

	//m_pMoveClass->SetStickValue(st);
	//chr_func::AddMoveFront(s, 0.4f, 0.5f);
	m_pMoveClass->Update();

	chr_func::CreateTransMatrix(s, 0.05f, &s->m_Renderer.m_TransMatrix);
	if (timer > 48)
	{
		s->SetState(new SoccerState_PlayerControll_Move);
	}
}
void SoccerState_PlayerControll_Sliding::Exit(SoccerPlayer* s)
{

	delete m_pMoveClass;
}
void SoccerState_PlayerControll_Attack::Enter(SoccerPlayer* s)
{
	class SoccerMoveEvent :public CharacterAttack_A::MoveEvent
	{
		SoccerPlayer* m_pSoccer;
	public:
		SoccerMoveEvent(SoccerPlayer* pSoccer) :
			m_pSoccer(pSoccer){}

		void Update(bool isRun, RATIO speed_ratio)
		{
			m_pSoccer->m_Renderer.Update(1);
		}

		void RunStart()
		{
			m_pSoccer->m_Renderer.SetMotion(SoccerPlayer::_ms_Atk1);
		}

		void StandStart()
		{
			m_pSoccer->m_Renderer.SetMotion(SoccerPlayer::_ms_Stand);
		}
	};
	CharacterAttack_A::Params p;


	p.Acceleration = 0.0f;
	p.MaxSpeed = 0.0f;
	p.TurnSpeed = 0.1f;
	p.DownSpeed = 0.2f;

	m_pMoveClass = new CharacterAttack_A(s, p, new SoccerMoveEvent(s));
}
void SoccerState_PlayerControll_Attack::Execute(SoccerPlayer* s)
{
	timer++;
	Vector2 st = controller::GetStickValue(controller::stick::left, s->m_PlayerInfo.number);

	m_pMoveClass->SetStickValue(st);
	//chr_func::AddMoveFront(s, 0.4f, 0.5f);
	m_pMoveClass->Update();

	chr_func::CreateTransMatrix(s, 0.05f, &s->m_Renderer.m_TransMatrix);
	if (timer > 20 && timer < 46 && KEY_Get(KEY_B, 1))
	{
		s->SetState(new SoccerState_PlayerControll_AttackCombo);
	}
	else if (timer > 46)
	{
		s->SetState(new SoccerState_PlayerControll_Move);
	}

}
void SoccerState_PlayerControll_Attack::Exit(SoccerPlayer* s)
{
	delete m_pMoveClass;
}
void SoccerState_PlayerControll_AttackCombo::Enter(SoccerPlayer* s)
{
	class SoccerMoveEvent :public CharacterAttack_A::MoveEvent
	{
		SoccerPlayer* m_pSoccer;
	public:
		SoccerMoveEvent(SoccerPlayer* pSoccer) :
			m_pSoccer(pSoccer){}

		void Update(bool isRun, RATIO speed_ratio)
		{
			m_pSoccer->m_Renderer.Update(1);
		}

		void RunStart()
		{
			m_pSoccer->m_Renderer.SetMotion(SoccerPlayer::_ms_Atk2);
		}

		void StandStart()
		{
			m_pSoccer->m_Renderer.SetMotion(SoccerPlayer::_ms_Stand);
		}
	};
	CharacterAttack_A::Params p;
	timer = 0;

	p.Acceleration = 0.0f;
	p.MaxSpeed = 0.0f;
	p.TurnSpeed = 0.1f;
	p.DownSpeed = 0.2f;

	m_pMoveClass = new CharacterAttack_A(s, p, new SoccerMoveEvent(s));
}
void SoccerState_PlayerControll_AttackCombo::Execute(SoccerPlayer* s)
{
	timer++;
	Vector2 st = controller::GetStickValue(controller::stick::left, s->m_PlayerInfo.number);

	m_pMoveClass->SetStickValue(st);
	m_pMoveClass->Update();

	chr_func::CreateTransMatrix(s, 0.05f, &s->m_Renderer.m_TransMatrix);
	if (timer > 20 && timer < 46 && KEY_Get(KEY_B, 1))
	{
		s->SetState(new SoccerState_PlayerControll_AttackFinish);
	}
	else if (timer > 46)
	{
		s->SetState(new SoccerState_PlayerControll_Move);
	}

}
void SoccerState_PlayerControll_AttackCombo::Exit(SoccerPlayer* s)
{
	delete m_pMoveClass;
}
void SoccerState_PlayerControll_AttackFinish::Enter(SoccerPlayer* s)
{
	class SoccerMoveEvent :public CharacterAttack_A::MoveEvent
	{
		SoccerPlayer* m_pSoccer;
	public:
		SoccerMoveEvent(SoccerPlayer* pSoccer) :
			m_pSoccer(pSoccer){}

		void Update(bool isRun, RATIO speed_ratio)
		{
			m_pSoccer->m_Renderer.Update(1);
		}

		void RunStart()
		{
			m_pSoccer->m_Renderer.SetMotion(SoccerPlayer::_ms_Atk3);
		}

		void StandStart()
		{
			m_pSoccer->m_Renderer.SetMotion(SoccerPlayer::_ms_Stand);
		}
	};
	CharacterAttack_A::Params p;
	timer = 0;

	p.Acceleration = 0.0f;
	p.MaxSpeed = 0.0f;
	p.TurnSpeed = 0.1f;
	p.DownSpeed = 0.2f;

	m_pMoveClass = new CharacterAttack_A(s, p, new SoccerMoveEvent(s));
}
void SoccerState_PlayerControll_AttackFinish::Execute(SoccerPlayer* s)
{
	timer++;
	Vector2 st = controller::GetStickValue(controller::stick::left, s->m_PlayerInfo.number);

	m_pMoveClass->SetStickValue(st);
	//chr_func::AddMoveFront(s, 0.4f, 0.5f);
	m_pMoveClass->Update();

	chr_func::CreateTransMatrix(s, 0.05f, &s->m_Renderer.m_TransMatrix);
	if (timer > 50)
	{
		s->SetState(new SoccerState_PlayerControll_Move);
	}

}
void SoccerState_PlayerControll_AttackFinish::Exit(SoccerPlayer* s)
{
	delete m_pMoveClass;
}