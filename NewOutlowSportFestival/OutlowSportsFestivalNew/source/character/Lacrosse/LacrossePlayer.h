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



//***************************************************
//		ラクロスプレイヤー
//***************************************************
class LacrossePlayer : public CharacterBase
{
private:
	LacrosseStateMachine* m_pStateMachine;  // ステートマシン

public:
	CharacterRenderer	m_Renderer;  // レンダラ

	// モーションタイプ
	enum MotionType
	{
		mt_Stand,
		mt_Run,
	};

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
