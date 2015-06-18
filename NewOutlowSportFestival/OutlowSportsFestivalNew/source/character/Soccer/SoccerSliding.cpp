#include "SoccerSliding.h"
#include "../CharacterFunction.h"

SoccerSliding::SoccerSliding(
	const Params&P,
	SoccerPlayer* s)
{
	m_Params = P;
	m_SoccerPlayer = s;
	timer = 0;
}
SoccerSliding::~SoccerSliding()
{

}
void SoccerSliding::Start()
{
	m_SoccerPlayer->m_Renderer.SetMotion(SoccerPlayer::_ms_Rolling);
}
void SoccerSliding::Update()
{
	timer++;
	m_SoccerPlayer->m_Renderer.Update(1);
	//前に加速し、方向をスティックの向きに
	chr_func::AddMoveFront(m_SoccerPlayer, m_Params.speed, m_Params.speed);
	chr_func::PositionUpdate(m_SoccerPlayer);
	
}
bool SoccerSliding::is_End()
{

	if (timer > 48){
		m_SoccerPlayer->m_Renderer.SetMotion(SoccerPlayer::_ms_Stand);
		timer = 0;
		return true;
	}
	else
		return false;
}