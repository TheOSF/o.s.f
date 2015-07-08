#include "TennisPlayerState_UsualMove.h"
#include "TennisPlayerState_Shot.h"
#include "TennisPlayerState_Counter.h"
#include "../../GameSystem/GameController.h"
#include "../CharacterFunction.h"
#include "../../Ball/UsualBall.h"
#include "../../Damage/Damage.h"
#include "../CharacterCounterClass.h"
#include "../CharacterMoveClass.h"
#include "../CharacterShotAttackClass.h"
#include "Tennis_HitEvent.h"


//****************************************************
//	�e�j�X�v���C���[�̑���N���X�w�b�_�[
//****************************************************

TennisState* TennisState_PlayerControll_Move::GetPlayerControllMove(
	TennisPlayer* pt)
{
	switch (pt->m_PlayerInfo.player_type)
	{
	case PlayerType::_Player:
		return new TennisState_PlayerControll_Move();

	case PlayerType::_Computer:
		switch (pt->m_PlayerInfo.strong_type)
		{
		case StrongType::_Weak:
			//return new �ア�ʏ�ړ�
		case StrongType::_Usual:
			//return new �ア�ʏ�ړ�
		case StrongType::_Strong:
			//return new �ア�ʏ�ړ�
		default:break;
		}
	default:break;
	}

	assert("�ʏ�X�e�[�g���쐬�ł��Ȃ��L�����N�^�^�C�v�ł� TennisState_PlayerControll_Move::GetPlayerControllMove" && 0);
	return nullptr;
}

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
		new TennisHitEvent(t)
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
	chr_func::CreateTransMatrix(t, t->m_ModelSize, &t->m_Renderer.m_TransMatrix);


	if (controller::GetTRG(controller::button::sankaku, t->m_PlayerInfo.number))
	{// [��] �Ń{�[������
		t->SetState(new TennisState_PlayerControll_Shot());
	}

	if (controller::GetTRG(controller::button::_R1, t->m_PlayerInfo.number))
	{// [R1] �� [�J�E���^�[]
		t->SetState(new TennisState_PlayerControll_Counter());
	}
}

void TennisState_PlayerControll_Move::Exit(TennisPlayer* t)
{
	delete m_pMoveClass;
}


