#include	"iextreme.h"
#include	"../IexSystem/System.h"
#include	"debug\DebugFunction.h"
#include	"sceneGamePlay.h"
#include	"character\Tennis\TennisPlayer.h"
#include	"character\Tennis\TennisPlayerState.h"
#include	"../Camera/Camera.h"

#include "../character/Lacrosse/LacrossePlayer.h"
#include "../character/Lacrosse/LacrossePlayerState.h"

//*****************************************************************************************************************************
//
//	グローバル変数
//
//*****************************************************************************************************************************

static LPIEXMESH pStage;

//*****************************************************************************************************************************
//
//	初期化
//
//*****************************************************************************************************************************


bool sceneGamePlay::Initialize()
{
	//	環境設定
	iexLight::SetAmbient(0x404040);
	iexLight::SetFog(800, 1000, 0);

	Vector3 dir(1.0f, -1.0f, -0.5f);
	dir.Normalize();
	iexLight::DirLight(shader, 0, &dir, 0.8f, 0.8f, 0.8f);

	pStage = new iexMesh("DATA\\STAGE\\Stage.IMO");

	DefCamera.m_Position = Vector3(0, 40, -55);
	DefCamera.m_Target = Vector3(0, 4, 0);

	//キャラクタ作成
	CharacterBase::PlayerInfo pl;

	pl.chr_type = CharacterType::_Tennis;
	pl.number = (PlayerNum::Value)0;
	pl.player_type = PlayerType::_Player;
	pl.strong_type = StrongType::__ErrorType;
	
	//テニスを作成し、動きとしてプレイヤー操作クラスをセット
	//(new TennisPlayer(pl))->SetState(new TennisState_PlayerControll_Move());

	// ラクロス作成
	(new LacrossePlayer(pl))->SetState(new LacrosseState_PlayerControllMove());

	return true;
}

//*****************************************************************************************************************************
//
//		解放
//
//*****************************************************************************************************************************

sceneGamePlay::~sceneGamePlay()
{
	delete pStage;

	DefCamera.Release();
	DefRendererMgr.Release();
	DefGameObjMgr.Release();
}

//*****************************************************************************************************************************
//
//		更新
//
//*****************************************************************************************************************************
void	sceneGamePlay::Update()
{
	DefCamera.Update();
	DefGameObjMgr.Update();
}

//*****************************************************************************************************************************
//
//		描画関連
//
//*****************************************************************************************************************************

void	sceneGamePlay::Render()
{
	DefCamera.Clear();

	pStage->Render();

	DefRendererMgr.DeferredRender();
	DefRendererMgr.ForwardRender();
}
