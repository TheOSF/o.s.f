#ifndef __BALL_H__
#define __BALL_H__

#include <map>
#include <list>
#include "iextreme.h"
#include "../GameSystem/ForwardDecl.h"

//*****************************************************
//		玉ベースクラス
//*****************************************************

class BallBase
{
public:
	//通常ボール打ちのワールド座標上でのyの値
	static const float UsualBallShotY;

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
		CharacterBase*	pParent;	//発射したキャラクタへのポインタ
		Type			type;		//玉のタイプ
		Vector3			pos;		//場所
		Vector3			move;		//移動量
	};

	Params m_Params;

	//コンストラクタ・デストラクタで自動的にマネージャに登録・削除を行う
	BallBase();
	virtual ~BallBase();

	//引数のボールがカウンター可能かどうか
	static bool isCanCounter(const BallBase* pBall);
};


//*****************************************************
//	ボールマネージャ(シングルトン実装)
//*****************************************************
class BallManager
{
public:
	typedef std::map<BallBase*, BallBase*> BallMap;

	//登録・削除をBallBaseのみ可能にするため
	friend class BallBase;

	//インスタンスのゲッタ・解放
	static BallManager& GetInstance();
	static void Release();

	//ボールデータ取得
	BallMap* GetBallMap();

	//もっともカウンターするのに適したボールを得る
	bool GetCounterBall(
		BallBase**	ppOut,			//戻り値として返却するボール
		CrVector3	character_pos,	//キャラクタの場所
		Vector3*	pOutAfterFrameBallPos,//キャッチまでの移動フレーム後のボールの位置
		float		catch_area_size,//キャッチ可能な範囲
		int			move_frame		//キャッチまでの移動フレーム
		);
private:
	static BallManager*		m_pInstance;
	BallMap					m_BallMap;

	BallManager();
	~BallManager();

	bool AddBall(BallBase* pBall);
	bool EraceBall(BallBase* pBall);
};

#define DefBallMgr (BallManager::GetInstance())

#endif