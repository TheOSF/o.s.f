#include "TennisPlayerState.h"
#include "../../GameSystem/GameController.h"
#include "../CharacterFunction.h"
#include "../../Ball/UsualBall.h"
#include "../../Damage/Damage.h"
#include "../CharacterCounterClass.h"
#include "../CharacterMoveClass.h"
#include "../CharacterShotAttackClass.h"

//****************************************************
//	�e�j�X�v���C���[�̑���N���X�w�b�_�[
//****************************************************

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


	if (controller::GetTRG(controller::button::sankaku, t->m_PlayerInfo.number))
	{// [��] �Ń{�[������
		t->SetState(new TennisState_PlayerControll_Shot());
	}

	if (controller::GetTRG(controller::button::_R1, t->m_PlayerInfo.number))
	{// [R1] �� [�J�E���^�[�\��]
		t->SetState(new TennisState_PlayerControll_Counter());
	}
}

void TennisState_PlayerControll_Move::Exit(TennisPlayer* t)
{
	delete m_pMoveClass;
}

//***************************************************
//		�v���C���[����� �J�E���^�[�N���X
//***************************************************

// �X�e�[�g�J�n
void TennisState_PlayerControll_Counter::Enter(TennisPlayer* t)
{
	// �J�E���^�[�N���X�쐬
	m_pCounter = CreateCounterClass(t);
}


// �X�e�[�g���s
void TennisState_PlayerControll_Counter::Execute(TennisPlayer* t)
{
	// �{�^���X�V
	controller::button::button_state button_state;
	button_state = controller::GetButtonState(
		controller::button::_R1, 
		t->m_PlayerInfo.number
		);
	m_pCounter->SetButtonState(button_state);

	//�X�V
	if (m_pCounter->Update() == false)
	{
		return;
	}
}


// �X�e�[�g�I��
void TennisState_PlayerControll_Counter::Exit(TennisPlayer* t)
{
	delete m_pCounter;
}


// �J�E���^�[�\���N���X�쐬
CharacterCounter* TennisState_PlayerControll_Counter::CreateCounterClass(TennisPlayer* t)
{
	class CounterEvent : public CharacterCounter::Event
	{
		TennisPlayer* m_pTennis;
		int m_CounterLevel;
	public:
		// �R���X�g���N�^
		CounterEvent(TennisPlayer* pTennisPlayer) :
			m_pTennis(pTennisPlayer),
			m_CounterLevel(0){}

		// �X�V
		void Update()override
		{
			// ���f���X�V
			m_pTennis->m_Renderer.Update(1);

			// �]���s��X�V
			chr_func::CreateTransMatrix(
				m_pTennis,
				0.05f,
				&m_pTennis->m_Renderer.m_TransMatrix);
		}

		// �\���J�n
		void PoseStart()override
		{
			m_pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_CounterPose);
		}

		// �\���I��
		void PoseEnd()override
		{// �J�E���^�[
			m_pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_Counter);
		}

		// �J�E���^�[�ł���{�[�������ꂽ
		void BallEnter()override
		{
			MyDebugString("CounterBall is Enter.\n");
		}

		// ���x���A�b�v
		void LevelUp(int level)override
		{
			m_CounterLevel = level;
			MyDebugString("%d\n", level);
		}

		// �J�E���^�[�J�n
		void SwingStart()override
		{
			m_pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_Counter);
		}

		// �J�E���^�[�I��
		void SwingEnd()override
		{// �ʏ�ړ���
			m_pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_Stand);
			m_pTennis->SetState(new TennisState_PlayerControll_Move());
		}

		// �ł��Ԃ����Ƃ�
		void HitBall(bool is_just)override
		{
			MyDebugString("Hit Ball.\n");
		}
	};

	// �p�����[�^�ݒ�
	CharacterCounter::CounterParams params;
	params.MaxPoseFrame = 60;
	params.LevelUpFrame = 45;
	params.SwingTotalFrame = 30;
	params.CounterMoveFrame = 5;
	params.MoveDownSpeed = 0.2f;
	params.CanCounterArea = 10.0f;

	return new CharacterCounter(
		3,
		params,
		t,
		new CounterEvent(t)
		);
}


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
		atk
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