#include "LacrossePlayerState.h"
#include "../../GameSystem/GameController.h"
#include "../CharacterFunction.h"

#include "../CharacterMoveClass.h"
#include "../CharacterShotAttackClass.h"
#include "../CharacterEvasionClass.h"
#include "LacrosseAttackClose.h"
#include "LacrosseCounterPoseClass.h"

//*************************************************************
//
//		ラクロスの操作クラス
//
//*************************************************************


//***************************************************
//		プレイヤー操作の移動クラス
//     LacrosseState_PlayerControllMove
//***************************************************

// 移動時のイベントクラス作成
CharacterUsualMove* LacrosseState_PlayerControllMove::CreateMoveClass(LacrossePlayer* t)
{
	class LacrosseMoveEvent : public CharacterUsualMove::MoveEvent
	{
		LacrossePlayer* m_pLacrosse;
	public:
		LacrosseMoveEvent(LacrossePlayer* pLacrosse) :
			m_pLacrosse(pLacrosse){}

		// 更新
		void Update(bool isRun, RATIO speed_ratio)
		{
			m_pLacrosse->m_Renderer.Update(1);
		}

		// 走り出した時
		void RunStart()
		{
			m_pLacrosse->m_Renderer.SetMotion(lacrosse_player::mt_Run);
		}

		// 止まった時
		void StandStart()
		{
			m_pLacrosse->m_Renderer.SetMotion(lacrosse_player::mt_Stand);
		}
	};

	// 移動パラメータ設定
	CharacterUsualMove::Params p;
	p.Acceleration = 0.2f;
	p.MaxSpeed = 0.23f;
	p.TurnSpeed = 0.3f;
	p.DownSpeed = 0.2f;

	return new CharacterUsualMove(t, p, new LacrosseMoveEvent(t), new DamageManager::HitEventBase());
}


// ステート開始
void LacrosseState_PlayerControllMove::Enter(LacrossePlayer* t)
{
	// 移動クラス作成
	m_pMoveClass = this->CreateMoveClass(t);
}


// ステート実行
void LacrosseState_PlayerControllMove::Execute(LacrossePlayer* t)
{
	Vector2 st = controller::GetStickValue(controller::stick::left, t->m_PlayerInfo.number);

	m_pMoveClass->SetStickValue(st);
	m_pMoveClass->Update();
	chr_func::CreateTransMatrix(t, 0.05f, &t->m_Renderer.m_TransMatrix);

	if (controller::GetTRG(controller::button::batu, t->m_PlayerInfo.number))
	{// [×] で [回避]
		t->SetState(new LacrosseState_PlayerControllEvasion());
		return;
	}

	if (controller::GetTRG(controller::button::shikaku, t->m_PlayerInfo.number))
	{// [□] で [近接攻撃]
		t->SetState(new LacrosseState_PlayerControllAttackClose(0));
		return;
	}

	if (controller::GetTRG(controller::button::sankaku, t->m_PlayerInfo.number))
	{// [△] で [遠距離攻撃]
		t->SetState(new LacrosseState_PlayerControllShotAttack());
		return;
	}

	if (controller::GetTRG(controller::button::_R1, t->m_PlayerInfo.number))
	{// [R1] で [カウンター構え]
		//t->SetState(new LacrosseState_PlayerControllCounterPose());
		return;
	}
}


// ステート終了
void LacrosseState_PlayerControllMove::Exit(LacrossePlayer* t)
{
	delete m_pMoveClass;
}



//***************************************************
//		プレイヤー操作の近距離攻撃クラス
//     LacrosseState_PlayerControllAttackClose
//***************************************************

// 最大コンボ数
const int LacrosseState_PlayerControllAttackClose::kComboMax = 3;

// コンストラクタ
LacrosseState_PlayerControllAttackClose::LacrosseState_PlayerControllAttackClose(int combo) :
m_ComboCount(combo),
m_DoCombo(false),
m_pAttackClass(nullptr)
{

}


// ステート開始
void LacrosseState_PlayerControllAttackClose::Enter(LacrossePlayer* t)
{
	static const lacrosse_player::MotionType motion_type[kComboMax] = {
		lacrosse_player::mt_AttackClose_1,
		lacrosse_player::mt_AttackClose_2,
		lacrosse_player::mt_AttackClose_3
	};

	// 攻撃クラス作成
	m_pAttackClass = CreateAttackClass(t, motion_type[m_ComboCount]);
}


