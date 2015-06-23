#ifndef __BASEBALL_PLAYER_STATE_H__
#define __BASEBALL_PLAYER_STATE_H__

#include "BaseballPlayer.h"

#include "../CharacterMoveClass.h"

//****************************************************
//	野球プレイヤーの操作クラスヘッダー
//****************************************************

//プレイヤー操作の移動クラス
class BaseballState_PlayerControll_Move :public BaseballState
{
private:
	CharacterUsualMove* m_pMoveClass;
public:
	//　ステート開始
	void Enter(BaseballPlayer* b)override;
	//　ステート実行
	void Execute(BaseballPlayer* b)override;
	//　ステート終了
	void Exit(BaseballPlayer* b)override;
};


//プレイヤー操作の回避クラス
class CharacterEvasion;
class BaseballState_PlayerControll_Evasion :public BaseballState
{

public:
	//　コンストラクタ
	BaseballState_PlayerControll_Evasion();
	//　ステート開始
	void Enter(BaseballPlayer* b)override;
	//　ステート実行
	void Execute(BaseballPlayer* b)override;
	//　ステート終了
	void Exit(BaseballPlayer* b)override;

private:
	// 回避クラス作成
	CharacterEvasion* CreateEvasionClass(BaseballPlayer* b);
private:
	// 回避クラス
	CharacterEvasion* m_pEvasionClass;
};
#endif