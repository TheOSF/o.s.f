#include "EffekseerSystem.h"
#include "EffekseerEffectManager.h"

//*****************************************************************
//          EffekseerSystemクラス
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


// Effekseer初期化
bool EffekseerSystem::InitializeEffekseer(LPDIRECT3DDEVICE9 pDevice, int32_t spriteMax)
{
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = EffekseerRendererDX9::Renderer::Create(pDevice, spriteMax);
	}
	return true;
}


// Effekseer解放
bool EffekseerSystem::ReleaseEffekseer()
{
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Destory();
		m_pRenderer = nullptr;
	}
	return true;
}


// マネージャ作成
EffekseerEffectManager* EffekseerSystem::CreateManager(int32_t instanceMax)
{
	Effekseer::Manager* pManager = Effekseer::Manager::Create(instanceMax);

	// 左手座標系に設定
	pManager->SetCoordinateSystem(Effekseer::eCoordinateSystem::COORDINATE_SYSTEM_LH);

	// 描画用インスタンスから描画機能を設定
	pManager->SetSpriteRenderer(m_pRenderer->CreateSpriteRenderer());
	pManager->SetRibbonRenderer(m_pRenderer->CreateRibbonRenderer());
	pManager->SetRingRenderer(m_pRenderer->CreateRingRenderer());
	pManager->SetModelRenderer(m_pRenderer->CreateModelRenderer());

	// 描画用インスタンスからテクスチャの読込機能を設定
	pManager->SetTextureLoader(m_pRenderer->CreateTextureLoader());
	pManager->SetModelLoader(m_pRenderer->CreateModelLoader());

	return new EffekseerEffectManager(pManager);
}


// パラメータ更新
void EffekseerSystem::UpdateParams()
{
	// レンダラーに行列をセット
	m_pRenderer->SetCameraMatrix(m_ViewMatrix);
	m_pRenderer->SetProjectionMatrix(m_ProjectionMatrix);

}


// 描画開始
void EffekseerSystem::BeginRendering()
{
	m_pRenderer->BeginRendering();
}


// 描画終了
void EffekseerSystem::EndRendering()
{
	m_pRenderer->EndRendering();
}
