//#ifndef __AMEFOOT_PLAYER_H__
//#define __AMEFOOT_PLAYER_H__
//
//#include "../CharacterBase.h"
//#include "../CharacterRenderer.h"
//#include "../CharacterStateTemplate.h"	
//
//class AmefootPlayer;
//
////�X�e�[�g�}�V���^���t��
//
//typedef ChrStateMachine<AmefootPlayer, CharacterBase::MsgType> TennisStateMachine;
//typedef ChrState<AmefootPlayer, CharacterBase::MsgType>TennisState;
//
////*************************************************************
////		�A���t�g�v���C���[�N���X
////*************************************************************
//
//class AmefootPlayer :public CharacterBase
//{
//public:
//	enum MotionType{
//		_mt_Stand,
//		_mt_Run,
//
//		_mt_CounterPose,
//		_mt_Counter,
//	};
//	AmefootPlayer(const  CharacterBase::PlayerInfo& info);
//	~AmefootPlayer();
//
//	CharacterRenderer m_Render;
//
//private:
//	AmefootStateMachine* m_pStateMachine;
//};
//
//
//#endif