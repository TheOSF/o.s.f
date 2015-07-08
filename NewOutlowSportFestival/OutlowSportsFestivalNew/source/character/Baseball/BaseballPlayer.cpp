#include "BaseballPlayer.h"
#include "../../Damage/Damage.h"
#include "../../GameSystem/GameController.h"


//*************************************************************
//		�싅�v���C���[�N���X
//*************************************************************

//�@�R���X�g���N�^
BaseballPlayer::BaseballPlayer(const CharacterBase::PlayerInfo& info) :
CharacterBase(info), batterflg(true),
m_Renderer(new  BlendAnimationMesh("DATA\\CHR\\BaseBall\\player_B.iem"))
{
	m_pStateMachine = new BaseballStateMachine(this);
}

//�@�f�X�g���N�^
BaseballPlayer::~BaseballPlayer(){
	delete m_pStateMachine;
}

//�@�X�e�[�g�Z�b�g
void BaseballPlayer::SetState(BaseballState* state){
	//�@�V�����X�e�[�g���Z�b�g
	m_pStateMachine->set_state(state);
}

//�@�X�V
bool BaseballPlayer::Update(){
	//�@�؂�ւ�
	Change();
	// �X�e�[�g���s
	m_pStateMachine->state_execute();

	return true;	//���true��Ԃ��Ə�������Ȃ�
}

bool  BaseballPlayer::Msg(MsgType mt){
	return m_pStateMachine->Msg(mt);
}

//�@�؂�ւ�
void BaseballPlayer::Change(){
	if (controller::GetTRG(controller::button::_L1, m_PlayerInfo.number)){
		if (batterflg){
			batterflg = false;
		}
		else{
			batterflg = true;
		}
	}

}