#pragma once


//*****************************************************************
//          BulletDebug.h
//*****************************************************************
#include "BulletSystem.h"


//*****************************************************************
//          BulletDebug�N���X
//          DebugDrawManager�N���X ���g�p���ĕ`�悵�܂��B
//*****************************************************************
class BulletDebugDrawer : public btIDebugDraw
{
private:
	int                           m_debugDrawMode;  // �f�o�b�O���[�h
	IDirect3DDevice9* m_pDevice;                 // �`��Ɏg�p����f�o�C�X

private:
	// btVector3��D3DXVECTOR3
	const D3DXVECTOR3 btVector3ToVector3(const btVector3& btVec3);

	// btVector3��D3DXCOLOR
	const D3DXCOLOR btVector3ToColor(const btVector3& btVec3);

public:
	// �R���X�g���N�^
	BulletDebugDrawer(IDirect3DDevice9* pDevice);

	// �f�X�g���N�^
	virtual~BulletDebugDrawer();

	// ���̕`��
	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color)override;

	// �Փ˓_(�����t��)�̕`��
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)override;

	// �x���A�G���[���̏o��
	void reportErrorWarning(const char* warningString)override;

	// 3D�����̕`��
	void draw3dText(const btVector3& location, const char* textString)override;

	// �f�o�b�O���[�h�̐ݒ�
	void setDebugMode(int debugMode)override;

	// �f�o�b�O���[�h�̎擾
	int getDebugMode() const override;
};


