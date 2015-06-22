#pragma once

#include "NonCopyable.h"


/**
* �V���O���g�����N���X
* �p�����邱�Ƃ�Singleton�����܂��B

* ��
* class Hoge : public cSingleton<Hoge>
* {
* private:
*    Hoge();
*    ~Hoge();
* };

* �� �g���O�� StartUp() �A�g���I�������� ShutDown() �֐����Ă�ł��������I

*/
template<class _Ty>
class cSingleton
	:private cNonCopyable
{
public:
	typedef typename _Ty InstanceType;

private:
	static InstanceType*  instance_;         // �C���X�^���X
	bool                           is_initialized_;  // �������ς݃t���O

protected:
	inline cSingleton() :is_initialized_(false){}  // �R���X�g���N�^
	inline virtual~cSingleton(){}                       // �f�X�g���N�^

public:

	/**
	* �C���X�^���X���擾���܂��B
	*/
	inline static InstanceType& GetInstance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new InstanceType();
		}

		return *instance_;
	}


	/**
	* �C���X�^���X������܂��B
	*/
	inline static void ReleaseInstance()
	{

		if (instance_ != nullptr)
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

	/**
	* ���p�J�n���܂��B
	*/
	bool StartUp()
	{
		// ���ɏ������ς�
		if (is_initialized_ == true)
		{
			return false;
		}

		if (Initialize() == false)
		{
			return false;
		}

		is_initialized_ = true;
		return true;
	}


	/**
	* ���p�I�����܂��B
	*/
	bool ShutDown(bool release_instance = false)
	{
		// ���ɉ���ς�
		if (is_initialized_ == false)
		{
			return false;
		}

		// �������
		if (Release() == false)
		{
			return false;
		}

		is_initialized_ = false;

		// �C���X�^���X���
		if (release_instance == true)
		{
			ReleaseInstance();
		}

		return true;
	}


protected:
	/**
	* ���������܂��B
	*/
	virtual bool Initialize() = 0;
	
	/**
	* ������܂��B
	*/
	virtual bool Release() = 0;

};

// �C���X�^���X
template<class _Ty> 
typename cSingleton<_Ty>::InstanceType* cSingleton<_Ty>::instance_ = nullptr;





// EOF