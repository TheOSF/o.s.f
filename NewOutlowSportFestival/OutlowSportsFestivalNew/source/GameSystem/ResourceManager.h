#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include "iextreme.h"

//-----------------------------------------------------
//              リソース管理クラス
//-----------------------------------------------------

class Resource
{
public:
	//メッシュタイプ
	enum MeshType
	{
		_Sphere, //球

		__MaxMeshType //max
	};
	
	//テクスチャタイプ
	enum TextureType
	{
		_White, //白いテクスチャ

		__MaxTextureType //max
	};

	//実態の取得・解放
	static Resource& GetInstance();
	static void Release();

	//登録
	void Regist(MeshType  type, iexMesh* pMesh);
	void Regist(TextureType  type, iex2DObj* pMesh);
	
	//リソースのゲッタ
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