#include "TennisPlayerState.h"
#include "../../GameSystem/GameController.h"
#include "../CharacterFunction.h"
#include "../../Ball/UsualBall.h"
#include "../../Damage/Damage.h"
#include "../CharacterCounterClass.h"
#include "../CharacterMoveClass.h"
#include "../CharacterShotAttackClass.h"

//****************************************************
//	テニスプレイヤーの操作クラスヘッダー
//****************************************************

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


	if (controller::GetTRG(controller::button::sankaku, t->m_PlayerInfo.number))
	{// [△] でボール発射
		t->SetState(new TennisState_PlayerControll_Shot());
	}

	if (controller::GetTRG(controller::button::_R1, t->m_PlayerInfo.number))
	{// [R1] で [カウンター構え]
		t->SetState(new TennisState_PlayerControll_Counter());
	}
}

void TennisState_PlayerControll_Move::Exit(TennisPlayer* t)
{
	delete m_pMoveClass;
}

//***************************************************
//		プレイヤー操作の カウンタークラス
//***************************************************

// ステート開始
void TennisState_PlayerControll_Counter::Enter(TennisPlayer* t)
{
	// カウンタークラス作成
	m_pCounter = CreateCounterClass(t);
}


// ステート実行
void TennisState_PlayerControll_Counter::Execute(TennisPlayer* t)
{
	// ボタン更新
	controller::button::button_state button_state;
	button_state = controller::GetButtonState(
		controller::button::_R1, 
		t->m_PlayerInfo.number
		);
	m_pCounter->SetButtonState(button_state);

	//更新
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


// カウンター構えクラス作成
CharacterCounter* TennisState_PlayerControll_Counter::CreateCounterClass(TennisPlayer* t)
{
	class CounterEvent : public CharacterCounter::Event
	{
		TennisPlayer* m_pTennis;
		int m_CounterLevel;
	public:
		// コンストラクタ
		CounterEvent(TennisPlayer* pTennisPlayer) :
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
		{// カウンター
			m_pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_Counter);
		}

		// カウンターできるボールが現れた
		void BallEnter()override
		{
			MyDebugString("CounterBall is Enter.\n");
		}

		// レベルアップ
		void LevelUp(int level)override
		{
			m_CounterLevel = level;
			MyDebugString("%d\n", level);
		}

		// カウンター開始
		void SwingStart()override
		{
			m_pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_Counter);
		}

		// カウンター終了
		void SwingEnd()override
		{// 通常移動へ
			m_pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_Stand);
			m_pTennis->SetState(new TennisState_PlayerControll_Move());
		}

		// 打ち返したとき
		void HitBall(bool is_just)override
		{
			MyDebugString("Hit Ball.\n");
		}
	};

	// パラメータ設定
	CharacterCounter::CounterParams params;
	params.MaxPoseFrame = 60;
	params.LevelUpFrame = 45;
	params.SwingTotalFrame = 30;
	params.CounterMoveFrame = 5;
	params.MoveDownSpeed = 0.2f;
	params.CanCounterArea = 10.0f;

	return new CharacterCounter(
		3,
		params,
		t,
		new CounterEvent(t)
		);
}


//****************************************************
//	テニス_プレイヤー操作の遠距離攻撃クラス
//****************************************************

void TennisState_PlayerControll_Shot::Enter(TennisPlayer* t)
{
	class ShotEvent :public CharacterShotAttack::Event
	{
		TennisPlayer* pTennis;
	public:
		ShotEvent(TennisPlayer* pTennis):
			pTennis(pTennis)
		{

		}
		void Update()
		{
			//アニメーション更新
			pTennis->m_Renderer.Update(1);

			// 転送行列更新
			chr_func::CreateTransMatrix(
				pTennis,
				0.05f,
				&pTennis->m_Renderer.m_TransMatrix);
		}

		void Shot()
		{
			//ボール発射
			BallBase::Params param;

			//移動は前向き
			chr_func::GetFront(pTennis, &param.move);
			//スピードは適当
			param.move *= 0.65f;	
			//キャラの場所に(最終的に腕の位置に？)
			param.pos = pTennis->m_Params.pos;
			//高さをキャラ共通ボール発射のYに
			param.pos.y = BallBase::UsualBallShotY;	
			//親を自分に
			param.pParent = pTennis;
			//通常タイプ
			param.type = BallBase::Type::_Usual;

			//生成
			new UsualBall(param, DamageBase::Type::_WeekDamage, 1);
		}

		void AttackStart()
		{
			pTennis->m_Renderer.SetMotion(TennisPlayer::_mt_Shot);
		}

		void AttackEnd()
		{
			//攻撃終了時に通常移動モードに戻る
			pTennis->SetState(new TennisState_PlayerControll_Move());
		}
	};

	CharacterShotAttack::AttackParams atk;

	atk.AllFrame = 40;
	atk.AttackPower = 1;
	atk.MaxTurnRadian = PI / 4;
	atk.MoveDownSpeed = 0.1f;
	atk.ShotFrame = 15;

	m_pShotClass = new CharacterShotAttack(
		t,
		new ShotEvent(t),
		atk
		);
}

void TennisState_PlayerControll_Shot::Execute(TennisPlayer* t)
{
	m_pShotClass->Update();
}

void TennisState_PlayerControll_Shot::Exit(TennisPlayer* t)
{
	delete m_pShotClass;
}