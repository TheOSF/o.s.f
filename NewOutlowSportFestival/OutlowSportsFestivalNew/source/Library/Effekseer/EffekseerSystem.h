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
//          EffekseerSystemクラス
//*****************************************************************
class EffekseerSystem
{
private:
	// Effekseer初期化
	bool InitializeEffekseer(LPDIRECT3DDEVICE9 pDevice, int32_t spriteMax);

	// Effekseer解放
	bool ReleaseEffekseer();

public:
	// コンストラクタ
	EffekseerSystem(LPDIRECT3DDEVICE9 pDevice, int32_t spriteMax = 4000);

	// デストラクタ
	~EffekseerSystem();


	// パラメータ更新
	void UpdateParams();

	// 描画開始
	void BeginRendering();

	// 描画終了
	void EndRendering();

	// マネージャ作成
	EffekseerEffectManager* CreateManager(int32_t instanceMax = 4000);

public:
	// 描画用インスタンス
	typedef EffekseerRenderer::Renderer Renderer;

	Effekseer::Matrix44  m_ViewMatrix;          // ビュー変換行列
	Effekseer::Matrix44  m_ProjectionMatrix;  // 射影変換行列

private:
	Renderer*  m_pRenderer;    // 描画用インスタンス

};
