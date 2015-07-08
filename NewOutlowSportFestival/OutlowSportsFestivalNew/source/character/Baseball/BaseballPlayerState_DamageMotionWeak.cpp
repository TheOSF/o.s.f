#include "BaseballPlayerState_DamageMotionWeak.h"
//#include "BaseballPlayerState_UsualMove.h"
#include "Baseball_HitEvent.h"
#include "../CharacterFunction.h"

BaseballState_DamageMotion_Weak::BaseballState_DamageMotion_Weak(
	BaseballPlayer* pBaseball,
	const Vector3& Damage_vec  //�_���[�W���󂯂�����
	) :
	m_pBaseball(pBaseball),
	m_Damage_vec(Damage_vec)
{

}

void BaseballState_DamageMotion_Weak::Enter(BaseballPlayer* t)
{
	//�L�����N�^���ʂЂ�݃N���X�̃e�j�X�ŗL�C�x���g�N���X
	class BaseballEvent :public CharacterDamageMotion::Event
	{
	public:
		BaseballEvent(BaseballPlayer* pBaseball) :m_pBaseball(pBaseball){}

		void Update(float speed)
		{
			//���f���̍X�V�̂�
			m_pBaseball->m_Renderer.Update(speed);
			//chr_func::CreateTransMatrix(m_pBaseball, m_pBaseball->m_ModelSize, &m_pBaseball->m_Renderer.m_TransMatrix);
		}
		void Start()
		{
			//�Ђ�݃��[�V�������Z�b�g
			//m_pBaseball->m_Renderer.SetMotion(BaseballPlayer::_mt_Damage_Weak);
		}
		void End()
		{
			//�ʏ�X�e�[�g���Z�b�g
		//	m_pBaseball->SetState(
		//		BaseballState_PlayerControll_Move::GetPlayerControllMove(m_pBaseball)
		//		);
		}
	private:
		BaseballPlayer*  m_pBaseball;
	};

	//�_���[�W���[�V�����p�����[�^�[���쐬����
	CharacterDamageMotion::Params Param;

	Param.AllFrame = 35;
	Param.damage_vec = m_Damage_vec;
	Param.hitBack = 0.5f;
	Param.hitStopFrame = 0;
	Param.NoDamageFrame = 10;

	//�Ђ�݃N���X���쐬
	m_pDamageMotionClass = new CharacterDamageMotion(
		m_pBaseball,
		new BaseballEvent(m_pBaseball),
		new BaseballHitEvent(m_pBaseball),
		Param
		);

}

void BaseballState_DamageMotion_Weak::Execute(BaseballPlayer* t)
{
	m_pDamageMotionClass->Update();
}

void BaseballState_DamageMotion_Weak::Exit(BaseballPlayer* t)
{

}