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

#define MyMemoryLeakCheck
//#define MyMemoryLeakCheck _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)

//*****************************************************************
//printfと同じ形式で出力ウィンドウに表示
//*****************************************************************
#define MyDebugString(str,...)\
{\
	TCHAR temp[512]; \
	sprintf_s<512>(temp, str, __VA_ARGS__); \
	OutputDebugString(temp); \
}

//*****************************************************************
//	メッセージボックスをprintfみたいに表示する
//*****************************************************************
#define MessageBoxPlus(str,...)\
{\
	char t[512]; \
	sprintf_s<512>(t, str, __VA_ARGS__); \
	MessageBox(0, t, "MessageBoxPlus", MB_OK); \
}

//#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)


//*****************************************************************
//printfと同じ形式でアサートに文字列を表示させる
//*****************************************************************

#define MyAssert(expr,str,...)\
{\
if (!(expr)){\
	\
	\
	char t[256], ti[600]; \
	sprintf_s<256>(t, str, __VA_ARGS__); \
	sprintf_s<600>(ti, "　%s　の行番号　%d　でエラーが発生しました \n %s \n式(%s) \n実行を続けますか？", __FILE__, __LINE__, t, #expr); \
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