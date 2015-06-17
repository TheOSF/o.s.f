#include "GameObject.h"

GameObjectManager*	GameObjectManager::m_pInstance = nullptr;

GameObjectBase::GameObjectBase()
{
	MyAssert(DefGameObjMgr.Add(this), "“o˜^Ž¸”s");
}

GameObjectBase::~GameObjectBase()
{
	
}

GameObjectManager& GameObjectManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new GameObjectManager();
	}
	return *m_pInstance;
}

void GameObjectManager::Release()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void GameObjectManager::Update()
{
	GameObjectMap::iterator it = m_GameObjectMap.begin();

	while(it != m_GameObjectMap.end())
	{
		if (it->second->Update() == false)
		{
			delete it->second;
			it = m_GameObjectMap.erase(it);
			
			continue;
		}
		++it;
	}
}

bool GameObjectManager::Add(LpGameObjectBase pObj)
{
	if (m_GameObjectMap.find(pObj) != m_GameObjectMap.end())
	{
		return false;
	}

	m_GameObjectMap.insert(GameObjectMap::value_type(pObj, pObj));

	return true;
}

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{

}
