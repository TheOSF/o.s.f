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
//          EffekseerEffectManagerクラス
//          複数のエフェクトを管理するクラス
//*****************************************************************
class EffekseerEffectManager
{
public:
	typedef int                                          EffectID;    // エフェクトID
	typedef Effekseer::Manager               Manager;   // エフェクト管理クラス
	typedef Effekseer::Effect                    Effect;       // エフェクトクラス
	typedef std::map<EffectID, Effect*> EffectMap; // エフェクトリスト

private:
	// 生成はEffekseerSystemが担当
	friend EffekseerSystem;

	// コンストラクタ
	EffekseerEffectManager(Manager* pManager);

public:
	// デストラクタ
	~EffekseerEffectManager();

	// エフェクト読み込み
	void LoadEffect(EffectID id, const EFK_CHAR* file);

	// エフェクト再生
	EffekseerEffect* PlayEffect(EffectID id);

	// すべてのインスタンスを更新
	// 何倍速で更新するか(60fps基準)
	void UpdateAllInstances(float deltaFrame);

	// すべてのインスタンスを描画
	void RenderAllInstances();

private:
	Manager* m_pManager;  // エフェクト管理クラス
	EffectMap m_Effects;       // エフェクトリスト
};


