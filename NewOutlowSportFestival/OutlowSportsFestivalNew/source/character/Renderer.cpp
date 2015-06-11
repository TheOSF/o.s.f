#include "Renderer.h"
#include "../debug/DebugFunction.h"

RendererManager* RendererManager::m_pInstance = nullptr;

//*************************************************
//	描画クラスベース
//*************************************************

DeferredRenderer::DeferredRenderer()
{
	MyAssert(
		DefRendererMgr.AddDeferredRenderer(this),
		"DeferredRendererの追加に失敗しました");
}



DeferredRenderer::~DeferredRenderer()
{
	MyAssert(
		DefRendererMgr.EraceDeferredRenderer(this),
		"DeferredRendererの削除に失敗しました");
}



ForwardRenderer::ForwardRenderer() :
m_SortZ(1000)
{
	MyAssert(
		DefRendererMgr.AddForwardRenderer(this),
		"ForwardRendererの追加に失敗しました");
}

ForwardRenderer::~ForwardRenderer()
{
	MyAssert(
		DefRendererMgr.EraceForwardRenderer(this),
		"ForwardRendererの削除に失敗しました");
}



//*************************************************
//	描画マネージャ
//*************************************************

RendererManager& RendererManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new RendererManager();
	}
	return *m_pInstance;
}

void RendererManager::Release()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

bool RendererManager::AddDeferredRenderer(LpDeferredRenderer pDef)
{
	if (m_DeferredRendererMap.find(pDef) != m_DeferredRendererMap.end())
	{
		return false;
	}

	m_DeferredRendererMap.insert(
		DeferredRendererMap::value_type(pDef, pDef)
		);

	return true;
}

bool RendererManager::EraceDeferredRenderer(LpDeferredRenderer pDef)
{
	auto it = m_DeferredRendererMap.find(pDef);

	if (it == m_DeferredRendererMap.end())
	{
		return false;
	}

	m_DeferredRendererMap.erase(it);
	return true;
}


bool RendererManager::AddForwardRenderer(LpForwardRenderer pDef)
{
	if (m_ForwardRendererMap.find(pDef) != m_ForwardRendererMap.end())
	{
		return false;
	}

	m_ForwardRendererMap.insert(
		ForwardRendererMap::value_type(pDef, pDef)
		);

	return true;
}

bool RendererManager::EraceForwardRenderer(LpForwardRenderer pDef)
{
	auto it = m_ForwardRendererMap.find(pDef);

	if (it == m_ForwardRendererMap.end())
	{
		return false;
	}

	m_ForwardRendererMap.erase(it);
	return true;
}


//ディファード描画
void RendererManager::DeferredRender()
{
	for (auto it = m_DeferredRendererMap.begin();
		it != m_DeferredRendererMap.end();
		++it)
	{
		it->second->Render();
	}
}

//Z値比較用関数
static int CompareFunc(const void*p1, const void* p2)
{
	return ((**(LpForwardRenderer*)p1).m_SortZ > (**(LpForwardRenderer*)p2).m_SortZ) ? (-1) : (1);
}

//フォワード描画
void RendererManager::ForwardRender()
{
	if (m_ForwardRendererMap.empty())
	{
		return;
	}

	//ソート結果用配列を生成
	LpForwardRenderer* SortData = new LpForwardRenderer[m_ForwardRendererMap.size()];

	try
	{
		int count = 0;

		for (auto it = m_ForwardRendererMap.begin();
			it != m_ForwardRendererMap.end();
			++it)
		{
			SortData[count++] = it->second;

			//Z値を計算する
			it->second->CalcZ();
		}

		//遠い順番にソート
		std::qsort(
			&SortData[0],
			count,
			sizeof(LpForwardRenderer),
			CompareFunc
			);

		//描画
		for (int i = 0; i < count; ++i)
		{
			SortData[i]->Render();
		}

	}
	catch (...)
	{
		delete[]SortData;
		throw;
	}

	delete[]SortData;
}


RendererManager::RendererManager()
{

}

RendererManager::~RendererManager()
{

}