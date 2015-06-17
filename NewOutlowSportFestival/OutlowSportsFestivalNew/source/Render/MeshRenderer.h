#ifndef __MESH_RENDERER_H__
#define __MESH_RENDERER_H__

#include "Renderer.h"
#include "iextreme.h"


//**************************************************************************
//		���b�V�������_���[�N���X(���b�V�����}�C�t���[�������I�ɕ`�悷��)
//**************************************************************************

class MeshRenderer :public DeferredRenderer
{
public:
	MeshRenderer(
		LPIEXMESH	pMesh,		//�`�悷�郁�b�V���̃|�C���^
		bool		MeshDelete	//�������̃��b�V����delete���邩�ǂ���
		);

	~MeshRenderer();

	//�`��
	void Render();

	//���[���h�ϊ��s��̃Z�b�^�E�Q�b�^
	void SetMatrix(const Matrix& mat);
	const Matrix& GetMatrix()const;
private:
	iexMesh*	const	m_pMesh;
	bool		const	m_MeshDelete;
};

#endif