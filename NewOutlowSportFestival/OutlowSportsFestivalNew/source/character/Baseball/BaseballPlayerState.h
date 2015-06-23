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

private:
	bool batterflg;//　(true:バッター,false:投手)

public:
	//　コンストラクタ
	BaseballState_PlayerControll_Move() :batterflg(true){}
	//　ステート開始
	void Enter(BaseballPlayer* b)override;
	//　ステート実行
	void Execute(BaseballPlayer* b)override;
	//　ステート終了
	void Exit(BaseballPlayer* b)override;
public:

	//　バッター時実行
	void Batter(BaseballPlayer* b);
	//　投手時実行
	void Pitcher(BaseballPlayer* b);
	//　セッター
	void SetBatterFlg(BaseballPlayer* b){ batterflg = b->getBatterFlg(); }
};


//プレイヤー操作の回避クラス
class CharacterEvasion;
class BaseballState_PlayerControll_Evasion :public BaseballState{
private:
	float roolspeed;//　回避時の速さ
private:
	// 回避クラス作成
	CharacterEvasion* CreateEvasionClass(BaseballPlayer* b);
private:
	// 回避クラス
	CharacterEvasion* m_pEvasionClass;
public:
	//　コンストラクタ
	BaseballState_PlayerControll_Evasion(float speed);
	//　ステート開始
	void Enter(BaseballPlayer* b)override;
	//　ステート実行
	void Execute(BaseballPlayer* b)override;
	//　ステート終了
	void Exit(BaseballPlayer* b)override;

};
#endif