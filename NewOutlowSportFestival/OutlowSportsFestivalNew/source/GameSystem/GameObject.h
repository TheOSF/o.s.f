#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <map>
#include "debug\DebugFunction.h"

class GameObjectManager;


//********************************************************************
//	�p������Ǝ����ōX�V����Q�[�����I�u�W�F�N�g�̃x�[�X�N���X
//********************************************************************

class GameObjectBase
{
public:
	enum MsgType
	{
		_PlayStart,	//�v���C�J�n��(���E���h���Ƃ�)�ɑ����郁�b�Z�[�W
		_RoundEnd,	//���E���h�I�����ɑ����郁�b�Z�[�W
	};

	GameObjectBase();

	virtual bool Update() = 0;	//false��Ԃ��Ə�������
	virtual bool Msg(MsgType mt) = 0;
protected:
	friend class GameObjectManager;
	virtual ~GameObjectBase();
};

typedef GameObjectBase* LpGameObjectBase;


//********************************************************************
//	�I�u�W�F�N�g�N���X�̕`��E�X�V������}�l�[�W���N���X
//********************************************************************

class GameObjectManager
{
public:
	static GameObjectManager& GetInstance();
	static void Release();
	
	void Update();	//�S�I�u�W�F�N�g�X�V

	void SendMsg(GameObjectBase::MsgType mt);	//�S�I�u�W�F�N�g�Ƀ��b�Z�[�W�𑗐M

private:
	typedef std::map<LpGameObjectBase, LpGameObjectBase> GameObjectMap;

	friend class GameObjectBase;
private:
	static GameObjectManager*	m_pInstance;
	GameObjectMap				m_GameObjectMap;
private:
	GameObjectManager();
	~GameObjectManager();

	bool Add(LpGameObjectBase pObj);
	bool Erace(LpGameObjectBase pObj);
};

#define DefGameObjMgr (GameObjectManager::GetInstance())


#endif