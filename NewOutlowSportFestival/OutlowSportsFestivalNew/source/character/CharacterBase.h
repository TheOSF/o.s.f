#ifndef __CHARACTER_BASE_H__
#define __CHARACTER_BASE_H__

#include "../GameObject.h"
#include "../GameSystem.h"

#include "iextreme.h"

//***************************************************
//		キャラクタクラス
//***************************************************


class CharacterBase :public GameObjectBase
{
private:
	CharacterBase(const CharacterBase&);
public:

	struct PlayerInfo
	{
		PlayerNum::Value		number;			//プレイヤー番号
		PlayerType::Value		player_type;	//プレイヤータイプ
		StrongType::Value		strong_type;	//強さタイプ
		CharacterType::Value	chr_type;		//キャラクタタイプ
	};

	struct Params
	{
		Vector3				pos;		//座標
		Vector3				move;		//移動量
		float				hitScale;	//あたり判定の円の大きさ
		float				angle;		//アングル(ラジアン)
		float				HP;			//０～
		float				SP;			//０～１００
	};
	const PlayerInfo	m_PlayerInfo;
	Params				m_Params;
	inline const Params& Getparam()
		const{
		return m_Params;
	}

	CharacterBase(const PlayerInfo& info);
	virtual ~CharacterBase(){}

	virtual bool Update() = 0;	//この関数がfalseを返すとdeleteされる
	virtual bool Msg(MsgType mt) = 0;	//受信できたメッセージはtrueを
};

#endif