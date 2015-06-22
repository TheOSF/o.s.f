#include "BulletDebug.h"
#include "DebugDrawManager.h"


//*****************************************************************
//          BulletDebugクラス
//          DebugDrawManagerクラス を使用して描画します。
//*****************************************************************


// コンストラクタ
BulletDebugDrawer::BulletDebugDrawer(IDirect3DDevice9* pDevice) :
m_debugDrawMode(btIDebugDraw::DBG_NoDebug),
m_pDevice(pDevice)
{

}


// デストラクタ
BulletDebugDrawer::~BulletDebugDrawer()
{
	m_pDevice = nullptr;
}


// btVector3→D3DXVECTOR3
const D3DXVECTOR3 BulletDebugDrawer::btVector3ToVector3(const btVector3& btVec3)
{
	D3DXVECTOR3 vec;
	vec.x = btVec3.x();
	vec.y = btVec3.y();
	vec.z = btVec3.z();
	return vec;
}


// btVector3→D3DXCOLOR
const D3DXCOLOR BulletDebugDrawer::btVector3ToColor(const btVector3& btVec3)
{
	D3DXCOLOR color;
	color.r = btVec3.x();
	color.g = btVec3.y();
	color.b = btVec3.z();
	color.a = 1.0f;
	return color;
}


// 線の描画
void BulletDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	// 線の描画
	_DDM::I().DrawLine(
		m_pDevice,
		btVector3ToVector3(from),
		btVector3ToVector3(to),
		btVector3ToColor(color)
		);
}


// 衝突点(方向付き)の描画
void BulletDebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
	btVector3 to = distance * (PointOnB + normalOnB);
	drawLine(PointOnB, to, color);
}


// 警告、エラー文の出力
void BulletDebugDrawer::reportErrorWarning(const char* warningString)
{
	MyDebugString(warningString);
}


// 3D文字の描画
void BulletDebugDrawer::draw3dText(const btVector3& location, const char* textString)
{

}


// デバッグモードの設定
void BulletDebugDrawer::setDebugMode(int debugDrawMode)
{
	m_debugDrawMode = debugDrawMode;
}


// デバッグモードの取得
int BulletDebugDrawer::getDebugMode() const
{
	return m_debugDrawMode;
}
