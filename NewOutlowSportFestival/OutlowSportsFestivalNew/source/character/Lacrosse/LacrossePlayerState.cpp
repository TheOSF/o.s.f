#include "LacrossePlayerState.h"
#include "../../GameSystem/GameController.h"
#include "../CharacterFunction.h"

//*************************************************************
//
//		���N���X�̑���N���X
//
//*************************************************************


//***************************************************
//		�v���C���[����̈ړ��N���X
//     LacrosseState_PlayerControllMove
//***************************************************

// �ړ����̃C�x���g�N���X�쐬
CharacterUsualMove::MoveEvent* LacrosseState_PlayerControllMove::CreateMoveEvent(LacrossePlayer* t)
{
	class LacrosseMoveEvent : public CharacterUsualMove::MoveEvent
	{
		LacrossePlayer* m_pLacrosse;
	public:
		LacrosseMoveEvent(LacrossePlayer* pLacrosse) :
			m_pLacrosse(pLacrosse){}

		// �X�V
		void Update(bool isRun, RATIO speed_ratio)
		{
			m_pLacrosse->m_Renderer.Update(1);
		}

		// ����o������
		void RunStart()
		{
			m_pLacrosse->m_Renderer.SetMotion(LacrossePlayer::mt_Run);
		}

		// �~�܂�����
		void StandStart()
		{
			m_pLacrosse->m_Renderer.SetMotion(LacrossePlayer::mt_Stand);
		}
	};

	return new LacrosseMoveEvent(t);
}


// �X�e�[�g�J�n
void LacrosseState_PlayerControllMove::Enter(LacrossePlayer* t)
{
	// �ړ��p�����[�^�ݒ�
	CharacterUsualMove::Params p;
	p.Acceleration = 0.2f;
	p.MaxSpeed = 0.23f;
	p.TurnSpeed = 0.3f;
	p.DownSpeed = 0.2f;

	// �ړ��N���X�쐬
	m_pMoveClass = new CharacterUsualMove(t, p, this->CreateMoveEvent(t));

}


// �X�e�[�g���s
void LacrosseState_PlayerControllMove::Execute(LacrossePlayer* t)
{
	Vector2 st = controller::GetStickValue(controller::stick::left, t->m_PlayerInfo.number);

	m_pMoveClass->SetStickValue(st);
	m_pMoveClass->Update();

	chr_func::CreateTransMatrix(t, 0.05f, &t->m_Renderer.m_TransMatrix);
}


// �X�e�[�g�I��
void LacrosseState_PlayerControllMove::Exit(LacrossePlayer* t)
{
	delete m_pMoveClass;
}




