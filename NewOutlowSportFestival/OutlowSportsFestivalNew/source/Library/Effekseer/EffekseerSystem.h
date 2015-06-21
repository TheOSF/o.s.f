#pragma once


//*****************************************************************
//          EffekseerRenderer.h
//*****************************************************************

#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
//#include <XAudio2.h>

#pragma comment(lib,"Effekseer.lib")
#pragma comment(lib,"EffekseerRendererDX9.lib")
//#pragma comment(lib,"EffekseerSoundXAudio2.lib")

class EffekseerEffectManager;

//*****************************************************************
//          EffekseerSystem�N���X
//*****************************************************************
class EffekseerSystem
{
private:
	// Effekseer������
	bool InitializeEffekseer(LPDIRECT3DDEVICE9 pDevice, int32_t spriteMax);

	// Effekseer���
	bool ReleaseEffekseer();

public:
	// �R���X�g���N�^
	EffekseerSystem(LPDIRECT3DDEVICE9 pDevice, int32_t spriteMax = 4000);

	// �f�X�g���N�^
	~EffekseerSystem();


	// �p�����[�^�X�V
	void UpdateParams();

	// �`��J�n
	void BeginRendering();

	// �`��I��
	void EndRendering();

	// �}�l�[�W���쐬
	EffekseerEffectManager* CreateManager(int32_t instanceMax = 4000);

public:
	// �`��p�C���X�^���X
	typedef EffekseerRenderer::Renderer Renderer;

	Effekseer::Matrix44  m_ViewMatrix;          // �r���[�ϊ��s��
	Effekseer::Matrix44  m_ProjectionMatrix;  // �ˉe�ϊ��s��

private:
	Renderer*  m_pRenderer;    // �`��p�C���X�^���X

};
