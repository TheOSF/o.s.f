#ifndef __BASEBALL_PLAYER_STATE_H__
#define __BASEBALL_PLAYER_STATE_H__

#include "BaseballPlayer.h"

<<<<<<< HEAD
#include "../Template/CharacterMoveClass.h"

=======
#include "../CharacterMoveClass.h"
#include "../CharacterShotAttackClass.h"
>>>>>>> c4abe03b37255dbd8036da53888bca9bc4e32b7e
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

//プレイヤー操作の遠距離クラス(バッター)
class CharacterShotAttack;
class BaseballState_PlayerControll_ShotAttack_B :public BaseballState{
private:
	//　遠距離クラス作成(バッター)
	CharacterShotAttack* CreateShotAttackClass_B(BaseballPlayer* b);
private:
	//　遠距離クラス
	CharacterShotAttack* m_pShotAttackClass_B;
public:
	//　コンストラクタ
	BaseballState_PlayerControll_ShotAttack_B();
	//　ステート開始
	void Enter(BaseballPlayer* b)override;
	//　ステート実行
	void Execute(BaseballPlayer* b)override;
	//　ステート終了
	void Exit(BaseballPlayer* b)override;
};

//プレイヤー操作の遠距離クラス(ピッチャー)
class CharacterShotAttack;
class BaseballState_PlayerControll_ShotAttack_P :public BaseballState{
private:
	//　遠距離クラス作成(ピッチャー)
	CharacterShotAttack* CreateShotAttackClass_P(BaseballPlayer* b);
private:
	//　遠距離クラス
	CharacterShotAttack* m_pShotAttackClass_P;
public:
	
	//　コンストラクタ
	BaseballState_PlayerControll_ShotAttack_P();
	//　ステート開始
	void Enter(BaseballPlayer* b)override;
	//　ステート実行
	void Execute(BaseballPlayer* b)override;
	//　ステート終了
	void Exit(BaseballPlayer* b)override;
	
};

#endif