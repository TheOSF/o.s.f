#include "TennisPlayerState.h"
#include "../../GameSystem/GameController.h"
#include "../CharacterFunction.h"
#include "../../Ball/UsualBall.h"
#include "../../Damage/Damage.h"
#include "../CharacterCounterPoseClass.h"
#include "../CharacterCounterClass.h"


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
		param.pos.y=BallBase::UsualBallShotY;
		param.pParent = t;
		param.type = BallBase::Type::_Usual;

		new UsualBall(param, DamageBase::Type::_WeekDamage, 1);
	}

	if (controller::GetTRG(controller::button::_R1, t->m_PlayerInfo.number))
	{// [R1] で [カウンター構え]
		t->SetState(new TennisState_PlayerControll_CounterPose());
	}
}

void TennisState_PlayerControll_Move::Exit(TennisPlayer* t)
{
	delete m_pMoveClass;
}



//***************************************************
//		プレイヤー操作の カウンター構えクラス
//***************************************************

// ステート開始
void TennisState_PlayerControll_CounterPose::Enter(TennisPlayer* t)
{
	// カウンター構えクラス作成
	m_pCounterPose = CreateCounterPoseClass(t);
}


// ステート実行
void TennisState_PlayerControll_CounterPose::Execute(TennisPlayer* t)
{
	//更新
	if (m_pCounterPose->Update() == false)
	{
		return;
	}

	if (controller::GetLeave(controller::button::_R1, t->m_PlayerInfo.number))
	{// [R1離す] でカウンター
		t->m_Renderer.SetMotion(TennisPlayer::_mt_Counter);

		// カウンターレベル取得
		int level = m_pCounterPose->GetLevel();

		// カウンターステートへ
		t->SetState(new TennisState_PlayerControll_Counter(level));
		return;
	}
}


// ステート終了
void TennisState_PlayerControll_CounterPose::Exit(TennisPlayer* t)
{
	delete m_pCounterPose;
}


// カウンター構えクラス作成
CharacterCounterPose* TennisState_PlayerControll_CounterPose::CreateCounterPoseClass(TennisPlayer* t)
{
	class CounterPoseEvent : public CharacterCounterPose::Event
	{
		TennisPlayer* m_pTennis;
		int m_CounterLevel;
	public:
		// コンストラクタ
		CounterPoseEvent(TennisPlayer* pTennisPlayer) :
			m_pTennis(pTennisPlayer),
			m_CounterLevel(0){}

		// 更新
		void Update()override
		{
			// モデル更新
			m_pTennis->m_Renderer.Update(1);

			// 転送行列更新
			chr_func::CreateTransMatrix(
				m_pTennis,
				0.05f,
				&m_pTennis->m_Renderer.m_TransMatrix);
		}

		// 構え開始
		void PoseStart()override
		{
			m_pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_CounterPose);
		}

		// 構え終了
		void PoseEnd()override
		{
			// カウンターへ
			m_pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_Counter);
			m_pTennis->SetState(new TennisState_PlayerControll_Counter(m_CounterLevel));
		}

		// レベルアップ
		void LevelUp(int level)override
		{
			m_CounterLevel = level;
			MyDebugString("%d\n", level);
		}
	};

	// パラメータ設定
	CharacterCounterPose::CounterPoseParams params;
	params.MaxPoseFrame = 60;
	params.LevelUpFrame = 45;
	params.MoveDownSpeed = 0.2f;

	return new CharacterCounterPose(
		3,
		params,
		t,
		new CounterPoseEvent(t)
		);
}


//***************************************************
//		プレイヤー操作の カウンター構えクラス
//***************************************************

// コンストラクタ
TennisState_PlayerControll_Counter::TennisState_PlayerControll_Counter(int level) :
m_Level(level),
m_pCounter(nullptr)
{

}


// ステート開始
void TennisState_PlayerControll_Counter::Enter(TennisPlayer* t)
{
	// カウンタークラス作成
	m_pCounter = this->CreateCounterClass(t, m_Level);
}


// ステート実行
void TennisState_PlayerControll_Counter::Execute(TennisPlayer* t)
{
	// スティックの値取得
	Vector2 stickValue = controller::GetStickValue(controller::stick::left, t->m_PlayerInfo.number);
	
	// スティックの値セット
	m_pCounter->SetStickValue(stickValue);

	// 更新
	if (m_pCounter->Update() == false)
	{
		return;
	}
}


// ステート終了
void TennisState_PlayerControll_Counter::Exit(TennisPlayer* t)
{
	delete m_pCounter;
}


// カウンタークラス作成
CharacterCounter* TennisState_PlayerControll_Counter::CreateCounterClass(TennisPlayer* t, int level)
{
	class CounterEvent : public CharacterCounter::Event
	{
		TennisPlayer* m_pTennis;
	public:
		// コンストラクタ
		CounterEvent(TennisPlayer* pTennisPlayer) :
			m_pTennis(pTennisPlayer){}

		// 更新
		void Update()override
		{
			// モデル更新
			m_pTennis->m_Renderer.Update(1.0f);

			// 転送行列更新
			chr_func::CreateTransMatrix(
				m_pTennis,
				0.05f,
				&m_pTennis->m_Renderer.m_TransMatrix);
		}

		// カウンター開始
		void CounterStart(int level)override
		{
			m_pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_Counter);
		}

		// カウンター終了
		void CounterEnd()override
		{// 通常移動へ
			m_pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_Stand);
			m_pTennis->SetState(new TennisState_PlayerControll_Move());
		}
	};

	// カウンターパラメータ設定
	CharacterCounter::CounterParams params;
	params.Level                    = level;  // レベル
	params.MoveDownSpeed = 0.2f;   // 減速割合
	params.TotalFrame           = 60;     // 全フレーム

	// 生成して返す
	return new CharacterCounter(
		params,
		t,
		new CounterEvent(t)
		);
}

