#include	"iextreme.h"
#include	"../IexSystem/System.h"
#include	"debug\DebugFunction.h"
#include	"sceneGamePlay.h"
#include	"character\Tennis\TennisPlayer.h"
#include	"character\Tennis\TennisPlayerState.h"

#include "../character/Lacrosse/LacrossePlayer.h"
#include "../character/Lacrosse/LacrossePlayerState.h"

//*****************************************************************************************************************************
//
//	�O���[�o���ϐ�
//
//*****************************************************************************************************************************
static iexView* m_pView;
static LPIEXMESH pStage;

//*****************************************************************************************************************************
//
//	������
//
//*****************************************************************************************************************************


bool sceneGamePlay::Initialize()
{
	//	���ݒ�
	iexLight::SetAmbient(0x404040);
	iexLight::SetFog(800, 1000, 0);

	Vector3 dir(1.0f, -1.0f, -0.5f);
	dir.Normalize();
	iexLight::DirLight(shader, 0, &dir, 0.8f, 0.8f, 0.8f);

	m_pView = new iexView;
	m_pView->Set(Vector3(0, 40, -55), Vector3(0, 4, 0));
	
	pStage = new iexMesh("DATA\\STAGE\\Stage.IMO");


	//�L�����N�^�쐬
	CharacterBase::PlayerInfo pl;

	pl.chr_type = CharacterType::_Tennis;
	pl.number = (PlayerNum::Value)0;
	pl.player_type = PlayerType::_Player;
	pl.strong_type = StrongType::__ErrorType;
	
	//�e�j�X���쐬���A�����Ƃ��ăv���C���[����N���X���Z�b�g
	//(new TennisPlayer(pl))->SetState(new TennisState_PlayerControll_Move());

	// ���N���X�쐬
	(new LacrossePlayer(pl))->SetState(new LacrosseState_PlayerControllMove());

	return true;
}

//*****************************************************************************************************************************
//
//		���
//
//*****************************************************************************************************************************

sceneGamePlay::~sceneGamePlay()
{
	delete m_pView;
	delete pStage;

	DefRendererMgr.Release();
	DefGameObjMgr.Release();
}

//*****************************************************************************************************************************
//
//		�X�V
//
//*****************************************************************************************************************************
void	sceneGamePlay::Update()
{
	m_pView->Activate();

	DefGameObjMgr.Update();
}

//*****************************************************************************************************************************
//
//		�`��֘A
//
//*****************************************************************************************************************************

void	sceneGamePlay::Render()
{
	m_pView->Clear();

	pStage->Render();

	DefRendererMgr.DeferredRender();
	DefRendererMgr.ForwardRender();
}