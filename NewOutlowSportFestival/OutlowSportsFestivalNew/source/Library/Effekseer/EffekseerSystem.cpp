#include "EffekseerSystem.h"
#include "EffekseerEffectManager.h"

//*****************************************************************
//          EffekseerSystem�N���X
//*****************************************************************

EffekseerSystem::EffekseerSystem(
	LPDIRECT3DDEVICE9 pDevice, 
	int32_t spriteMax):
	m_pRenderer(nullptr)
{
	this->InitializeEffekseer(pDevice, spriteMax);
}


EffekseerSystem::~EffekseerSystem()
{
	this->ReleaseEffekseer();
}


// Effekseer������
bool EffekseerSystem::InitializeEffekseer(LPDIRECT3DDEVICE9 pDevice, int32_t spriteMax)
{
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = EffekseerRendererDX9::Renderer::Create(pDevice, spriteMax);
	}
	return true;
}


// Effekseer���
bool EffekseerSystem::ReleaseEffekseer()
{
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Destory();
		m_pRenderer = nullptr;
	}
	return true;
}


// �}�l�[�W���쐬
EffekseerEffectManager* EffekseerSystem::CreateManager(int32_t instanceMax)
{
	Effekseer::Manager* pManager = Effekseer::Manager::Create(instanceMax);

	// ������W�n�ɐݒ�
	pManager->SetCoordinateSystem(Effekseer::eCoordinateSystem::COORDINATE_SYSTEM_LH);

	// �`��p�C���X�^���X����`��@�\��ݒ�
	pManager->SetSpriteRenderer(m_pRenderer->CreateSpriteRenderer());
	pManager->SetRibbonRenderer(m_pRenderer->CreateRibbonRenderer());
	pManager->SetRingRenderer(m_pRenderer->CreateRingRenderer());
	pManager->SetModelRenderer(m_pRenderer->CreateModelRenderer());

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	pManager->SetTextureLoader(m_pRenderer->CreateTextureLoader());
	pManager->SetModelLoader(m_pRenderer->CreateModelLoader());

	return new EffekseerEffectManager(pManager);
}


// �p�����[�^�X�V
void EffekseerSystem::UpdateParams()
{
	// �����_���[�ɍs����Z�b�g
	m_pRenderer->SetCameraMatrix(m_ViewMatrix);
	m_pRenderer->SetProjectionMatrix(m_ProjectionMatrix);

}


// �`��J�n
void EffekseerSystem::BeginRendering()
{
	m_pRenderer->BeginRendering();
}


// �`��I��
void EffekseerSystem::EndRendering()
{
	m_pRenderer->EndRendering();
}
