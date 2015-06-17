#ifndef __COLLISION_H__
#define __COLLISION_H__

/*
	キャラ-＞ステージ
	キャラ-＞キャラ

	ボール-＞ステージ
	ボール-＞キャラ
	
	アイテム-＞キャラ
	アイテム-＞ステージ
*/

#include "iextreme.h"
#include "ForwardDecl.h"


class CollisionManager
{
public:
	static CollisionManager& GetInstance();
	static void Release();

	void Update();
	void Render();

	//床座標以下なら床座標に補正する
	bool FloorCheck(float& posY);

	//レイピック
	bool RayPick(LPVECTOR3 out, LPVECTOR3 pos, LPVECTOR3 vec, float* dist);
private:
	

};

#endif