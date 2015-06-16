#pragma once


//*************************************************************
//
//		ラクロスの操作クラスヘッダー
//
//*************************************************************


#include "LacrossePlayer.h"
#include "../CharacterMoveClass.h"
#include "LacrosseAttackClose.h"

//***************************************************
//		プレイヤー操作の移動クラス
//***************************************************
class LacrosseState_PlayerControllMove : public LacrosseState
{
private:
	CharacterUsualMove* m_pMoveClass;  // キャラクター共通の移動クラス

	// 移動時のイベントクラス作成
	CharacterUsualMove::MoveEvent* CreateMoveEvent(LacrossePlayer* t);

public:
	// ステート開始
	void Enter(LacrossePlayer* t)override;

	// ステート実行
	void Execute(LacrossePlayer* t)override;

	// ステート終了
	void Exit(LacrossePlayer* t)override;

};


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
