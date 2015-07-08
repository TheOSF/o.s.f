#include "TennisPlayerState_UsualMove.h"
#include "TennisPlayerState_Shot.h"
#include "TennisPlayerState_Counter.h"
#include "../../GameSystem/GameController.h"
#include "../CharacterFunction.h"
#include "../../Ball/UsualBall.h"
#include "../../Damage/Damage.h"
#include "../CharacterCounterClass.h"
#include "../CharacterMoveClass.h"
#include "../CharacterShotAttackClass.h"
#include "Tennis_HitEvent.h"


//****************************************************
//	テニスプレイヤーの操作クラスヘッダー
//****************************************************

TennisState* TennisState_PlayerControll_Move::GetPlayerControllMove(
	TennisPlayer* pt)
{
	switch (pt->m_PlayerInfo.player_type)
	{
	case PlayerType::_Player:
		return new TennisState_PlayerControll_Move();

	case PlayerType::_Computer:
		switch (pt->m_PlayerInfo.strong_type)
		{
		case StrongType::_Weak:
			//return new 弱い通常移動
		case StrongType::_Usual:
			//return new 弱い通常移動
		case StrongType::_Strong:
			//return new 弱い通常移動
		default:break;
		}
	default:break;
	}

	assert("通常ステートが作成できないキャラクタタイプです TennisState_PlayerControll_Move::GetPlayerControllMove" && 0);
	return nullptr;
}

//ステート開始
void TennisState_PlayerControll_Move::Enter(TennisPlayer* t)
{
	//移動イベントクラス
	class TennisMoveEvent :public CharacterUsualMove::MoveEvent
	{
		TennisPlayer* m_pTennis;
	public:
		TennisMoveEvent(TennisPlayer* pTennis) :
			m_pTennis(pTennis){}

		//アニメーションの更新
		void Update(bool isRun, RATIO speed_ratio)
		{
			m_pTennis->m_Renderer.Update(1);
		}
		//走り始めにモーションをセット
		void RunStart()
		{
			m_pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_Run);
		}
		//立ちはじめにモーションをセット
		void StandStart()
		{
			m_pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_Stand);
		}
	};

	//移動パラメータを代入
	CharacterUsualMove::Params p;

	p.Acceleration = 0.2f;
	p.MaxSpeed = 0.2f;
	p.TurnSpeed = 0.3f;
	p.DownSpeed = 0.2f;

	//移動クラスの作成
	m_pMoveClass = new CharacterUsualMove(
		t,
		p,
		new TennisMoveEvent(t),
		new TennisHitEvent(t)
		);
}


void TennisState_PlayerControll_Move::Execute(TennisPlayer* t)
{
	//スティックの値を取得
	Vector2 st = controller::GetStickValue(controller::stick::left, t->m_PlayerInfo.number);

	//スティックの値セット
	m_pMoveClass->SetStickValue(st);

	//更新
	m_pMoveClass->Update();

	//モデルのワールド変換行列を更新
	chr_func::CreateTransMatrix(t, t->m_ModelSize, &t->m_Renderer.m_TransMatrix);


	if (controller::GetTRG(controller::button::sankaku, t->m_PlayerInfo.number))
	{// [△] でボール発射
		t->SetState(new TennisState_PlayerControll_Shot());
	}

	if (controller::GetTRG(controller::button::_R1, t->m_PlayerInfo.number))
	{// [R1] で [カウンター]
		t->SetState(new TennisState_PlayerControll_Counter());
	}
}

void TennisState_PlayerControll_Move::Exit(TennisPlayer* t)
{
	delete m_pMoveClass;
}


