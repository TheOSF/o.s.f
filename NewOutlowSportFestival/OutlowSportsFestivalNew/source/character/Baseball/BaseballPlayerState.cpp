#include "BaseballPlayerState.h"
#include "../../GameSystem/GameController.h"
#include "../CharacterFunction.h"

#include "../CharacterEvasionClass.h"
#include "../../Ball/UsualBall.h"
#include "../../Damage/Damage.h"
#include "../CharacterCounterClass.h"

//***************************************
//　移動
//***************************************
//　ステート開始
void BaseballState_PlayerControll_Move::Enter(BaseballPlayer* b)
{
	//　移動イベントクラス(ローカルクラス)
	class BaseballMoveEvent :public CharacterUsualMove::MoveEvent
	{
		BaseballPlayer* m_pBaseball;
	public:
		BaseballMoveEvent(BaseballPlayer* pBaseball) :
			m_pBaseball(pBaseball){}

		//　アニメーション更新
		void Update(bool isRun, RATIO speed_ratio){
			m_pBaseball->m_Renderer.Update(1);
		}
		//　走り始めにモーションセット
		void RunStart(){
			m_pBaseball->m_Renderer.SetMotion(baseball_player::_mt_Run);
		}
		//　立ち始めにモーションセット
		void StandStart(){
			m_pBaseball->m_Renderer.SetMotion(baseball_player::_mt_Stand);
		}
	};

	//　ダメージイベントクラスの作成
	class BaseballDamageHitEvent :public DamageManager::HitEventBase
	{
		BaseballPlayer* m_pTennis;
	public:
		BaseballDamageHitEvent(BaseballPlayer* pTennis) :
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

	//　移動パラメータを代入
	CharacterUsualMove::Params p;

	p.Acceleration = 0.2f;
	p.MaxSpeed = 0.2f;
	p.TurnSpeed = 0.3f;
	p.DownSpeed = 0.2f;

	//　移動クラスの作成
	m_pMoveClass = new CharacterUsualMove(
		b,
		p,
		new BaseballMoveEvent(b),
		new BaseballDamageHitEvent(b)
		);
}


//　ステート実行
void BaseballState_PlayerControll_Move::Execute(BaseballPlayer* b){

	//　スティックの値を取得
	Vector2 st = controller::GetStickValue(controller::stick::left, b->m_PlayerInfo.number);

	//　スティックの値セット
	m_pMoveClass->SetStickValue(st);

	//　更新
	m_pMoveClass->Update();

	//　モデルのワールド変換行列を更新
	chr_func::CreateTransMatrix(b, 0.05f, &b->m_Renderer.m_TransMatrix);

	//　回避行動[×]
	if (controller::GetTRG(controller::button::batu, b->m_PlayerInfo.number)){
		b->SetState(new BaseballState_PlayerControll_Evasion());
		return;
	}

}

//　ステートの終了
void BaseballState_PlayerControll_Move::Exit(BaseballPlayer* b){
	delete m_pMoveClass;
}

//***************************************
//　回避
//***************************************

//　コンストラクタ
BaseballState_PlayerControll_Evasion::BaseballState_PlayerControll_Evasion():
m_pEvasionClass(nullptr)
{

}

//　ステート開始
void BaseballState_PlayerControll_Evasion::Enter(BaseballPlayer* b){
	// 回避クラス作成
	m_pEvasionClass = this->CreateEvasionClass(b);
}


//　ステート実行
void BaseballState_PlayerControll_Evasion::Execute(BaseballPlayer* b){
	// スティックの値セット
	m_pEvasionClass->SetStickValue(
		controller::GetStickValue(controller::stick::left, b->m_PlayerInfo.number));

	// 更新
	if (m_pEvasionClass->Update() == false)
	{
		return;
	}
}

//　ステート終了
void BaseballState_PlayerControll_Evasion::Exit(BaseballPlayer* b){
	delete m_pEvasionClass;
}


//　回避クラス
CharacterEvasion* BaseballState_PlayerControll_Evasion::CreateEvasionClass(BaseballPlayer* b){
	class EvasionEvent : public CharacterEvasion::Event{
		BaseballPlayer* m_pBaseball;//　野球
	public:
		//　コンストラクタ
		EvasionEvent(BaseballPlayer* pBaseball) :
			m_pBaseball(pBaseball){}

		// 更新
		void Update()override
		{
			// モデル更新
			m_pBaseball->m_Renderer.Update(1.0f);

			// 転送行列更新
			chr_func::CreateTransMatrix(
				m_pBaseball,
				0.05f,
				&m_pBaseball->m_Renderer.m_TransMatrix);
		}


		// 回避行動開始
		void EvasionStart()override
		{
			m_pBaseball->m_Renderer.SetMotion(baseball_player::_mt_Evasion);
		}


		// 回避行動終了
		void EvasionEnd()override
		{
			// 通常移動へ
			m_pBaseball->m_Renderer.SetMotion(baseball_player::_mt_Stand);
			m_pBaseball->SetState(new BaseballState_PlayerControll_Move());
		}
	};

	// 回避パラメータ設定
	CharacterEvasion::EvasionParams params;
	params.AllFrame = 35;         // 全35フレーム
	params.MaxTurnRadian = PI / 4;    // 45°
	params.MoveDownSpeed = 0.2f;      // 減速割合
	params.MoveSpeed = 0.35f;    // 移動スピード
	params.NoDamageStartFrame = 3;          // 開始3フレームで無敵開始
	params.NoDamageEndFrame = 20;       // 開始20フレームで無敵終了

	// 作成
	return new CharacterEvasion(
		b,
		new EvasionEvent(b),
		params
		);
}
