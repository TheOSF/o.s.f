#pragma once


//*************************************************************
//
//		ラクロスの操作クラスヘッダー
//
//*************************************************************


#include "LacrossePlayer.h"

class CharacterUsualMove;
//***************************************************
//		プレイヤー操作の移動クラス
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
	CharacterUsualMove* m_pMoveClass;  // キャラクター共通の移動クラス

	// 移動時のイベントクラス作成
	CharacterUsualMove* CreateMoveClass(LacrossePlayer* t);
};


class LacrosseAttackClose;
//***************************************************
//		プレイヤー操作の近距離攻撃クラス
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
	static const int            kComboMax;        // 最大コンボ数
	const int                     m_ComboCount;  // コンボ数
	LacrosseAttackClose* m_pAttackClass;  // 近接攻撃クラス
	bool                            m_DoCombo;      // コンボするかどうか

	// 近接攻撃クラス作成
	LacrosseAttackClose* CreateAttackClass(LacrossePlayer* t, lacrosse_player::MotionType motion);
};


class LacrosseEvasion;
//***************************************************
//		プレイヤー操作の回避クラス
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
	LacrosseEvasion* m_pEvasionClass; // 回避クラス

	// 回避クラス作成
	LacrosseEvasion* CreateEvasionClass(LacrossePlayer* t);
};
