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

//#define MyMemoryLeakCheck
#define MyMemoryLeakCheck _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)

//*****************************************************************
//printf�Ɠ����`���ŏo�̓E�B���h�E�ɕ\��
//*****************************************************************
#define MyDebugStringA(str,...)\
{\
	char temp[512]; \
	sprintf_s<512>(temp, str, __VA_ARGS__); \
	OutputDebugStringA(temp); \
}

#define MyDebugStringW(str,...)\
{\
	wchar_t temp[512]; \
	sprintf_s<512>(temp, str, __VA_ARGS__); \
	OutputDebugStringW(temp); \
}

//*****************************************************************
//	���b�Z�[�W�{�b�N�X��printf�݂����ɕ\������
//*****************************************************************
#define MessageBoxPlusA(str,...)\
{\
	char t[512]; \
	sprintf_s<512>(t, str, __VA_ARGS__); \
	MessageBox(0, t, "MessageBoxPlus", MB_OK); \
}

#define MessageBoxPlusW(str,...)\
{\
	wchar_t t[512]; \
	swprintf_s<512>(t, str, __VA_ARGS__); \
	MessageBox(0, t, L"MessageBoxPlus", MB_OK); \
}

//#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)


//*****************************************************************
//printf�Ɠ����`���ŃA�T�[�g�ɕ������\��������
//*****************************************************************

// �}���`�o�C�g�p
#define MyAssertA(expr,str,...)\
{\
if (!(expr)){\
	\
	\
	char t[256], ti[600]; \
	sprintf_s<256>(t, str, __VA_ARGS__); \
	sprintf_s<600>(ti, "�@%s�@�̍s�ԍ��@%d�@�ŃG���[���������܂��� \n %s \n��(%s) \n���s�𑱂��܂����H", __FILE__, __LINE__, t, #expr); \
	MessageBeep(MB_OK); \
	MessageBoxA(0, ti, "MyAssertError!!!", MB_YESNO); \
}\
}

// Unicode�p
#define MyAssertW(expr,str,...)\
{\
if (!(expr)){\
	\
	\
	wchar_t t[256], ti[600]; \
	swprintf_s<256>(t, str, __VA_ARGS__); \
	swprintf_s<600>(ti, L"�@%s�@�̍s�ԍ��@%d�@�ŃG���[���������܂��� \n %s \n��(%s) \n���s�𑱂��܂����H", __FILEW__, __LINE__, t, L#expr); \
	MessageBeep(MB_OK); \
	MessageBoxW(0, ti, L"MyAssertError!!!", MB_YESNO);\
}\
}


// Unicode �� �}���`�o�C�g�Œu������
#if defined (UNICODE)||(_UNICODE)

#define MyDebugString(str,...) MyDebugStringW(str,__VA_ARGS__)
#define MessageBoxPlus(str,...) MessageBoxPlusW(str,__VA_ARGS__)
#define MyAssert(expr,str,...) MyAssertW(expr,str,__VA_ARGS__)

#else

#define MyDebugString(str,...) MyDebugStringA(str,__VA_ARGS__)
#define MessageBoxPlus(str,...) MessageBoxPlusA(str,__VA_ARGS__)
#define MyAssert(expr,str,...) MyAssertA(expr,str,__VA_ARGS__)

#endif

#else

#define MyMemoryLeakCheck

#define MyDebugString(str,...)
#define MyDebugStringA(str,...)
#define MyDebugStringW(str,...)

#define MessageBoxPlus(str,...)
#define MessageBoxPlusA(str,...)
#define MessageBoxPlusW(str,...)


#endif	


#endif