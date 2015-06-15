#ifndef __GAME_SYSTEM_H__
#define __GAME_SYSTEM_H__

//****************************************************************
//	ゲームのシステム系の列挙値ヘッダ
//****************************************************************


namespace PlayerNum
{
	//プレイヤー番号の値
	enum Value
	{
		_ErrorType = -1			//エラ－番号
	};
};

//プレイヤータイプ列挙
namespace PlayerType
{
	enum Value
	{
		_Player,	//通常プレイヤー
		_Computer,	//コンピュータ操作のプレイヤー
	};
};


//プレイヤーの強さ列挙
namespace StrongType
{
	enum Value
	{
		_Weak,		//弱い
		_Usual,		//普通
		_Strong,	//強い

		__ErrorType //プレイヤー操作の場合の値
	};
};

//キャラクタのスポーツタイプ
namespace CharacterType
{
	enum Value
	{
		_Tennis,			//テニス
		_Baseball,			//野球
		_Soccer,			//サッカー
		_Volleyball,		//バレー
		_Americanfootball,	//アメフト
		_Lacrosse,			//ラクロス

		__ErrorType,		//エラー(未設定)
	};
}

#endif