#include "TennisPlayerState.h"
#include "../../GameSystem/GameController.h"
#include "../CharacterFunction.h"
#include "../../Ball/UsualBall.h"
#include "../../Damage/Damage.h"


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

	//ダメージイベントクラスの作成
	class TennisDamageHitEvent :public DamageManager::HitEventBase
	{
		TennisPlayer* m_pTennis;
	public:
		TennisDamageHitEvent(TennisPlayer* pTennis) :
			m_pTennis(pTennis){}

		//当たった時にそのダメージの種類から、それぞれのステートに派生させる
		bool Hit(DamageBase* pDmg)
		{
			bool ret = true;

			switch (pDmg->type)
			{
			case DamageBase::Type::_WeekDamage:
				//m_pTennis->SetState();	ステートができていないため
				break;
			case DamageBase::Type::_VanishDamage:
				//m_pTennis->SetState();
				break;
			case DamageBase::Type::_UpDamage:
				//m_pTennis->SetState();
				break;
			default:
				ret = false;
				break;
			}

			return ret;
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
		new TennisDamageHitEvent(t)
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
	chr_func::CreateTransMatrix(t, 0.05f, &t->m_Renderer.m_TransMatrix);

	//ボール発射(仮)
	if (controller::GetTRG(controller::button::sankaku, t->m_PlayerInfo.number))
	{
		BallBase::Params param;

		chr_func::GetFront(t, &param.move);
		param.move *= 0.5f;
		param.pos = t->m_Params.pos;
		param.pParent = t;
		param.type = BallBase::Type::_Usual;

		new UsualBall(param, DamageBase::Type::_WeekDamage, 1);
	}
}

void TennisState_PlayerControll_Move::Exit(TennisPlayer* t)
{
	delete m_pMoveClass;
}
