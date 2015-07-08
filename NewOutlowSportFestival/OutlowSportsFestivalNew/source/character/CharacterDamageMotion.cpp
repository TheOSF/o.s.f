#include "CharacterDamageMotion.h"
#include "CharacterFunction.h"
#include "CharacterBase.h"

CharacterDamageMotion::CharacterDamageMotion(
	CharacterBase* pCharacter,
	Event* pEvent,
	DamageManager::HitEventBase* pHitEvent,
	const Params& params
	):
	m_pCharacter(pCharacter),
	m_Timer(0),
	m_pEvent(pEvent),
	m_Start(false),
	m_End(false),
	m_pHitEvent(pHitEvent)
{
	m_Params = params;
}

CharacterDamageMotion::~CharacterDamageMotion()
{
	delete m_pEvent;
}


// �X�V
void CharacterDamageMotion::Update()
{
	//�t���[���X�V
	++m_Timer;

	if (m_Start == false)
	{
		m_Start = true;

		//�L�����N�^���_���[�W�̕����Ɍ�������
		chr_func::AngleControll(
			m_pCharacter,
			m_pCharacter->m_Params.pos - m_Params.damage_vec
			);

		//�X�^�[�g�C�x���g�Ăяo��
		m_pEvent->Start();
	}

	//���G�t���[������
	if (m_Timer > m_Params.NoDamageFrame)
	{
		//�_���[�W����
		chr_func::DamageCheck(m_pCharacter, m_pHitEvent);
	}

	//�C�x���g�N���X�X�V
	m_pEvent->Update((m_Timer < m_Params.hitStopFrame) ? (0.2f) : (1.0f));

	//�I������
	if (m_End == false &&
		m_Params.AllFrame <= m_Timer)
	{
		m_End = true;
		m_pEvent->End();
	}
}