#include "TennisPlayerState_Counter.h"
#include "TennisPlayerState_UsualMove.h"
#include "../../GameSystem/GameController.h"
#include "../Template/CharacterFunction.h"
#include "../../Ball/UsualBall.h"
#include "../../Damage/Damage.h"
#include "../Template/CharacterCounterClass.h"
#include "../Template/CharacterMoveClass.h"
#include "../Template/CharacterShotAttackClass.h"


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
	m_pCounter->Update();

	//モデルのワールド変換行列を更新
	chr_func::CreateTransMatrix(t, 0.05f, &t->m_Renderer.m_TransMatrix);
}


// ステート終了
void TennisState_PlayerControll_Counter::Exit(TennisPlayer* t)
{
	delete m_pCounter;
}


// カウンター構えクラス作成
CharacterCounter* TennisState_PlayerControll_Counter::CreateCounterClass(TennisPlayer* t)
{
	class CounterEvent : public CharacterCounter::CounterEvent
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
			//MyDebugString("CounterBall is Enter.\n");
		}

		// レベルアップ
		void LevelUp(int level)override
		{
			m_CounterLevel = level;
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
			//MyDebugString("Hit Ball.\n");
		}
	};

	// パラメータ設定
	CharacterCounter::CounterParams params;
	params.MaxCounterLevel = 3;
	params.MaxPoseFrame = 60;
	params.LevelUpFrame = 45;
	params.SwingTotalFrame = 15;
	params.MoveToBallFrame = 2;
	params.NormalCounterArea = 10.0f;
	params.JustCounterArea = 5.0f;
	params.DamageReceiveArea = 0.5f;
	params.MoveDownSpeed = 0.2f;


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

	return new CharacterCounter(
		t,
		params,
		new CounterEvent(t)
		);
}