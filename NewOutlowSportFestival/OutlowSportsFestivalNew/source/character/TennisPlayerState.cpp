#include "TennisPlayerState.h"
#include "../system/GameController.h"
#include "CharacterFunction.h"

void TennisState_PlayerControll_Move::Enter(TennisPlayer* t)
{
	CharacterUsualMove::Params p;

	p.Acceleration = 0.005f;
	p.MaxSpeed = 0.01f;
	p.TurnSpeed = 0.2f;

	m_pMoveClass = new CharacterUsualMove(t, p);
}


void TennisState_PlayerControll_Move::Execute(TennisPlayer* t)
{
	Vector2 st = controller::GetStickValue(controller::stick::left, t->m_PlayerInfo.number);
	MyDebugString("x=%f y=%f \n", st.x, st.y);
	m_pMoveClass->SetStickValue(st);
	m_pMoveClass->Update();
	chr_func::CreateTransMatrix(t, 0.1f, &t->m_Renderer.m_TransMatrix);
}

void TennisState_PlayerControll_Move::Exit(TennisPlayer* t)
{
	delete m_pMoveClass;
}
