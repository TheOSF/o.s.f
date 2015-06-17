#pragma once

//***************************************************
//		LacrossePlayer.h
//***************************************************

#include "../CharacterBase.h"
#include "../CharacterStateTemplate.h"
#include "../CharacterRenderer.h"


// ステートマシン型名付け
class LacrossePlayer;
typedef ChrStateMachine<LacrossePlayer, CharacterBase::MsgType> LacrosseStateMachine;
typedef ChrState<LacrossePlayer, CharacterBase::MsgType> LacrosseState;


namespace lacrosse_player
{
	// モーションタイプ
	enum MotionType
	{
		mt_Stand,
		mt_Run,

		mt_AttackClose_1,  // 近距離１段目
		mt_AttackClose_2 = 15,  // 近距離２段目
		mt_AttackClose_3 = 16,  // 近距離３段目


		mt_Evasion = 5,  // 回避

		mt_AttackHitBall = 3, // 遠距離攻撃
	};


#if 0
	// できる行動のタイプ
	enum StateType
	{
		st_UsualMove,  // 通常移動

		st_AttackClose_1, // 近距離１段目
		st_AttackClose_2, // 近距離２段目
		st_AttackClose_3, // 近距離３段目
	};
#endif

}


//***************************************************
//		ラクロスプレイヤー
//***************************************************
class LacrossePlayer : public CharacterBase
{
private:
	LacrosseStateMachine* m_pStateMachine;  // ステートマシン

public:
	CharacterRenderer	m_Renderer;  // レンダラ

public:
	LacrossePlayer(const CharacterBase::PlayerInfo& info);
	~LacrossePlayer();
	
	// ステート変更
	void SetState(LacrosseState* state);

	// 更新
	bool Update()override;

	// ステートにメッセージを送信
	bool Msg(MsgType msg)override;

};
