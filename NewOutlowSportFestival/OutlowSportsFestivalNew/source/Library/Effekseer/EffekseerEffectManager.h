#pragma once


//*****************************************************************
//          EffekseerEffectManager.h
//*****************************************************************

#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <map>

class EffekseerEffect;
class EffekseerSystem;
//*****************************************************************
//          EffekseerEffectManager�N���X
//          �����̃G�t�F�N�g���Ǘ�����N���X
//*****************************************************************
class EffekseerEffectManager
{
public:
	typedef int                                          EffectID;    // �G�t�F�N�gID
	typedef Effekseer::Manager               Manager;   // �G�t�F�N�g�Ǘ��N���X
	typedef Effekseer::Effect                    Effect;       // �G�t�F�N�g�N���X
	typedef std::map<EffectID, Effect*> EffectMap; // �G�t�F�N�g���X�g

private:
	// ������EffekseerSystem���S��
	friend EffekseerSystem;

	// �R���X�g���N�^
	EffekseerEffectManager(Manager* pManager);

public:
	// �f�X�g���N�^
	~EffekseerEffectManager();

	// �G�t�F�N�g�ǂݍ���
	void LoadEffect(EffectID id, const EFK_CHAR* file);

	// �G�t�F�N�g�Đ�
	EffekseerEffect* PlayEffect(EffectID id);

	// ���ׂẴC���X�^���X���X�V
	// ���{���ōX�V���邩(60fps�)
	void UpdateAllInstances(float deltaFrame);

	// ���ׂẴC���X�^���X��`��
	void RenderAllInstances();

private:
	Manager* m_pManager;  // �G�t�F�N�g�Ǘ��N���X
	EffectMap m_Effects;       // �G�t�F�N�g���X�g
};


