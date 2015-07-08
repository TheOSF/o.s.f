#include "BaseballPlayerState.h"
#include "Baseball_HitEvent.h"
#include "../../GameSystem/GameController.h"
#include "../CharacterFunction.h"
#include "../CharacterManager.h"
#include "../CharacterEvasionClass.h"

#include "../../Ball/UsualBall.h"
#include "../../Ball/MilderHoming.h"
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

	//　切り替え

	SetBatterFlg(b);
	//　実行パターン
	if (batterflg){
		//　バッター時
		Batter(b);
	}
	else{
		//　投手時
		Pitcher(b);
	}

}

//　ステートの終了
void BaseballState_PlayerControll_Move::Exit(BaseballPlayer* b){
	delete m_pMoveClass;
}

//　バッター時
void BaseballState_PlayerControll_Move::Batter(BaseballPlayer* b){
	//　遠距離攻撃[△]
	if (controller::GetTRG(controller::button::sankaku, b->m_PlayerInfo.number)){
		b->SetState(new BaseballState_PlayerControll_ShotAttack_B());
		return;
	}
	//　回避行動[×]
	if (controller::GetTRG(controller::button::batu, b->m_PlayerInfo.number)){
		b->SetState(new BaseballState_PlayerControll_Evasion(0.25f));
		return;
	}
}

//　投手時
void  BaseballState_PlayerControll_Move::Pitcher(BaseballPlayer* b){
	//　遠距離攻撃[△]
	if (controller::GetTRG(controller::button::sankaku, b->m_PlayerInfo.number)){
		b->SetState(new BaseballState_PlayerControll_ShotAttack_P());
		return;
	}
	//　回避行動[×]
	if (controller::GetTRG(controller::button::batu, b->m_PlayerInfo.number)){
		b->SetState(new BaseballState_PlayerControll_Evasion(0.65f));
		return;
	}
}
//***************************************
//　回避
//***************************************

//　コンストラクタ
BaseballState_PlayerControll_Evasion::BaseballState_PlayerControll_Evasion(float speed) :
m_pEvasionClass(nullptr)
{
	roolspeed = speed;
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
	params.MoveSpeed = roolspeed;    // 移動スピード
	params.NoDamageStartFrame = 3;          // 開始3フレームで無敵開始
	params.NoDamageEndFrame = 20;       // 開始20フレームで無敵終了

	// 作成
	return new CharacterEvasion(
		b,
		new EvasionEvent(b),
		params
		);
}

//***************************************
//　遠距離(バッター)
//***************************************

//　コンストラクタ
BaseballState_PlayerControll_ShotAttack_B::BaseballState_PlayerControll_ShotAttack_B():m_pShotAttackClass_B(nullptr){

}


//　ステート開始
void BaseballState_PlayerControll_ShotAttack_B::Enter(BaseballPlayer* b){
	// 回避クラス作成
	m_pShotAttackClass_B = this->CreateShotAttackClass_B(b);
}


//　ステート実行
void BaseballState_PlayerControll_ShotAttack_B::Execute(BaseballPlayer* b){
	// スティックの値セット
	m_pShotAttackClass_B->SetStickValue(
		controller::GetStickValue(controller::stick::left, b->m_PlayerInfo.number));

	// 更新
	if (m_pShotAttackClass_B->Update() == false)
	{
		return;
	}
}

//　ステート終了
void BaseballState_PlayerControll_ShotAttack_B::Exit(BaseballPlayer* b){
	delete m_pShotAttackClass_B;
}




