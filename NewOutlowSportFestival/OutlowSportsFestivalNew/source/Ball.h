#ifndef __BALL_H__
#define __BALL_H__

#include <map>
#include <list>
#include "iextreme.h"

//*****************************************************
//		玉ベースクラス
//*****************************************************

class BallBase
{
public:
	//球の機能のタイプ
	enum Type
	{
		_DontWork,				//描画はしているが、あたり判定のないボール
		_Usual,					//通常のボール
		_CantCounter,			//カウンターできない通常のボール
		_CanVolleySmash,		//バレーキャラクタでスマッシュすることができる状態のボール
		_TennisSpecialAtk,		//テニス
	};

	//パラメータ構造体
	struct Params
	{
		Type		type;
		Vector3		pos;
		Vector3		move;
	};

	Params	m_Params;

	//コンストラクタ・デストラクタで自動的にマネージャに登録・削除を行う
	BallBase();
	virtual ~BallBase();
};


//*****************************************************
//	ボールマネージャ(シングルトン実装)
//*****************************************************
class BallManager
{
public:
	//登録・削除をBallBaseのみ可能にするため
	friend class BallBase;

	//インスタンスのゲッタ・解放
	static BallManager& GetInstance();
	static void Release();

private:
	typedef std::map<BallBase*, BallBase*> BallMap;

	static BallManager*		m_pInstance;
	BallMap					m_BallMap;

	BallManager();
	~BallManager();

	bool AddBall(BallBase* pBall);
	bool EraceBall(BallBase* pBall);
};

#define DefBallMgr (BallManager::GetInstance())

#endif