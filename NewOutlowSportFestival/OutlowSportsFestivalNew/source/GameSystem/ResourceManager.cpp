#include "ResourceManager.h"

Resource* Resource::m_pInstance = nullptr;


//-----------------------------------------------------
//              ���\�[�X�Ǘ��N���X
//-----------------------------------------------------

Resource& Resource::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new Resource();
	}
	return *m_pInstance;
}

void Resource::Release()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

void Resource::Regist(MeshType  type, iexMesh* pMesh)
{
	MyAssert(
		m_pMeshArray[type] == nullptr,
		"���b�V�����\�[�X�̓�d�o�^���s���܂��� type= %d ",
		(int)type);

	m_pMeshArray[type] = pMesh;
}

void Resource::Regist(TextureType  type, iex2DObj* pTex)
{
	MyAssert(
		m_pTextureArray[type] == nullptr,
		"�e�N�X�`�����\�[�X�̓�d�o�^���s���܂��� type= %d ",
		(int)type
		);

	m_pTextureArray[type] = pTex;
}

iexMesh*  Resource::Get(MeshType  type)
{
	MyAssert(
		m_pMeshArray[type] != nullptr,
		"�o�^���Ă��Ȃ����\�[�X�̃��b�V�����v������܂��� type = %d ",
		(int)type
		);

	return m_pMeshArray[type];
}

iex2DObj* Resource::Get(TextureType  type)
{
	MyAssert(
		m_pTextureArray[type] != nullptr,
		"�o�^���Ă��Ȃ����\�[�X�̃e�N�X�`�����v������܂��� type = %d ",
		(int)type
		);

	return m_pTextureArray[type];
}

Resource::Resource()
{
	for (int i = 0; i < (int)__MaxMeshType; ++i)
	{
		m_pMeshArray[i] = nullptr;
	}

	for (int i = 0; i < (int)__MaxTextureType; ++i)
	{
		m_pTextureArray[i] = nullptr;
	}
}

Resource::~Resource()
{
	for (int i = 0; i < (int)__MaxMeshType; ++i)
	{
		delete m_pMeshArray[i];
	}

	for (int i = 0; i < (int)__MaxTextureType; ++i)
	{
		delete m_pTextureArray[i];
	}
}