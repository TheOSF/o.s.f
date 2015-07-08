#include "BaseballPlayerState_DamageMotionWeak.h"
//#include "BaseballPlayerState_UsualMove.h"
#include "Baseball_HitEvent.h"
#include "../CharacterFunction.h"

BaseballState_DamageMotion_Weak::BaseballState_DamageMotion_Weak(
	BaseballPlayer* pBaseball,
	const Vector3& Damage_vec  //ダメージを受けた方向
	) :
	m_pBaseball(pBaseball),
	m_Damage_vec(Damage_vec)
{

}

void BaseballState_DamageMotion_Weak::Enter(BaseballPlayer* t)
{
	//キャラクタ共通ひるみクラスのテニス固有イベントクラス
	class BaseballEvent :public CharacterDamageMotion::Event
	{
	public:
		BaseballEvent(BaseballPlayer* pBaseball) :m_pBaseball(pBaseball){}

		void Update(float speed)
		{
			//モデルの更新のみ
			m_pBaseball->m_Renderer.Update(speed);
			//chr_func::CreateTransMatrix(m_pBaseball, m_pBaseball->m_ModelSize, &m_pBaseball->m_Renderer.m_TransMatrix);
		}
		void Start()
		{
			//ひるみモーションをセット
			//m_pBaseball->m_Renderer.SetMotion(BaseballPlayer::_mt_Damage_Weak);
		}
		void End()
		{
			//通常ステートをセット
		//	m_pBaseball->SetState(
		//		BaseballState_PlayerControll_Move::GetPlayerControllMove(m_pBaseball)
		//		);
		}
	private:
		BaseballPlayer*  m_pBaseball;
	};

	//ダメージモーションパラメーターを作成する
	CharacterDamageMotion::Params Param;

	Param.AllFrame = 35;
	Param.damage_vec = m_Damage_vec;
	Param.hitBack = 0.5f;
	Param.hitStopFrame = 0;
	Param.NoDamageFrame = 10;

	//ひるみクラスを作成
	m_pDamageMotionClass = new CharacterDamageMotion(
		m_pBaseball,
		new BaseballEvent(m_pBaseball),
		new BaseballHitEvent(m_pBaseball),
		Param
		);

}

void BaseballState_DamageMotion_Weak::Execute(BaseballPlayer* t)
{
	m_pDamageMotionClass->Update();
}

void BaseballState_DamageMotion_Weak::Exit(BaseballPlayer* t)
{

}