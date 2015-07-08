#include "TennisPlayerState_Shot.h"
#include "TennisPlayerState_UsualMove.h"
#include "Tennis_HitEvent.h"
#include "../../GameSystem/GameController.h"
#include "../CharacterFunction.h"
#include "../../Ball/UsualBall.h"
#include "../../Damage/Damage.h"
#include "../CharacterCounterClass.h"
#include "../CharacterMoveClass.h"
#include "../CharacterShotAttackClass.h"


//****************************************************
//	�e�j�X_�v���C���[����̉������U���N���X
//****************************************************

void TennisState_PlayerControll_Shot::Enter(TennisPlayer* t)
{
	class ShotEvent :public CharacterShotAttack::Event
	{
		TennisPlayer* pTennis;
	public:
		ShotEvent(TennisPlayer* pTennis):
			pTennis(pTennis)
		{

		}
		void Update()
		{
			//�A�j���[�V�����X�V
			pTennis->m_Renderer.Update(1);

			// �]���s��X�V
			chr_func::CreateTransMatrix(
				pTennis,
				0.05f,
				&pTennis->m_Renderer.m_TransMatrix);
		}

		void Shot()
		{
			//�{�[������
			BallBase::Params param;

			//�ړ��͑O����
			chr_func::GetFront(pTennis, &param.move);
			//�X�s�[�h�͓K��
			param.move *= 0.65f;	
			//�L�����̏ꏊ��(�ŏI�I�ɘr�̈ʒu�ɁH)
			param.pos = pTennis->m_Params.pos;
			//�������L�������ʃ{�[�����˂�Y��
			param.pos.y = BallBase::UsualBallShotY;	
			//�e��������
			param.pParent = pTennis;
			//�ʏ�^�C�v
			param.type = BallBase::Type::_Usual;

			//����
			new UsualBall(param, DamageBase::Type::_WeekDamage, 1);
		}

		void AttackStart()
		{
			pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_Shot);
		}

		void AttackEnd()
		{
			//�U���I�����ɒʏ�ړ����[�h�ɖ߂�
			pTennis->SetState(new TennisState_PlayerControll_Move());
		}
	};

	CharacterShotAttack::AttackParams atk;

	atk.AllFrame = 40;
	atk.AttackPower = 1;
	atk.MaxTurnRadian = PI / 4;
	atk.MoveDownSpeed = 0.1f;
	atk.ShotFrame = 15;

	m_pShotClass = new CharacterShotAttack(
		t,
		new ShotEvent(t),
		atk,
		new TennisHitEvent(t)
		);
}

void TennisState_PlayerControll_Shot::Execute(TennisPlayer* t)
{
	m_pShotClass->Update();
}

void TennisState_PlayerControll_Shot::Exit(TennisPlayer* t)
{
	delete m_pShotClass;
}