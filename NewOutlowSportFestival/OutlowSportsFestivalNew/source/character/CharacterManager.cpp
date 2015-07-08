#include "CharacterManager.h"
#include "CharacterFunction.h"


CharacterManager* CharacterManager::m_pInstance = nullptr;

CharacterManager& CharacterManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CharacterManager();
	}

	return *m_pInstance;
}

void CharacterManager::Release()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

//�L�����N�^�f�[�^�̃Q�b�^
const CharacterManager::CharacterMap& 
	CharacterManager::GetCharacterMap()const
{
	return m_CharacterMap;
}

//�L�����N�^�̐����l�����擾
UINT CharacterManager::GetCharacterLiveCount()const
{
	UINT ret = 0;

	for (auto it = m_CharacterMap.begin();
		it != m_CharacterMap.end();
		++it)
	{
		//����ł��Ȃ������ꍇ
		if (!chr_func::isDie(it->first))
		{
			++ret;
		}
	}

	return ret;
}

CharacterManager::CharacterManager()
{

}

CharacterManager::~CharacterManager()
{

}

void CharacterManager::Add(LpCharacterBase c)
{
	m_CharacterMap.insert(CharacterMap::value_type(c, c));
}

void CharacterManager::Erace(LpCharacterBase c)
{
	m_CharacterMap.erase(c);
}