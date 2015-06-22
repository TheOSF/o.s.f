#ifndef __BALL_H__
#define __BALL_H__

#include <map>
#include <list>
#include "iextreme.h"
#include "../GameSystem/ForwardDecl.h"

//*****************************************************
//		�ʃx�[�X�N���X
//*****************************************************

class BallBase
{
public:
	//�ʏ�{�[���ł��̃��[���h���W��ł�y�̒l
	static const float UsualBallShotY;

	//���̋@�\�̃^�C�v
	enum Type
	{
		_DontWork,				//�`��͂��Ă��邪�A�����蔻��̂Ȃ��{�[��
		_Usual,					//�ʏ�̃{�[��
		_CantCounter,			//�J�E���^�[�ł��Ȃ��ʏ�̃{�[��
		_CanVolleySmash,		//�o���[�L�����N�^�ŃX�}�b�V�����邱�Ƃ��ł����Ԃ̃{�[��
		_TennisSpecialAtk,		//�e�j�X
	};

	//�p�����[�^�\����
	struct Params
	{
		CharacterBase*	pParent;	//���˂����L�����N�^�ւ̃|�C���^
		Type			type;		//�ʂ̃^�C�v
		Vector3			pos;		//�ꏊ
		Vector3			move;		//�ړ���
	};

	Params m_Params;

	//�R���X�g���N�^�E�f�X�g���N�^�Ŏ����I�Ƀ}�l�[�W���ɓo�^�E�폜���s��
	BallBase();
	virtual ~BallBase();

	//�����̃{�[�����J�E���^�[�\���ǂ���
	static bool isCanCounter(const BallBase* pBall);
};


//*****************************************************
//	�{�[���}�l�[�W��(�V���O���g������)
//*****************************************************
class BallManager
{
public:
	typedef std::map<BallBase*, BallBase*> BallMap;

	//�o�^�E�폜��BallBase�̂݉\�ɂ��邽��
	friend class BallBase;

	//�C���X�^���X�̃Q�b�^�E���
	static BallManager& GetInstance();
	static void Release();

	//�{�[���f�[�^�擾
	BallMap* GetBallMap();

	//�����Ƃ��J�E���^�[����̂ɓK�����{�[���𓾂�
	bool GetCounterBall(
		BallBase**	ppOut,			//�߂�l�Ƃ��ĕԋp����{�[��
		CrVector3	character_pos,	//�L�����N�^�̏ꏊ
		Vector3*	pOutAfterFrameBallPos,//�L���b�`�܂ł̈ړ��t���[����̃{�[���̈ʒu
		float		catch_area_size,//�L���b�`�\�Ȕ͈�
		int			move_frame		//�L���b�`�܂ł̈ړ��t���[��
		);
private:
	static BallManager*		m_pInstance;
	BallMap					m_BallMap;

	BallManager();
	~BallManager();

	bool AddBall(BallBase* pBall);
	bool EraceBall(BallBase* pBall);
};

#define DefBallMgr (BallManager::GetInstance())

#endif