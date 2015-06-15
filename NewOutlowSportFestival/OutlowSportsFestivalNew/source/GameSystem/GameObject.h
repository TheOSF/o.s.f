#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <map>
#include "debug\DebugFunction.h"


//********************************************************************
//	継承すると自動で更新するゲーム内オブジェクトのベースクラス
//********************************************************************

class GameObjectBase
{
public:
	enum MsgType
	{
		_PlayStart,	//プレイ開始時(ラウンドごとの)に送られるメッセージ
		_RoundEnd,	//ラウンド終了時に送られるメッセージ
	};

	GameObjectBase();
	virtual ~GameObjectBase();

	virtual bool Update() = 0;	//falseを返すと消去する
	virtual bool Msg(MsgType mt) = 0;
};

typedef GameObjectBase* LpGameObjectBase;


//********************************************************************
//	オブジェクトクラスの描画・更新をするマネージャクラス
//********************************************************************

class GameObjectManager
{
public:

	static GameObjectManager& GetInstance();
	static void Release();
	
	void Update();	//全オブジェクト更新

	void SendMsg(GameObjectBase::MsgType mt);	//全オブジェクトにメッセージを送信

private:
	typedef std::map<LpGameObjectBase, LpGameObjectBase> GameObjectMap;

	friend class GameObjectBase;
	friend GameObjectBase::GameObjectBase();
	friend GameObjectBase::~GameObjectBase();
private:
	static GameObjectManager*	m_pInstance;
	GameObjectMap				m_GameObjectMap;
private:
	GameObjectManager();
	~GameObjectManager();

	bool Add(LpGameObjectBase pObj);
	bool Erace(LpGameObjectBase pObj);
};

#define DefGameObjMgr (GameObjectManager::GetInstance())


#endif