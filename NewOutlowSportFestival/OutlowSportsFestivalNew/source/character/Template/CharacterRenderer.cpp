#include "CharacterRenderer.h"

//*************************************************
//	キャラクタ用メッシュクラス
//*************************************************


//通常コンストラクタ
CharacterRenderer::CharacterRenderer(BlendAnimationMesh* pAnimeMesh) :
m_pAnimeMesh(pAnimeMesh),
m_TransMatrix(pAnimeMesh->TransMatrix),
m_UsePartsMotion(false)
{
	Initialize();
}

//部位モーションをする際に
CharacterRenderer::CharacterRenderer(
	BlendAnimationMesh*		pAnimeMesh,
	const std::vector<int>& UpBodyBoneNums,
	const std::vector<int>& DownBodyBoneNums
	):
	m_pAnimeMesh(pAnimeMesh),
	m_TransMatrix(pAnimeMesh->TransMatrix),
	m_UsePartsMotion(false),
	m_UpBodyBoneNumArray(UpBodyBoneNums),
	m_DownBodyBoneNumArray(DownBodyBoneNums)
{
	Initialize();
}

CharacterRenderer::~CharacterRenderer()
{
	delete m_pAnimeMesh;
}

//通常のモーションセット
void CharacterRenderer::SetMotion(int m)
{
	const int nb = m_pAnimeMesh->GetNumBone();

	for (int i = 0; i < nb; ++i)
	{
		m_pAnimeMesh->SetMotion(m, i, 0);
	}
}


//上半身・下半身ごとのボーションセット
void CharacterRenderer::SetBodyUpMotion(int m)
{
	m_BodyUpMotion = m;

	for (
		auto it = m_UpBodyBoneNumArray.begin();
		it != m_UpBodyBoneNumArray.end();
		++it
		)
	{
		m_pAnimeMesh->SetMotion(m, *it, 0);
	}
}

void CharacterRenderer::SetBodyDownMotion(int m)
{
	m_BodyDownMotion = m;

	for (
		auto it = m_DownBodyBoneNumArray.begin();
		it != m_DownBodyBoneNumArray.end();
	++it
		)
	{
		m_pAnimeMesh->SetMotion(m, *it, 0);
	}
}


//通常のモーションスピードセット
void CharacterRenderer::SetMotionSpeed(float t)
{
	m_BodyUpMotionSpeed = m_BodyDownMotionSpeed = t;

	const int nb = m_pAnimeMesh->GetNumBone();

	for (int i = 0; i < nb; ++i)
	{
		m_pAnimeMesh->SetSpeed(i, 0, t);
	}
}

//上半身・下半身ごとのスピードセット
void CharacterRenderer::SetBodyUpMotionSpeed(float t)
{
	m_BodyUpMotionSpeed = t;

	for (
		auto it = m_UpBodyBoneNumArray.begin();
		it != m_UpBodyBoneNumArray.end();
	++it
		)
	{
		m_pAnimeMesh->SetSpeed(*it, 0, t);
	}
}

void CharacterRenderer::SetBodyDownMotionSpeed(float t)
{
	m_BodyDownMotionSpeed = t;

	for (
		auto it = m_DownBodyBoneNumArray.begin();
		it != m_DownBodyBoneNumArray.end();
	++it
		)
	{
		m_pAnimeMesh->SetSpeed(*it, 0, t);
	}
}

//モーション更新
void CharacterRenderer::Update(float t)
{
	m_pAnimeMesh->Animation(t);
	m_pAnimeMesh->Update();
}

//描画
void CharacterRenderer::Render()
{
	m_pAnimeMesh->Render();
}

void CharacterRenderer::Initialize()
{
	m_BodyUpMotionSpeed = m_BodyDownMotionSpeed = 1;
	m_BodyUpMotion = m_BodyDownMotion = 0;
	D3DXMatrixIdentity(&m_TransMatrix);
}