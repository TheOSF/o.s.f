#pragma once


//*****************************************************************
//          EffekseerEffectr.h
//*****************************************************************

#include <Effekseer.h>
#include <EffekseerRendererDX9.h>

//*****************************************************************
//          EffekseerEffectクラス
//          エフェクト単体のクラス
//*****************************************************************
class EffekseerEffect
{
public:
	typedef Effekseer::Handle      Handle;
	typedef Effekseer::Vector3D  Vector3D;
	typedef Effekseer::Manager   Manager;

	struct Params
	{
		Vector3D Position; // 座標
		Vector3D Angle;    // 角度
		Vector3D Scale;     // スケール
	};
	Params          m_Params;

	// コンストラクタ
	EffekseerEffect(Manager* pManager, const Handle handle);

	// デストラクタ
	~EffekseerEffect();

	// 自分が有効かどうか
	bool IsDead()const;

	// 更新
	void Update();

private:
	Manager*       m_pManager; // 自分を管理しているクラス
	const Handle  m_Handle;      // 描画・更新用ハンドル
};