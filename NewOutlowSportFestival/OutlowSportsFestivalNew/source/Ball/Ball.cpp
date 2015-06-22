#include "Ball.h"
#include "debug\DebugFunction.h"

//*****************************************************
//	���x�[�X�N���X
//*****************************************************

const float BallBase::UsualBallShotY = 2.5f;

BallBase::BallBase()
{
	MyAssert(DefBallMgr.AddBall(this), "�{�[���o�^�Ɏ��s���܂���");
}

BallBase::~BallBase()
{
	MyAssert(DefBallMgr.EraceBall(this), "�{�[���폜�Ɏ��s���܂���");
}

bool BallBase::isCanCounter(const BallBase* pBall)
{
	//�J�E���^�[�\�ȃ{�[�����ǂ���
	return pBall->m_Params.type == BallBase::Type::_Usual;
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

//�{�[���f�[�^�擾
BallManager::BallMap* BallManager::GetBallMap()
{
	return &m_BallMap;
}

//�����Ƃ��J�E���^�[����̂ɓK�����{�[���𓾂�
bool BallManager::GetCounterBall(
	BallBase**	ppOut,			//�߂�l�Ƃ��ĕԋp����{�[��
	CrVector3	character_pos,	//�L�����N�^�̏ꏊ
	Vector3*	pOutAfterFrameBallPos,//�L���b�`�܂ł̈ړ��t���[����̃{�[���̈ʒu
	float		catch_area_size,//�L���b�`�\�Ȕ͈�
	int			move_frame		//�L���b�`�܂ł̈ړ��t���[��
	)
{
	
	float most_near = catch_area_size;		//�����΂�߂��{�[���܂ł̋���
	float temp_len;
	float Fmove_frame = (float)move_frame;	

	*ppOut = nullptr;

	Vector3 move_pos;
	Vector3 len;

	for (
		auto it = m_BallMap.begin();
		it != m_BallMap.end();
		++it)
	{
		if (!BallBase::isCanCounter(it->second))
		{
			continue;
		}

		//Fmove_frame��̃{�[���̈ʒu���Z�o
		move_pos = it->second->m_Params.move;
		move_pos *= Fmove_frame;
		move_pos += it->second->m_Params.pos;

		//�������Z�o
		len = move_pos - character_pos;
		temp_len = len.Length();

		//�ŒZ�������X�V�����ꍇ�͖߂�l�ɑ��
		if (most_near > temp_len)
		{
			most_near = temp_len;
			*ppOut = it->second;
			*pOutAfterFrameBallPos = move_pos;
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