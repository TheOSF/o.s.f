#include "CharacterMoveClass.h"
#include "CharacterFunction.h"
#include "CharacterBase.h"
#include "../Damage/Damage.h"
#include "../Ball/Ball.h"
#include "../Camera/Camera.h"

//****************************************************************
//		キャラクタ共通の動きクラス
//****************************************************************

CharacterUsualMove::CharacterUsualMove(
	CharacterBase*					pParent,	//操るキャラクタのポインタ
	const Params&					param,		//移動パラメータ構造体
	MoveEvent*						pMoveEvent,	//移動イベントに反応するクラス
	DamageManager::HitEventBase*	pHitEventBase//ダメージを受けた時に反応するクラス
	) :
	m_StickValue(0, 0),
	m_pParent(pParent),
	m_isRun(false),
	m_pMoveEvent(pMoveEvent),
	m_pHitEventBase(pHitEventBase)
{
	m_Params = param;
}

CharacterUsualMove:: ~CharacterUsualMove()
{
	delete m_pMoveEvent;
}

void CharacterUsualMove::Update()
{
	//走っているかどうか
	bool now = Vector2Length(m_StickValue) > 0.1f;

	//イベントクラスの更新
	m_pMoveEvent->Update(now, (m_Params.MaxSpeed > 0.0f) ? (Vector3XZLength(m_pParent->m_Params.move) / m_Params.MaxSpeed) : (0));

	//走っているorいない処理の実行
	if (now)
	{
		//前に加速し、方向をスティックの向きに
		chr_func::AddMoveFront(m_pParent, m_Params.Acceleration, m_Params.MaxSpeed);
		
		chr_func::AngleControll(
			m_pParent,
			m_pParent->m_Params.pos + DefCamera.GetRight()*m_StickValue.x + DefCamera.GetForward()*m_StickValue.y, 
			m_Params.TurnSpeed
			);
	}
	else
	{
		//減速
		chr_func::XZMoveDown(m_pParent, m_Params.DownSpeed);
	}

	//イベントクラスの関数の呼び出し
	if (now != m_isRun)
	{
		m_isRun = now;
		if (now)
		{
			m_pMoveEvent->RunStart();
		}
		else
		{
			m_pMoveEvent->StandStart();
		}
	}

	//あたり判定をとる
	ShpereParam sp;

	sp.pos = m_pParent->m_Params.pos;
	sp.pos.y += BallBase::UsualBallShotY;
	sp.size = m_pParent->m_Params.hitScale;

	DefDamageMgr.HitCheckSphere(sp, *m_pHitEventBase);


	//位置の更新
	chr_func::PositionUpdate(m_pParent);
}

void CharacterUsualMove::SetStickValue(CrVector2 StickValue)
{
	m_StickValue = StickValue;
}