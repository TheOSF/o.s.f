#include "CharacterRenderer.h"

//*************************************************
//	�L�����N�^�p���b�V���N���X
//*************************************************


//�ʏ�R���X�g���N�^
CharacterRenderer::CharacterRenderer(BlendAnimationMesh* pAnimeMesh) :
m_pAnimeMesh(pAnimeMesh),
m_TransMatrix(pAnimeMesh->TransMatrix),
m_UsePartsMotion(false)
{
	Initialize();
}

//���ʃ��[�V����������ۂ�
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

//�ʏ�̃��[�V�����Z�b�g
void CharacterRenderer::SetMotion(int m)
{
	const int nb = m_pAnimeMesh->GetNumBone();

	for (int i = 0; i < nb; ++i)
	{
		m_pAnimeMesh->SetMotion(m, i, 0);
	}
}


//�㔼�g�E�����g���Ƃ̃{�[�V�����Z�b�g
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


//�ʏ�̃��[�V�����X�s�[�h�Z�b�g
void CharacterRenderer::SetMotionSpeed(float t)
{
	m_BodyUpMotionSpeed = m_BodyDownMotionSpeed = t;

	const int nb = m_pAnimeMesh->GetNumBone();

	for (int i = 0; i < nb; ++i)
	{
		m_pAnimeMesh->SetSpeed(i, 0, t);
	}
}

//�㔼�g�E�����g���Ƃ̃X�s�[�h�Z�b�g
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

//���[�V�����X�V
void CharacterRenderer::Update(float t)
{
	m_pAnimeMesh->Animation(t);
	m_pAnimeMesh->Update();
}

//�`��
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