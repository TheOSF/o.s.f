#include "BulletDebug.h"
#include "DebugDrawManager.h"


//*****************************************************************
//          BulletDebug�N���X
//          DebugDrawManager�N���X ���g�p���ĕ`�悵�܂��B
//*****************************************************************


// �R���X�g���N�^
BulletDebugDrawer::BulletDebugDrawer(IDirect3DDevice9* pDevice) :
m_debugDrawMode(btIDebugDraw::DBG_NoDebug),
m_pDevice(pDevice)
{

}


// �f�X�g���N�^
BulletDebugDrawer::~BulletDebugDrawer()
{
	m_pDevice = nullptr;
}


// btVector3��D3DXVECTOR3
const D3DXVECTOR3 BulletDebugDrawer::btVector3ToVector3(const btVector3& btVec3)
{
	D3DXVECTOR3 vec;
	vec.x = btVec3.x();
	vec.y = btVec3.y();
	vec.z = btVec3.z();
	return vec;
}


// btVector3��D3DXCOLOR
const D3DXCOLOR BulletDebugDrawer::btVector3ToColor(const btVector3& btVec3)
{
	D3DXCOLOR color;
	color.r = btVec3.x();
	color.g = btVec3.y();
	color.b = btVec3.z();
	color.a = 1.0f;
	return color;
}


// ���̕`��
void BulletDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	// ���̕`��
	_DDM::I().DrawLine(
		m_pDevice,
		btVector3ToVector3(from),
		btVector3ToVector3(to),
		btVector3ToColor(color)
		);
}


// �Փ˓_(�����t��)�̕`��
void BulletDebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
	btVector3 to = distance * (PointOnB + normalOnB);
	drawLine(PointOnB, to, color);
}


// �x���A�G���[���̏o��
void BulletDebugDrawer::reportErrorWarning(const char* warningString)
{
	MyDebugString(warningString);
}


// 3D�����̕`��
void BulletDebugDrawer::draw3dText(const btVector3& location, const char* textString)
{

}


// �f�o�b�O���[�h�̐ݒ�
void BulletDebugDrawer::setDebugMode(int debugDrawMode)
{
	m_debugDrawMode = debugDrawMode;
}


// �f�o�b�O���[�h�̎擾
int BulletDebugDrawer::getDebugMode() const
{
	return m_debugDrawMode;
}
