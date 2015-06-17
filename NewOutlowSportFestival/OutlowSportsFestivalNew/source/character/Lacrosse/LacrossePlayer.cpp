#include "LacrossePlayer.h"


//***************************************************
//		���N���X�v���C���[
//***************************************************

//----------------------------------------------
//     �R���X�g���N�^�E�f�X�g���N�^
//----------------------------------------------

// �R���X�g���N�^
LacrossePlayer::LacrossePlayer(const CharacterBase::PlayerInfo& info) :
CharacterBase(info),
m_HaveBall(false), 
m_Renderer(new BlendAnimationMesh("DATA\\CHR\\Golfer\\Player_G.iem"))
{
	m_pStateMachine = new LacrosseStateMachine(this);
	m_Renderer.SetMotion(2);
}


// �f�X�g���N�^
LacrossePlayer::~LacrossePlayer()
{
	delete m_pStateMachine;
}


//----------------------------------------------
//     ����
//----------------------------------------------

// �X�e�[�g�ύX
void LacrossePlayer::SetState(LacrosseState* state)
{
	// �V�����X�e�[�g���Z�b�g
	m_pStateMachine->set_state(state);
}


// �X�V
bool LacrossePlayer::Update()
{
	// �X�e�[�g�����s
	m_pStateMachine->state_execute();

	return true;
}


// �X�e�[�g�Ƀ��b�Z�[�W�𑗐M
bool LacrossePlayer::Msg(MsgType msg)
{
	return m_pStateMachine->Msg(msg);
}

