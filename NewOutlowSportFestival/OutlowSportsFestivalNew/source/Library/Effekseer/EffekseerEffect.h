#pragma once


//*****************************************************************
//          EffekseerEffectr.h
//*****************************************************************

#include <Effekseer.h>
#include <EffekseerRendererDX9.h>

//*****************************************************************
//          EffekseerEffect�N���X
//          �G�t�F�N�g�P�̂̃N���X
//*****************************************************************
class EffekseerEffect
{
public:
	typedef Effekseer::Handle      Handle;
	typedef Effekseer::Vector3D  Vector3D;
	typedef Effekseer::Manager   Manager;

	struct Params
	{
		Vector3D Position; // ���W
		Vector3D Angle;    // �p�x
		Vector3D Scale;     // �X�P�[��
	};
	Params          m_Params;

	// �R���X�g���N�^
	EffekseerEffect(Manager* pManager, const Handle handle);

	// �f�X�g���N�^
	~EffekseerEffect();

	// �������L�����ǂ���
	bool IsDead()const;

	// �X�V
	void Update();

private:
	Manager*       m_pManager; // �������Ǘ����Ă���N���X
	const Handle  m_Handle;      // �`��E�X�V�p�n���h��
};