//　遠距離クラス
CharacterShotAttack* BaseballState_PlayerControll_ShotAttack_B::CreateShotAttackClass_B(BaseballPlayer* b){
	class ShotAttackEvent_B :public CharacterShotAttack::Event{
		BaseballPlayer* m_pBaseball;//　野球
	public:
		//　コンストラクタ
		ShotAttackEvent_B(BaseballPlayer* pBaseball) :
			m_pBaseball(pBaseball){}
		//　更新
		void Update()override{
			//　モデル更新
			m_pBaseball->m_Renderer.Update(1.0f);

			// 転送行列更新
			chr_func::CreateTransMatrix(
				m_pBaseball,
				0.05f,
				&m_pBaseball->m_Renderer.m_TransMatrix);
		}

		// ダメージ判定開始 & ボール発射
		void Shot()
		{
			//ボール発射
			BallBase::Params param;

			//　遠距離攻撃(param計算)
			param = m_pBaseball->BaseballShot(m_pBaseball, param);

			//生成
			new UsualBall(param, DamageBase::Type::_WeekDamage, 1);
		}

		//　遠距離攻撃開始
		void AttackStart()override{
			//　☆モーション
			m_pBaseball->m_Renderer.SetMotion(baseball_player::_mt_Shot);
		}

		void AttackEnd()
		{
			//攻撃終了時に通常移動モードに戻る
			m_pBaseball->SetState(new BaseballState_PlayerControll_Move());
		}
	};

	CharacterShotAttack::AttackParams atk;

	atk.AllFrame = 40;
	atk.AttackPower = 8;
	atk.MaxTurnRadian = PI / 4;
	atk.MoveDownSpeed = 0.8f;
	atk.ShotFrame = 15;

	return m_pShotAttackClass_B = new CharacterShotAttack(
		b,
		new ShotAttackEvent_B(b),
		atk,
		new  BaseballHitEvent(b)
		);
}


//***************************************
//　遠距離(投手)
//***************************************
class ShotAttackEvent_P;
//　コンストラクタ
BaseballState_PlayerControll_ShotAttack_P::BaseballState_PlayerControll_ShotAttack_P() :m_pShotAttackClass_P(nullptr){

}


//　ステート開始
void BaseballState_PlayerControll_ShotAttack_P::Enter(BaseballPlayer* b){
	// 回避クラス作成
	m_pShotAttackClass_P = this->CreateShotAttackClass_P(b);
}


//　ステート実行
void BaseballState_PlayerControll_ShotAttack_P::Execute(BaseballPlayer* b){
	// スティックの値セット
	m_pShotAttackClass_P->SetStickValue(
		controller::GetStickValue(controller::stick::left, b->m_PlayerInfo.number));

	// 更新
	if (m_pShotAttackClass_P->Update() == false)
	{
		return;
	}
}

//　ステート終了
void BaseballState_PlayerControll_ShotAttack_P::Exit(BaseballPlayer* b){
	delete m_pShotAttackClass_P;
}


//　遠距離クラス
CharacterShotAttack* BaseballState_PlayerControll_ShotAttack_P::CreateShotAttackClass_P(BaseballPlayer* b){
	class ShotAttackEvent_P :public CharacterShotAttack::Event{
		BaseballPlayer* m_pBaseball;//　野球
	public:
		//　ボール
		BallBase::Params param;
		//　ターゲット
		Vector3 target;
	public:
		//　コンストラクタ
		ShotAttackEvent_P(BaseballPlayer* pBaseball) :
			m_pBaseball(pBaseball){}
		//　更新
		void Update()override{
			//　モデル更新
			m_pBaseball->m_Renderer.Update(1.0f);

			// 転送行列更新
			chr_func::CreateTransMatrix(
				m_pBaseball,
				0.05f,
				&m_pBaseball->m_Renderer.m_TransMatrix);
		}
	public:
		// ダメージ判定開始 & ボール発射
		void Shot()
		{
			//　遠距離攻撃(param計算)
			param = m_pBaseball->BaseballShot(m_pBaseball, param);
			//　ターゲット決定
			param = m_pBaseball->TargetDecision(param, target);
			
			//生成
			new MilderHoming(m_pBaseball, param, target, DamageBase::Type::_WeekDamage, 1);
		}

		//　遠距離攻撃開始
		void AttackStart()override{
			//　☆モーション
			m_pBaseball->m_Renderer.SetMotion(baseball_player::_mt_Shot);
		}
		
		void AttackEnd()
		{
			//攻撃終了時に通常移動モードに戻る
			m_pBaseball->SetState(new BaseballState_PlayerControll_Move());
		}
	};

	CharacterShotAttack::AttackParams atk;

	atk.AllFrame = 40;
	atk.AttackPower = 8;
	atk.MaxTurnRadian = PI / 4;
	atk.MoveDownSpeed = 0.8f;
	atk.ShotFrame = 15;

	return m_pShotAttackClass_P = new CharacterShotAttack(
		b,
		new ShotAttackEvent_P(b),
		atk,
		new  BaseballHitEvent(b)
		);
}
