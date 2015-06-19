#ifndef __TENNIS_PLAYER_STATE_H__
#define __TENNIS_PLAYER_STATE_H__

#include "TennisPlayer.h"
#include "../CharacterMoveClass.h"


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

class CharacterCounterPose;
//***************************************************
//		プレイヤー操作の カウンター構えクラス
//***************************************************
class TennisState_PlayerControll_CounterPose : public TennisState
{
public:
	// ステート開始
	void Enter(TennisPlayer* t)override;

	// ステート実行
	void Execute(TennisPlayer* t)override;

	// ステート終了
	void Exit(TennisPlayer* t)override;

private:
	// カウンター構えクラス作成
	CharacterCounterPose* CreateCounterPoseClass(TennisPlayer* t);

	CharacterCounterPose* m_pCounterPose; // カウンター構えクラス
};


class CharacterCounter;
//***************************************************
//		プレイヤー操作の カウンター構えクラス
//***************************************************
class TennisState_PlayerControll_Counter : public TennisState
{
public:
	// コンストラクタ
	TennisState_PlayerControll_Counter(int level);

	// ステート開始
	void Enter(TennisPlayer* t)override;

	// ステート実行
	void Execute(TennisPlayer* t)override;

	// ステート終了
	void Exit(TennisPlayer* t)override;

private:
	// カウンタークラス作成
	CharacterCounter* CreateCounterClass(TennisPlayer* t, int level);

	int                           m_Level;        // カウンターレベル
	CharacterCounter*  m_pCounter; // カウンタークラス
};

#endif