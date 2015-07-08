#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include "iextreme.h"

//-----------------------------------------------------
//              ���\�[�X�Ǘ��N���X
//-----------------------------------------------------

class Resource
{
public:
	//���b�V���^�C�v
	enum MeshType
	{
		_Sphere, //��

		__MaxMeshType //max
	};
	
	//�e�N�X�`���^�C�v
	enum TextureType
	{
		_White, //�����e�N�X�`��

		__MaxTextureType //max
	};

	//���Ԃ̎擾�E���
	static Resource& GetInstance();
	static void Release();

	//�o�^
	void Regist(MeshType  type, iexMesh* pMesh);
	void Regist(TextureType  type, iex2DObj* pMesh);
	
	//���\�[�X�̃Q�b�^
	iexMesh*  Get(MeshType  type);
	iex2DObj* Get(TextureType  type);

private:

	Resource();
	Resource(const Resource&);
	~Resource();

	static Resource* m_pInstance;

	iexMesh*  m_pMeshArray[__MaxMeshType];
	iex2DObj* m_pTextureArray[__MaxTextureType];
};

#define DefResource (Resource::GetInstance())

#endif