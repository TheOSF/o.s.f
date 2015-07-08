#ifndef __CHARACTER_SLIDING_CLASS_H__
#define __CHARACTER_SLIDING_CLASS_H__

#include "iextreme.h"
#include "SoccerPlayer.h"

//****************************************************************
//		�T�b�J�[�̃X���C�f�B���O�N���X
//****************************************************************


//�X���C�f�B���O�N���X
class SoccerSliding
{
public:
	struct Params
	{
		float speed;
		float damage;
	};

	SoccerSliding(
		const Params&P,
		SoccerPlayer* s );

	~SoccerSliding();

	void Start();
	void Update();
	bool is_End();
private:
	Params m_Params;
	SoccerPlayer* m_SoccerPlayer;
	int timer;
};

#endif