#ifndef __MESH_RENDERER_H__
#define __MESH_RENDERER_H__

#include "Renderer.h"
#include "iextreme.h"


//**************************************************************************
//		メッシュレンダラークラス(メッシュをマイフレーム自動的に描画する)
//**************************************************************************

class MeshRenderer :public DeferredRenderer
{
public:
	MeshRenderer(
		LPIEXMESH	pMesh,		//描画するメッシュのポインタ
		bool		MeshDelete	//第一引数のメッシュをdeleteするかどうか
		);

	~MeshRenderer();

	//描画
	void Render();

	//ワールド変換行列のセッタ・ゲッタ
	void SetMatrix(const Matrix& mat);
	const Matrix& GetMatrix()const;
private:
	iexMesh*	const	m_pMesh;
	bool		const	m_MeshDelete;
};

#endif