#include "Ball.h"
#include "debug\DebugFunction.h"

//*****************************************************
//	���x�[�X�N���X
//*****************************************************

const float BallBase::UsualBallShotY = 1.0f;

BallBase::BallBase()
{
	MyAssert(DefBallMgr.AddBall(this), "�{�[���o�^�Ɏ��s���܂���");
}

BallBase::~BallBase()
{
	MyAssert(DefBallMgr.EraceBall(this), "�{�[���폜�Ɏ��s���܂���");
}



//*****************************************************
//	�{�[���}�l�[�W��(�V���O���g������)
//*****************************************************
BallManager* BallManager::m_pInstance = nullptr;

BallManager& BallManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new BallManager();
	}

	return *m_pInstance;
}

void BallManager::Release()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}


BallManager::BallManager()
{

}

BallManager::~BallManager()
{

}


bool BallManager::AddBall(BallBase* pBall)
{
	if (m_BallMap.find(pBall) != m_BallMap.end())
	{
		return false;
	}

	m_BallMap.insert(
		BallMap::value_type(pBall, pBall)
		);

	return true;
}

bool BallManager::EraceBall(BallBase* pBall)
{
	auto it = m_BallMap.find(pBall);

	if (it == m_BallMap.end())
	{
		return false;
	}

	m_BallMap.erase(it);

	return true;
}