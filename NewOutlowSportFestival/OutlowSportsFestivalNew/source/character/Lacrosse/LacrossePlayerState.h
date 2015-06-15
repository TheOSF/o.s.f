#pragma once


//*************************************************************
//
//		ラクロスの操作クラスヘッダー
//
//*************************************************************


#include "LacrossePlayer.h"
#include "../CharacterMoveClass.h"

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
