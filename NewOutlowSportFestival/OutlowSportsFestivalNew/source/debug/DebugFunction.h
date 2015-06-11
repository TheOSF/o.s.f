#ifndef __DEBUG_FUNCTION_H__
#define __DEBUG_FUNCTION_H__


//*****************************************************************
//new�I�[�o�[���[�h
//*****************************************************************

#define _CRTDBG_MAP_ALLOC

#include <cstdlib>
#include <cassert>
#include <crtdbg.h>
#include <new>
#include <memory>
#include <Windows.h>
#include <string>

//*****************************************************************
//�������[���[�N�����`�F�b�N
//*****************************************************************

#ifdef _DEBUG

#define MyMemoryLeakCheck
//#define MyMemoryLeakCheck _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)

//*****************************************************************
//printf�Ɠ����`���ŏo�̓E�B���h�E�ɕ\��
//*****************************************************************
#define MyDebugString(str,...)\
{\
	TCHAR temp[512]; \
	sprintf_s<512>(temp, str, __VA_ARGS__); \
	OutputDebugString(temp); \
}

//*****************************************************************
//	���b�Z�[�W�{�b�N�X��printf�݂����ɕ\������
//*****************************************************************
#define MessageBoxPlus(str,...)\
{\
	char t[512]; \
	sprintf_s<512>(t, str, __VA_ARGS__); \
	MessageBox(0, t, "MessageBoxPlus", MB_OK); \
}

//#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)


//*****************************************************************
//printf�Ɠ����`���ŃA�T�[�g�ɕ������\��������
//*****************************************************************

#define MyAssert(expr,str,...)\
{\
if (!(expr)){\
	\
	\
	char t[256], ti[600]; \
	sprintf_s<256>(t, str, __VA_ARGS__); \
	sprintf_s<600>(ti, "�@%s�@�̍s�ԍ��@%d�@�ŃG���[���������܂��� \n %s \n��(%s) \n���s�𑱂��܂����H", __FILE__, __LINE__, t, #expr); \
	MessageBeep(MB_OK); \
	MessageBox(0, ti, "MyAssertError!!!", MB_YESNO);\
}\
}

#else

#define MyDebugString(str,...)

#define MessageBoxPlus(str,...)

#define MyMemoryLeakCheck

#define MyAssert(expr,str,...) expr

#endif	


#endif