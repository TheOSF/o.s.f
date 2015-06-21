#include	"iextreme.h"
#include	"../IexSystem/System.h"
#include	"debug\DebugFunction.h"
#include	"sceneGamePlay.h"
#include	"../Ball/Ball.h"
#include	"../Camera/Camera.h"
#include	"../character/CharacterManager.h"

#include	"../character/Tennis/TennisPlayer.h"
#include	"../character/Tennis/TennisPlayerState.h"
#include	"../character/Soccer/SoccerPlayer.h"
#include	"../character/Soccer/SoccerPlayerState.h"

#include "../Library/Effekseer/EffekseerSystem.h"
#include "../Library/Effekseer/EffekseerEffectManager.h"
#include "../Library/Effekseer/EffekseerEffect.h"

//*****************************************************************************************************************************
//
//	�O���[�o���ϐ�
//
//*****************************************************************************************************************************
static LPIEXMESH pStage;
static EffekseerSystem* pEffekseerSystem;
static EffekseerEffectManager* pEffekseerEffectManager;
static EffekseerEffect* pEffekseerEffect;

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

	DefCamera.m_Position = Vector3(0, 40, -55);
	DefCamera.m_Target = Vector3(0, 4, 0);

	pStage = new iexMesh("DATA\\STAGE\\Stage.IMO");

	//�L�����N�^�쐬
	{
		CharacterBase::PlayerInfo pl;

		pl.chr_type = CharacterType::_Tennis;
		pl.number = (PlayerNum::Value)0;
		pl.player_type = PlayerType::_Player;
		pl.strong_type = StrongType::__ErrorType;

		TennisPlayer* tp = new TennisPlayer(pl);
		tp->SetState(new TennisState_PlayerControll_Move());
	}


	{
		CharacterBase::PlayerInfo pl;

		pl.chr_type = CharacterType::_Tennis;
		pl.number = (PlayerNum::Value)1;
		pl.player_type = PlayerType::_Player;
		pl.strong_type = StrongType::__ErrorType;

		TennisPlayer* tp = new TennisPlayer(pl);
		tp->SetState(new TennisState_PlayerControll_Move());
		tp->m_Params.pos.x += 40;
	}

	{ // Effekseer
		pEffekseerSystem = new EffekseerSystem(iexSystem::Device);
		pEffekseerEffectManager = pEffekseerSystem->CreateManager();

		pEffekseerEffectManager->LoadEffect(0, (const EFK_CHAR*)L"DATA//Effekseer//Sample//test.efk");
		

		// �G�t�F�N�g�Đ�
		pEffekseerEffect = pEffekseerEffectManager->PlayEffect(0);
	}

	return true;
}

//*****************************************************************************************************************************
//
//		���
//
//*****************************************************************************************************************************

sceneGamePlay::~sceneGamePlay()
{
	{// Effekseer
		delete pEffekseerEffect;
		delete pEffekseerEffectManager;
		delete pEffekseerSystem;
	}
	delete pStage;
	DefGameObjMgr.Release();
	DefCharacterMgr.Release();
	DefRendererMgr.Release();
	DefDamageMgr.Release();
	DefBallMgr.Release();
	DefCamera.Release();
}

//*****************************************************************************************************************************
//
//		�X�V
//
//*****************************************************************************************************************************
void	sceneGamePlay::Update()
{
	{// Effekseer

		// �r���[�s��ݒ�
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				pEffekseerSystem->m_ViewMatrix.Values[j][i] = matView.m[j][i];
			}
		}

		// �ˉe�ϊ��s��ݒ�
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				pEffekseerSystem->m_ProjectionMatrix.Values[j][i] = matProjection.m[j][i];
			}
		}

		// �����_���[�̍X�V
		pEffekseerSystem->UpdateParams();

		// �G�t�F�N�g�X�V
		if (pEffekseerEffect->IsDead())
		{
			delete pEffekseerEffect;
			pEffekseerEffect = pEffekseerEffectManager->PlayEffect(0);
		}
		else{
			pEffekseerEffect->m_Params.Angle.Y += 0.02f;
			pEffekseerEffect->Update();
		}

		// �}�l�[�W���[�̍X�V
		pEffekseerEffectManager->UpdateAllInstances(1.0f);
	}

	DefCamera.Update();

	DefGameObjMgr.Update();
}

//*****************************************************************************************************************************
//
//		�`��֘A
//
//*****************************************************************************************************************************

void	sceneGamePlay::Render()
{
	DefCamera.Clear();

	pStage->Render();

	DefRendererMgr.DeferredRender();
	DefRendererMgr.ForwardRender();

	{// Effekseer
		pEffekseerSystem->BeginRendering();
		pEffekseerEffectManager->RenderAllInstances();
		pEffekseerSystem->EndRendering();
	}
}
