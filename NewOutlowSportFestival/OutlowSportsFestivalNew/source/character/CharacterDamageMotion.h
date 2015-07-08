#pragma once

#include "iextreme.h"
#include "../GameSystem/ForwardDecl.h"
#include "../Damage/Damage.h"

//***************************************************
//		�L�����N�^�[���� �Ђ�݃N���X
//***************************************************
class CharacterDamageMotion
{
public:
	// �p�����[�^
	struct Params
	{
		int AllFrame;       // �S�t���[��
		int NoDamageFrame;	//���G�t���[��
		int hitStopFrame;	//�q�b�g�X�g�b�v�t���[��
		float hitBack;		//�q�b�g�o�b�N����
		Vector3 damage_vec;	//�_���[�W�̕���
	};

	// �Ђ�݃C�x���g�N���X
	class Event
	{
	public:
		virtual~Event(){}
		virtual void Update(float speed) = 0;       // �X�V(�����̓��[�V�����X�s�[�h)
		virtual void Start() = 0;     // �Ђ�݊J�n
		virtual void End() = 0;      // �Ђ�ݏI��
	};

	// �R���X�g���N�^
	CharacterDamageMotion(
		CharacterBase* pCharacter,
		Event* pEvent,
		DamageManager::HitEventBase* pHitEvent, 
		const Params& params
		);

	// �f�X�g���N�^
	~CharacterDamageMotion();

	// �X�V
	void Update();

private:
	bool				           m_Start;
	bool				           m_End;
	Params		                   m_Params;      // �p�����[�^
	CharacterBase*                 m_pCharacter;  // �L�����N�^�[
	int                            m_Timer;       // �^�C�}�[
	Event*                         m_pEvent;      // �C�x���g
	DamageManager::HitEventBase*   m_pHitEvent;   //�@�q�b�g�C�x���g
};

