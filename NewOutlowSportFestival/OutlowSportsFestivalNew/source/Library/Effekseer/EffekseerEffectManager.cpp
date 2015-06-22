#include "EffekseerEffectManager.h"
#include "EffekseerEffect.h"

//*****************************************************************
//          EffekseerEffectManagerクラス
//          複数のエフェクトを管理するクラス
//*****************************************************************

// コンストラクタ
EffekseerEffectManager::EffekseerEffectManager(Manager* pManager) :
m_pManager(pManager)
{
	
}


// デストラクタ
EffekseerEffectManager::~EffekseerEffectManager()
{
	// エフェクトの解放
	for (auto& it : m_Effects)
	{
		it.second->Release();
	}
	m_Effects.clear();

	// マネージャーの解放
	if (m_pManager != nullptr)
	{
		m_pManager->Destroy();
		m_pManager = nullptr;
	}
}


// エフェクト読み込み
void EffekseerEffectManager::LoadEffect(EffectID id, const EFK_CHAR* file)
{
	// チェック
	MyAssert(
		m_Effects.find(id) == m_Effects.end(), 
		"ID[%d]には既に登録されています。\n",
		id
		);
	
	// 読み込み
	Effect* pEffect = Effect::Create(m_pManager, file);

	MyAssertW(
		pEffect != nullptr,
		L"ファイル : %s の読み込みに失敗しました。\n", (const wchar_t*)file
		);

	// 登録
	m_Effects.insert(
		std::pair<EffectID, Effect*>(id, pEffect)
		);
}


// エフェクト再生
EffekseerEffect* EffekseerEffectManager::PlayEffect(EffectID id)
{
	auto& it = m_Effects.find(id);

	// チェック
	MyAssert(
		it != m_Effects.end(),
		"ID[%d]にエフェクトが登録されていません。\n",
		id
		);

	// インスタンスハンドル取得
	EffekseerEffect::Handle handle = m_pManager->Play(it->second, 0, 0, 0);

	return new EffekseerEffect(
		m_pManager,
		handle
		);
}


// すべてのインスタンスを更新
// 何倍速で更新するか(60fps基準)
void EffekseerEffectManager::UpdateAllInstances(float deltaFrame)
{
	m_pManager->Update(deltaFrame);
}


// すべてのインスタンスを描画
void EffekseerEffectManager::RenderAllInstances()
{
	m_pManager->Draw();
}

