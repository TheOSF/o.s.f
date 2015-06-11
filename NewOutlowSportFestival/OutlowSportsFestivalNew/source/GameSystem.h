#ifndef __GAME_SYSTEM_H__
#define __GAME_SYSTEM_H__

//****************************************************************
//	�Q�[���̃V�X�e���n�̗񋓒l�w�b�_
//****************************************************************


namespace PlayerNum
{
	//�v���C���[�ԍ��̒l
	enum Value
	{
		_ErrorType = -1			//�G���|�ԍ�
	};
};

//�v���C���[�^�C�v��
namespace PlayerType
{
	enum Value
	{
		_Player,	//�ʏ�v���C���[
		_Computer,	//�R���s���[�^����̃v���C���[
	};
};


//�v���C���[�̋�����
namespace StrongType
{
	enum Value
	{
		_Weak,		//�ア
		_Usual,		//����
		_Strong,	//����

		__ErrorType //�v���C���[����̏ꍇ�̒l
	};
};

//�L�����N�^�̃X�|�[�c�^�C�v
namespace CharacterType
{
	enum Value
	{
		_Tennis,			//�e�j�X
		_Baseball,			//�싅
		_Soccer,			//�T�b�J�[
		_Volleyball,		//�o���[
		_Americanfootball,	//�A���t�g
		_Lacrosse,			//���N���X

		__ErrorType,		//�G���[(���ݒ�)
	};
}

#endif