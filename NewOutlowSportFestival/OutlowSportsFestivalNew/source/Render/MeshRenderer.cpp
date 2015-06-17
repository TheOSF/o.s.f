#include "MeshRenderer.h"

//**************************************************************************
//		���b�V�������_���[�N���X(���b�V�����}�C�t���[�������I�ɕ`�悷��)
//**************************************************************************

MeshRenderer::MeshRenderer(
	LPIEXMESH	pMesh,
	bool		MeshDelete
	) :
	m_pMesh(pMesh),
	m_MeshDelete(MeshDelete)
{

}

MeshRenderer::~MeshRenderer()
{
	if (m_MeshDelete)
	{
		delete m_pMesh;
	}
}

void MeshRenderer::Render()
{
	m_pMesh->Render();
}


void MeshRenderer::SetMatrix(const Matrix& mat)
{
	m_pMesh->TransMatrix = mat;
}


const Matrix& MeshRenderer::GetMatrix()const
{
	return m_pMesh->TransMatrix;
}