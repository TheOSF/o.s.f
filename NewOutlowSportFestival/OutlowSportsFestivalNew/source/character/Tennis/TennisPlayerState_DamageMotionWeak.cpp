#include "TennisPlayerState_DamageMotionWeak.h"
#include "TennisPlayerState_UsualMove.h"
#include "Tennis_HitEvent.h"
#include "../CharacterFunction.h"

TennisState_DamageMotion_Weak::TennisState_DamageMotion_Weak(
	TennisPlayer* pTennis,
	const Vector3& Damage_vec  //�_���[�W���󂯂�����
	):
	m_pTennis(pTennis),
	m_Damage_vec(Damage_vec)
{

}

void TennisState_DamageMotion_Weak::Enter(TennisPlayer* t)
{
	//�L�����N�^���ʂЂ�݃N���X�̃e�j�X�ŗL�C�x���g�N���X
	class TennisEvent :public CharacterDamageMotion::Event
	{
	public:
		TennisEvent(TennisPlayer* pTennis) :m_pTennis(pTennis){}

		void Update(float speed)
		{
			//���f���̍X�V�̂�
			m_pTennis->m_Renderer.Update(speed);
			chr_func::CreateTransMatrix(m_pTennis, m_pTennis->m_ModelSize, &m_pTennis->m_Renderer.m_TransMatrix);
		}
		void Start()
		{
			//�Ђ�݃��[�V�������Z�b�g
			m_pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_Damage_Weak);
		}
		void End()
		{
			//�ʏ�X�e�[�g���Z�b�g
			m_pTennis->SetState(
				TennisState_PlayerControll_Move::GetPlayerControllMove(m_pTennis)
				);
		}
	private:
		TennisPlayer*  m_pTennis;
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
		m_pTennis,
		new TennisEvent(m_pTennis),
		new TennisHitEvent(m_pTennis),
		Param
		);

}

void TennisState_DamageMotion_Weak::Execute(TennisPlayer* t)
{
	m_pDamageMotionClass->Update();
}

void TennisState_DamageMotion_Weak::Exit(TennisPlayer* t)
{

}