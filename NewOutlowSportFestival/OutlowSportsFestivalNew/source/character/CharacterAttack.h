#ifndef __CHARACTER_ATTACK_CLASS_H__
#define __CHARACTER_ATTACK_CLASS_H__

class CharacterBase;

#include "iextreme.h"

//****************************************************************
//		�L�����N�^���ʂ̍U���N���X
//****************************************************************


//�ʏ�U���N���X
class CharacterNearAttack
{
public:
	struct Params
	{
		int   AttackFrame;  //�U���J�n�t���[��
		int   EndFrame;  //�U���I���t���[��
		float speed;        //�X�s�[�h(�c��)
		float damage;       //�_���[�W
		float TurnSpeed;	//�p�x�ω��X�s�[�h
		int    CanDoComboFrame;       // ���̃R���{��t�t���[��
		int    GoNextComboFrame;      // �R���{�����s����t���[��
	};

	class AttackEvent
	{
	public:
		virtual~AttackEvent(){}
		virtual void Update() = 0;	//���t���[�����s�����֐�
		virtual void Assault() = 0;
		virtual void AttackStart() = 0;			//�U���J�n���ɌĂ΂��֐�
		virtual void AttackEnd() = 0;			//�_�����J�n���ɌĂ΂��֐�
	};

	CharacterNearAttack(
		CharacterBase*	pParent,	//����L�����N�^�̃|�C���^
		const Params&	param,
		AttackEvent*		pAtttackEvent);

	~CharacterNearAttack();

	bool Update();	//�X�V
	// �R���{�ł��邩�ǂ���
	bool CanDoCombo()const;

	// �R���{���s�ł��邩�ǂ���
	bool CanGoNextCombo()const;
	bool is_End();	//�X�V
	void SetStickValue(CrVector2 StickValue);
private:
	CharacterBase*	m_pCharacter;
	AttackEvent*	m_pAttackEvent;
	Params			m_Params;
	int             m_timer;
	Vector2			m_StickValue;
};

#endif