// ステート実行
void LacrosseState_PlayerControllAttackClose::Execute(LacrossePlayer* t)
{
	// スティックの値セット
	m_pAttackClass->SetStickValue(
		controller::GetStickValue(controller::stick::left, t->m_PlayerInfo.number));
	
	// 更新
	if (m_pAttackClass->Update() == false)
	{
		return;
	}
	
	if (controller::GetPush(controller::button::shikaku, t->m_PlayerInfo.number)&&
		m_pAttackClass->CanDoCombo())
	{// コンボフラグ オン
		m_DoCombo = true;
	}

	if (m_DoCombo&&
		m_pAttackClass->CanDoCombo()&&
		m_ComboCount+1 < kComboMax)
	{// コンボ実行
		t->SetState(new LacrosseState_PlayerControllAttackClose(m_ComboCount + 1));
		return;
	}
}


// ステート終了
void LacrosseState_PlayerControllAttackClose::Exit(LacrossePlayer* t)
{
	delete m_pAttackClass;
}


// 近接攻撃クラス作成
LacrosseAttackClose* LacrosseState_PlayerControllAttackClose::CreateAttackClass(LacrossePlayer* t, lacrosse_player::MotionType motion)
{
	static  const LacrosseAttackClose::ComboParams combo_params[kComboMax] = {
		{ 0.5f, 0.3f, PI / 4, 10, 30, 17 },
		{ 0.5f, 0.3f, PI / 4, 10, 30, 17 },
		{ 0.5f, 0.3f, PI / 4, 10, 30, 17 }
	};

	class AttackCloseEvent : public LacrosseAttackClose::Event
	{
		LacrossePlayer* m_pLacrosse; // ラクロスクラス
		const lacrosse_player::MotionType m_Motion; // 攻撃モーション
	public:
		// コンストラクタ
		AttackCloseEvent(LacrossePlayer* t, const lacrosse_player::MotionType motion) :
			m_pLacrosse(t), m_Motion(motion){}

		// 更新
		void Update()override
		{
			// モデル更新
			m_pLacrosse->m_Renderer.Update(1.0f);

			// 転送行列更新
			chr_func::CreateTransMatrix(
				m_pLacrosse,
				0.05f,
				&m_pLacrosse->m_Renderer.m_TransMatrix);
		}

		// ダメージ開始
		void DamageStart()
		{// とりあえず置いておく

		}

		// 攻撃開始
		void AttackStart()override
		{
			m_pLacrosse->m_Renderer.SetMotion(m_Motion);
		}

		// 攻撃終了
		void AttackEnd()override
		{
			// 通常移動へ
			m_pLacrosse->m_Renderer.SetMotion(lacrosse_player::mt_Stand);
			m_pLacrosse->SetState(new LacrosseState_PlayerControllMove());
		}
	};

	return new LacrosseAttackClose(
		t, 
		new AttackCloseEvent(t, motion), 
		combo_params[m_ComboCount]);
}




//***************************************************
//		プレイヤー操作の回避クラス
//     LacrosseState_PlayerControllEvasion
//***************************************************

// コンストラクタ
LacrosseState_PlayerControllEvasion::LacrosseState_PlayerControllEvasion() :
m_pEvasionClass(nullptr)
{

}


// ステート開始
void LacrosseState_PlayerControllEvasion::Enter(LacrossePlayer* t)
{
	// 回避クラス作成
	m_pEvasionClass = this->CreateEvasionClass(t);
}


// ステート実行
void LacrosseState_PlayerControllEvasion::Execute(LacrossePlayer* t)
{
	// スティックの値セット
	m_pEvasionClass->SetStickValue(
		controller::GetStickValue(controller::stick::left, t->m_PlayerInfo.number));

	// 更新
	if (m_pEvasionClass->Update() == false)
	{
		return;
	}
}


// ステート終了
void LacrosseState_PlayerControllEvasion::Exit(LacrossePlayer* t)
{
	delete m_pEvasionClass;
}


