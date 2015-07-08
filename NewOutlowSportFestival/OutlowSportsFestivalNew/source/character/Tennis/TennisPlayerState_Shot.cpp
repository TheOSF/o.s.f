#include "TennisPlayerState_Shot.h"
#include "TennisPlayerState_UsualMove.h"
#include "Tennis_HitEvent.h"
#include "../../GameSystem/GameController.h"
#include "../CharacterFunction.h"
#include "../../Ball/UsualBall.h"
#include "../../Damage/Damage.h"
#include "../CharacterCounterClass.h"
#include "../CharacterMoveClass.h"
#include "../CharacterShotAttackClass.h"


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
		atk,
		new TennisHitEvent(t)
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