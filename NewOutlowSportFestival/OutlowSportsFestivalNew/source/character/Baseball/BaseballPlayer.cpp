#include "BaseballPlayer.h"
#include "../../Damage/Damage.h"
#include "../../GameSystem/GameController.h"
#include "../../Ball/UsualBall.h"

#include "../CharacterFunction.h"
#include "../CharacterManager.h"

//*************************************************************
//		�싅�v���C���[�N���X
//*************************************************************

//�@�R���X�g���N�^
BaseballPlayer::BaseballPlayer(const CharacterBase::PlayerInfo& info) :
CharacterBase(info), batterflg(true), target(0,0,0),
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

//�@�������֐���
BallBase::Params BaseballPlayer::BaseballShot(BaseballPlayer* b, BallBase::Params p){
	//�ړ��͑O����
	chr_func::GetFront(b, &p.move);
	//�X�s�[�h�͓K��
	p.move *= 0.45f;
	//�L�����̏ꏊ��(�ŏI�I�ɘr�̈ʒu�ɁH)
	p.pos = b->m_Params.pos;
	//�������L�������ʃ{�[�����˂�Y��
	p.pos.y = BallBase::UsualBallShotY;
	//�e��������
	p.pParent = b;
	//�ʏ�^�C�v
	p.type = BallBase::Type::_Usual;

	return p;
}

//�@�������^�[�Q�b�g�I��
BallBase::Params BaseballPlayer::TargetDecision( BallBase::Params p, Vector3 t){

	//�@map���
	const CharacterManager::CharacterMap& chr_map = DefCharacterMgr.GetCharacterMap();

	//�@�����֌W
	Vector3 v(0, 0, 0);
	float len = 2000.0f;
	float templen = 0.0f;

	//�@pos�ꎞ�ۑ��p
	Vector3 temppos(0, 0, 0);

	//�L�����N�^���W���Z�o
	for (auto it = chr_map.begin(); it != chr_map.end(); ++it){
		//�@����ł���continue
		if (chr_func::isDie(it->first) || it->first->m_PlayerInfo.number == m_PlayerInfo.number){
			continue;
		}
		//�@�������f
		t = m_Params.pos - it->first->m_Params.pos;
		templen = t.LengthSq();
		//�@��ԋ߂������E�ʒu�Z�o
		if (len > templen){
			len = templen;
			temppos = it->first->m_Params.pos;
		}
	}

	//�@�z�[�~���O�v�Z
	t = temppos - param.pos;
	t.Normalize();
	v.x += t.x*0.4f;
	v.z += t.z*0.4f;
	p.pos.x += v.x;
	p.pos.z += v.z;
	p.move = v;
	//�@param�Etarget��ۑ�
	param = p;
	target = t;

	return p;
}