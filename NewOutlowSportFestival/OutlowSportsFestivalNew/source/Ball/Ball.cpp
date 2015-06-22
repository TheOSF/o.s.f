#include "Ball.h"
#include "debug\DebugFunction.h"

//*****************************************************
//	球ベースクラス
//*****************************************************

const float BallBase::UsualBallShotY = 2.5f;

BallBase::BallBase()
{
	MyAssert(DefBallMgr.AddBall(this), "ボール登録に失敗しました");
}

BallBase::~BallBase()
{
	MyAssert(DefBallMgr.EraceBall(this), "ボール削除に失敗しました");
}

bool BallBase::isCanCounter(const BallBase* pBall)
{
	//カウンター可能なボールかどうか
	return pBall->m_Params.type == BallBase::Type::_Usual;
}

//*****************************************************
//	ボールマネージャ(シングルトン実装)
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

//ボールデータ取得
BallManager::BallMap* BallManager::GetBallMap()
{
	return &m_BallMap;
}

//もっともカウンターするのに適したボールを得る
bool BallManager::GetCounterBall(
	BallBase**	ppOut,			//戻り値として返却するボール
	CrVector3	character_pos,	//キャラクタの場所
	float		catch_area_size,//キャッチ可能な範囲
	int			move_frame		//キャッチまでの移動フレーム
	)
{
	
	float most_near = 10000000;		//いちばん近いボールまでの距離
	float temp_len;
	float Fmove_frame = (float)move_frame;	

	*ppOut = nullptr;

	Vector3 move_pos;	

	for (
		auto it = m_BallMap.begin();
		it != m_BallMap.end();
		++it)
	{
		if (!BallBase::isCanCounter(it->second))
		{
			continue;
		}

		//Fmove_frame後のボールの位置を算出
		move_pos = it->second->m_Params.move;
		move_pos *= Fmove_frame;
		move_pos += it->second->m_Params.pos;

		//距離を算出
		move_pos -= character_pos;
		temp_len = move_pos.Length();

		//最短距離を更新した場合は戻り値に代入
		if (most_near > temp_len)
		{
			most_near = temp_len;
			*ppOut = it->second;
		}
	}


	return *ppOut != nullptr;
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