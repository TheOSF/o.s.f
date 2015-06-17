#pragma once


//*************************************************************
//
//		ラクロスの操作クラスヘッダー
//
//*************************************************************


#include "LacrossePlayer.h"

class CharacterUsualMove;
//***************************************************
//		プレイヤー操作の 移動クラス
//***************************************************
class LacrosseState_PlayerControllMove : public LacrosseState
{
public:

	// ステート開始
	void Enter(LacrossePlayer* t)override;

	// ステート実行
	void Execute(LacrossePlayer* t)override;

	// ステート終了
	void Exit(LacrossePlayer* t)override;

private:
	// 移動時のイベントクラス作成
	CharacterUsualMove* CreateMoveClass(LacrossePlayer* t);

private:
	CharacterUsualMove* m_pMoveClass;  // キャラクター共通の移動クラス
};


class LacrosseAttackClose;
//***************************************************
//		プレイヤー操作の 近距離攻撃クラス
//***************************************************
class LacrosseState_PlayerControllAttackClose : public LacrosseState
{
public:
	// コンストラクタ
	LacrosseState_PlayerControllAttackClose(int combo);

	// ステート開始
	void Enter(LacrossePlayer* t)override;

	// ステート実行
	void Execute(LacrossePlayer* t)override;

	// ステート終了
	void Exit(LacrossePlayer* t)override;

private:
	// 近接攻撃クラス作成
	LacrosseAttackClose* CreateAttackClass(LacrossePlayer* t, lacrosse_player::MotionType motion);

private:
	static const int            kComboMax;        // 最大コンボ数
	const int                     m_ComboCount;  // コンボ数
	LacrosseAttackClose* m_pAttackClass;  // 近接攻撃クラス
	bool                            m_DoCombo;      // コンボするかどうか
};


class LacrosseEvasion;
//***************************************************
//		プレイヤー操作の 回避クラス
//***************************************************
class LacrosseState_PlayerControllEvasion : public LacrosseState
{
public:
	// コンストラクタ
	LacrosseState_PlayerControllEvasion();

	// ステート開始
	void Enter(LacrossePlayer* t)override;

	// ステート実行
	void Execute(LacrossePlayer* t)override;

	// ステート終了
	void Exit(LacrossePlayer* t)override;

private:
	// 回避クラス作成
	LacrosseEvasion* CreateEvasionClass(LacrossePlayer* t);

private:
	LacrosseEvasion* m_pEvasionClass; // 回避クラス
};


class LacrosseHitBallAttack;
//***************************************************
//		プレイヤー操作の 遠距離攻撃 (ボール打ち出し) クラス
//***************************************************
class LacrosseState_PlayerControllHitBallAttack : public LacrosseState
{
public:
	// コンストラクタ
	LacrosseState_PlayerControllHitBallAttack();

	// ステート開始
	void Enter(LacrossePlayer* t)override;

	// ステート実行
	void Execute(LacrossePlayer* t)override;

	// ステート終了
	void Exit(LacrossePlayer* t)override;

private:
	// 回避クラス作成
	LacrosseHitBallAttack* CreateAttackClass(LacrossePlayer* t);

private:
	LacrosseHitBallAttack* m_pAttackClass; // 回避クラス
};



class LacrosseCounterPose;
//***************************************************
//		プレイヤー操作の カウンター構えクラス
//***************************************************
class LacrosseState_PlayerControllCounterPose : public LacrosseState
{
public:
	// コンストラクタ
	LacrosseState_PlayerControllCounterPose();

	// ステート開始
	void Enter(LacrossePlayer* t)override;

	// ステート実行
	void Execute(LacrossePlayer* t)override;

	// ステート終了
	void Exit(LacrossePlayer* t)override;

private:
	// カウンター構えクラス作成
	LacrosseCounterPose* CreateCounterPoseClass(LacrossePlayer* t);

private:
	LacrosseCounterPose* m_pCounterPose; // カウンター構えクラス
};


#if 0
class LacrosseHitCounter;
//***************************************************
//		プレイヤー操作の カウンタークラス
//     このステート中は移動できる
//***************************************************
class LacrosseState_PlayerControllCounter : public LacrosseState
{
public:
	// コンストラクタ
	LacrosseState_PlayerControllCounter();

	// ステート開始
	void Enter(LacrossePlayer* t)override;

	// ステート実行
	void Execute(LacrossePlayer* t)override;

	// ステート終了
	void Exit(LacrossePlayer* t)override;

private:
	// カウンター打つクラス作成
	LacrosseHitCounter* CreateHitCounterClass(LacrossePlayer* t);

	// 移動クラス作成
	CharacterUsualMove* CreateMoveClass(LacrossePlayer* t);

private:
	LacrosseHitCounter*  m_pHitCounter; // カウンター打つクラス
	CharacterUsualMove* m_pMove;          // 移動クラス
	
};

#endif