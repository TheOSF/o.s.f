#pragma once


//*****************************************************************
//          BulletDebug.h
//*****************************************************************
#include "BulletSystem.h"


//*****************************************************************
//          BulletDebugクラス
//          DebugDrawManagerクラス を使用して描画します。
//*****************************************************************
class BulletDebugDrawer : public btIDebugDraw
{
private:
	int                           m_debugDrawMode;  // デバッグモード
	IDirect3DDevice9* m_pDevice;                 // 描画に使用するデバイス

private:
	// btVector3→D3DXVECTOR3
	const D3DXVECTOR3 btVector3ToVector3(const btVector3& btVec3);

	// btVector3→D3DXCOLOR
	const D3DXCOLOR btVector3ToColor(const btVector3& btVec3);

public:
	// コンストラクタ
	BulletDebugDrawer(IDirect3DDevice9* pDevice);

	// デストラクタ
	virtual~BulletDebugDrawer();

	// 線の描画
	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color)override;

	// 衝突点(方向付き)の描画
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)override;

	// 警告、エラー文の出力
	void reportErrorWarning(const char* warningString)override;

	// 3D文字の描画
	void draw3dText(const btVector3& location, const char* textString)override;

	// デバッグモードの設定
	void setDebugMode(int debugMode)override;

	// デバッグモードの取得
	int getDebugMode() const override;
};


