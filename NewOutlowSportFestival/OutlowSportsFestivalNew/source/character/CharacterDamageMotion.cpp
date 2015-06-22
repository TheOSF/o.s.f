#include "CharacterDamageMotion.h"
#include "CharacterFunction.h"
#include "CharacterBase.h"


CharacterDamageMotion::CharacterDamageMotion(
	CharacterBase* pCharacter,
	Event* pEvent,
	const Params& params
	):
	m_pCharacter(pCharacter),
	m_Timer(0),
	m_pEvent(pEvent),
	m_Start(false),
	m_End(false)
{
	m_Params = params;
}

CharacterDamageMotion::~CharacterDamageMotion()
{
	delete m_pEvent;
}


// 更新
void CharacterDamageMotion::Update()
{
	//フレーム更新
	++m_Timer;

	if (m_Start == false)
	{
		//キャラクタをダメージの方向に向かせる
		chr_func::AngleControll(
			m_pCharacter,
			m_pCharacter->m_Params.pos - m_Params.damage_vec
			);

		//スタートイベント呼び出し
		m_pEvent->Start();
	}

	//無敵フレーム判定
	if (m_Timer > m_Params.NoDamageFrame)
	{
		//ダメージ判定
		
		//chr_func::DamageCheck();
	}

	//イベントクラス更新
	m_pEvent->Update((m_Timer < m_Params.hitStopFrame) ? (0.2f) : (1.0f));

	//終了判定
	if (m_End == false &&
		m_Params.AllFrame <= m_Timer)
	{
		m_End = true;
		m_pEvent->End();
	}
}