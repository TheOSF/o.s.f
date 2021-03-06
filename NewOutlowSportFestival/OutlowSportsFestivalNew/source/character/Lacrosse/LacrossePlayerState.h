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


class CharacterEvasion;
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
	CharacterEvasion* CreateEvasionClass(LacrossePlayer* t);

private:
	CharacterEvasion* m_pEvasionClass; // 回避クラス
};


class CharacterShotAttack;
//***************************************************
//		プレイヤー操作の 遠距離攻撃 (ボール打ち出し) クラス
//***************************************************
class LacrosseState_PlayerControllShotAttack : public LacrosseState
{
public:
	// コンストラクタ
	LacrosseState_PlayerControllShotAttack();

	// ステート開始
	void Enter(LacrossePlayer* t)override;

	// ステート実行
	void Execute(LacrossePlayer* t)override;

	// ステート終了
	void Exit(LacrossePlayer* t)override;

private:
	// 攻撃クラス作成
	CharacterShotAttack* CreateAttackClass(LacrossePlayer* t);

private:
	CharacterShotAttack* m_pAttackClass; // 攻撃クラス
};




