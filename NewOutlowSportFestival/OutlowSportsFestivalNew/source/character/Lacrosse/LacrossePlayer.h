#pragma once

//***************************************************
//		LacrossePlayer.h
//***************************************************

#include "../CharacterBase.h"
#include "../CharacterStateTemplate.h"
#include "../CharacterRenderer.h"


// �X�e�[�g�}�V���^���t��
class LacrossePlayer;
typedef ChrStateMachine<LacrossePlayer, CharacterBase::MsgType> LacrosseStateMachine;
typedef ChrState<LacrossePlayer, CharacterBase::MsgType> LacrosseState;



//***************************************************
//		���N���X�v���C���[
//***************************************************
class LacrossePlayer : public CharacterBase
{
private:
	LacrosseStateMachine* m_pStateMachine;  // �X�e�[�g�}�V��

public:
	CharacterRenderer	m_Renderer;  // �����_��

	// ���[�V�����^�C�v
	enum MotionType
	{
		mt_Stand,
		mt_Run,
	};

public:
	LacrossePlayer(const CharacterBase::PlayerInfo& info);
	~LacrossePlayer();
	
	// �X�e�[�g�ύX
	void SetState(LacrosseState* state);

	// �X�V
	bool Update()override;

	// �X�e�[�g�Ƀ��b�Z�[�W�𑗐M
	bool Msg(MsgType msg)override;

};
