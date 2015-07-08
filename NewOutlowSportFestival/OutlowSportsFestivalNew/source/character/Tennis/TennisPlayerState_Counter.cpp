#include "TennisPlayerState_Counter.h"
#include "TennisPlayerState_UsualMove.h"
#include "../../GameSystem/GameController.h"
#include "../CharacterFunction.h"
#include "../../Ball/UsualBall.h"
#include "../../Damage/Damage.h"
#include "../CharacterCounterClass.h"
#include "../CharacterMoveClass.h"
#include "../CharacterShotAttackClass.h"


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
	m_pCounter->Update();

	//���f���̃��[���h�ϊ��s����X�V
	chr_func::CreateTransMatrix(t, 0.05f, &t->m_Renderer.m_TransMatrix);
}


// �X�e�[�g�I��
void TennisState_PlayerControll_Counter::Exit(TennisPlayer* t)
{
	delete m_pCounter;
}


// �J�E���^�[�\���N���X�쐬
CharacterCounter* TennisState_PlayerControll_Counter::CreateCounterClass(TennisPlayer* t)
{
	class CounterEvent : public CharacterCounter::CounterEvent
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
			//MyDebugString("CounterBall is Enter.\n");
		}

		// ���x���A�b�v
		void LevelUp(int level)override
		{
			m_CounterLevel = level;
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
			//MyDebugString("Hit Ball.\n");
		}
	};

	// �p�����[�^�ݒ�
	CharacterCounter::CounterParams params;
	params.MaxCounterLevel = 3;
	params.MaxPoseFrame = 60;
	params.LevelUpFrame = 45;
	params.SwingTotalFrame = 15;
	params.MoveToBallFrame = 2;
	params.NormalCounterArea = 10.0f;
	params.JustCounterArea = 5.0f;
	params.DamageReceiveArea = 0.5f;
	params.MoveDownSpeed = 0.2f;


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

	return new CharacterCounter(
		t,
		params,
		new CounterEvent(t)
		);
}