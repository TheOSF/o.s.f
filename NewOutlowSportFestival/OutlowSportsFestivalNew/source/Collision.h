#ifndef __COLLISION_H__
#define __COLLISION_H__

/*
	�L����-���X�e�[�W
	�L����-���L����

	�{�[��-���X�e�[�W
	�{�[��-���L����
	
	�A�C�e��-���L����
	�A�C�e��-���X�e�[�W
*/

#include "iextreme.h"
#include "ForwardDecl.h"

class CollisionDamage
{
public:
	enum Type
	{
		_WeekDamage,	//���݂݂̂̃_���[�W
		_VanishDamage,	//��������у_���[�W
		_UpDamage,		//��ɐ������(�o���[�Ƃ�)�ǌ��\
		_Damage,		//
	};
	LpCharacter pParent;

	struct Param
	{
		
	};

};

class CollisionManager
{
public:
	static CollisionManager& GetInstance();
	static void Release();

	void Update();
	void Render();

	//�����W�ȉ��Ȃ珰���W�ɕ␳����
	bool FloorCheck(float& posY);

	//���C�s�b�N
	bool RayPick(LPVECTOR3 out, LPVECTOR3 pos, LPVECTOR3 vec, float* dist);
private:
	

};

#endif