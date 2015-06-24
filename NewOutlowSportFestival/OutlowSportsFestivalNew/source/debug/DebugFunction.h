#ifndef __DEBUG_FUNCTION_H__
#define __DEBUG_FUNCTION_H__


//*****************************************************************
//newオーバーロード
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
//メモリーリーク自動チェック
//*****************************************************************

#ifdef _DEBUG

//#define MyMemoryLeakCheck
#define MyMemoryLeakCheck _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)

//*****************************************************************
//printfと同じ形式で出力ウィンドウに表示
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
//	メッセージボックスをprintfみたいに表示する
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
//printfと同じ形式でアサートに文字列を表示させる
//*****************************************************************

// マルチバイト用
#define MyAssertA(expr,str,...)\
{\
if (!(expr)){\
	\
	\
	char t[256], ti[600]; \
	sprintf_s<256>(t, str, __VA_ARGS__); \
	sprintf_s<600>(ti, "　%s　の行番号　%d　でエラーが発生しました \n %s \n式(%s) \n実行を続けますか？", __FILE__, __LINE__, t, #expr); \
	MessageBeep(MB_OK); \
	MessageBoxA(0, ti, "MyAssertError!!!", MB_YESNO); \
}\
}

// Unicode用
#define MyAssertW(expr,str,...)\
{\
if (!(expr)){\
	\
	\
	wchar_t t[256], ti[600]; \
	swprintf_s<256>(t, str, __VA_ARGS__); \
	swprintf_s<600>(ti, L"　%s　の行番号　%d　でエラーが発生しました \n %s \n式(%s) \n実行を続けますか？", __FILEW__, __LINE__, t, L#expr); \
	MessageBeep(MB_OK); \
	MessageBoxW(0, ti, L"MyAssertError!!!", MB_YESNO);\
}\
}


// Unicode と マルチバイトで置き換え
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

#define MyAssert(expr,str,...) expr
#define MyAssertA(expr,str,...) expr
#define MyAssertW(expr,str,...) expr

#endif	


#endif