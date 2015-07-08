#ifndef __CHARACTER_MANAGER_H__
#define __CHARACTER_MANAGER_H__

#include "../GameSystem/ForwardDecl.h"
#include <map>

//****************************************************************
//		�L�����N�^�̃}�l�[�W���N���X
//****************************************************************

class CharacterManager
{
public:
	typedef std::map<LpCharacterBase, LpCharacterBase> CharacterMap;

	static CharacterManager& GetInstance();
	static void Release();

	//�L�����N�^�f�[�^�̃Q�b�^
	const CharacterMap& GetCharacterMap()const;

	//�L�����N�^�̐����l�����擾
	UINT GetCharacterLiveCount()const;

private:
	friend class CharacterBase;
	

	static CharacterManager* m_pInstance;
	CharacterMap m_CharacterMap;

	CharacterManager();
	~CharacterManager();

	void Add(LpCharacterBase c);
	void Erace(LpCharacterBase c);
};

#define DefCharacterMgr (CharacterManager::GetInstance())

#endif