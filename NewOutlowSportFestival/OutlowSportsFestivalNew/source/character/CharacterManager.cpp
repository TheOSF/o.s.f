#include "CharacterManager.h"

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

//キャラクタデータのゲッタ
const CharacterManager::CharacterMap& 
	CharacterManager::GetCharacterMap()const
{
		return m_CharacterMap;
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