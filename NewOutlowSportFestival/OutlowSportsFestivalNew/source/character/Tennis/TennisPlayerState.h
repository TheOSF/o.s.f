#ifndef __TENNIS_PLAYER_STATE_H__
#define __TENNIS_PLAYER_STATE_H__

#include "TennisPlayer.h"
#include "../../GameSystem/ForwardDecl.h"

//****************************************************
//	テニスプレイヤーの操作クラスヘッダー
//****************************************************

//プレイヤー操作の移動クラス
class TennisState_PlayerControll_Move :public TennisState
{
private:
	CharacterUsualMove*		m_pMoveClass;
public:
	void Enter(TennisPlayer* t)override;
	void Execute(TennisPlayer* t)override;
	void Exit(TennisPlayer* t)override;
};

class CharacterCounter;
//***************************************************
//		プレイヤー操作の カウンタークラス
//***************************************************
class TennisState_PlayerControll_Counter : public TennisState
{
public:
	// ステート開始
	void Enter(TennisPlayer* t)override;

	// ステート実行
	void Execute(TennisPlayer* t)override;

	// ステート終了
	void Exit(TennisPlayer* t)override;

private:
	// カウンタークラス作成
	CharacterCounter* CreateCounterClass(TennisPlayer* t);

	CharacterCounter* m_pCounter; // カウンタークラス
};


//****************************************************
//	テニス_プレイヤー操作の遠距離攻撃クラス
//****************************************************
class TennisState_PlayerControll_Shot :public TennisState
{
private:
	CharacterShotAttack*	m_pShotClass;
public:
	void Enter(TennisPlayer* t)override;
	void Execute(TennisPlayer* t)override;
	void Exit(TennisPlayer* t)override;
};


#endif