// 回避クラス作成
CharacterEvasion* LacrosseState_PlayerControllEvasion::CreateEvasionClass(LacrossePlayer* t)
{
	class EvasionEvent : public CharacterEvasion::Event
	{
		LacrossePlayer* m_pLacrosse; // ラクロス
	public:
		// コンストラクタ
		EvasionEvent(LacrossePlayer* pLacrosse) :
			m_pLacrosse(pLacrosse){}


		// 更新
		void Update()override
		{
			// モデル更新
			m_pLacrosse->m_Renderer.Update(1.0f);

			// 転送行列更新
			chr_func::CreateTransMatrix(
				m_pLacrosse, 
				0.05f, 
				&m_pLacrosse->m_Renderer.m_TransMatrix);
		}


		// 回避行動開始
		void EvasionStart()override
		{
			m_pLacrosse->m_Renderer.SetMotion(lacrosse_player::mt_Evasion);
		}


		// 回避行動終了
		void EvasionEnd()override
		{
			// 通常移動へ
			m_pLacrosse->m_Renderer.SetMotion(lacrosse_player::mt_Stand);
			m_pLacrosse->SetState(new LacrosseState_PlayerControllMove());
		}
	};

	// 回避パラメータ設定
	CharacterEvasion::EvasionParams params;
	params.AllFrame                      = 35;         // 全35フレーム
	params.MaxTurnRadian            = PI / 4;    // 45°
	params.MoveDownSpeed         = 0.2f;      // 減速割合
	params.MoveSpeed                  = 0.25f;    // 移動スピード
	params.NoDamageStartFrame = 3;          // 開始3フレームで無敵開始
	params.NoDamageEndFrame   = 20;       // 開始20フレームで無敵終了

	// 作成
	return new CharacterEvasion(
		t,
		new EvasionEvent(t),
		params
		);
}




//***************************************************
//		プレイヤー操作の 遠距離攻撃 (ボール打ち出し) クラス
//     LacrosseState_PlayerControllShotAttack
//***************************************************

// コンストラクタ
LacrosseState_PlayerControllShotAttack::LacrosseState_PlayerControllShotAttack() :
m_pAttackClass(nullptr)
{

}


// ステート開始
void LacrosseState_PlayerControllShotAttack::Enter(LacrossePlayer* t)
{
	m_pAttackClass = this->CreateAttackClass(t);
}


// ステート実行
void LacrosseState_PlayerControllShotAttack::Execute(LacrossePlayer* t)
{
	// スティックの値セット
	m_pAttackClass->SetStickValue(
		controller::GetStickValue(controller::stick::left, t->m_PlayerInfo.number)
		);

	// 更新
	if (m_pAttackClass->Update() == false)
	{
		return;
	}
}


// ステート終了
void LacrosseState_PlayerControllShotAttack::Exit(LacrossePlayer* t)
{
	delete m_pAttackClass;
}


// 回避クラス作成
CharacterShotAttack* LacrosseState_PlayerControllShotAttack::CreateAttackClass(LacrossePlayer* t)
{
	class HitBallEvent : public CharacterShotAttack::Event
	{
		LacrossePlayer* m_pLacrosse; // ラクロス
	public:
		// コンストラクタ
		HitBallEvent(LacrossePlayer* pLacrossePlayer) :
			m_pLacrosse(pLacrossePlayer){}

		// 更新
		void Update()override
		{
			// モデル更新
			m_pLacrosse->m_Renderer.Update(1.0f);

			// 転送行列更新
			chr_func::CreateTransMatrix(
				m_pLacrosse,
				0.05f,
				&m_pLacrosse->m_Renderer.m_TransMatrix);
		}

		// ダメージ判定開始
		void Shot()override
		{// とりあえず置いておく

		}


		// 攻撃開始
		void AttackStart()override
		{
			m_pLacrosse->m_Renderer.SetMotion(lacrosse_player::mt_AttackHitBall);
		}

		// 攻撃終了
		void AttackEnd()override
		{
			// 通常移動へ
			m_pLacrosse->m_Renderer.SetMotion(lacrosse_player::mt_Stand);
			m_pLacrosse->SetState(new LacrosseState_PlayerControllMove());
		}
	};

	// 攻撃パラメータ作成
	CharacterShotAttack::AttackParams params;
	params.AllFrame                        = 30;     // 全30フレーム
	params.AttackPower                  = 10.0f; // 攻撃力
	params.ShotFrame                     = 5;       // 開始5フレームで球発射
	params.MaxTurnRadian              = PI / 4; // 45°
	params.MoveDownSpeed           = 0.2f;   // 減速割合

	// 生成して返す
	/*
	return new CharacterShotAttack(
		t,
		new HitBallEvent(t),
		params,
		);
		*/

	return 0;
}

