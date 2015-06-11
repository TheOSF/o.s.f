#ifndef __RENDERER_H__
#define __RENDERER_H__

//*************************************************
//	�`��N���X�x�[�X
//*************************************************
#include <map>

//�f�B�t�@�[�h�`��p�N���X
class DeferredRenderer
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^�Ŏ����I�ɕ`������邽�߂̓o�^������
	DeferredRenderer();
	virtual ~DeferredRenderer();

	//�`��(�����I�ɌĂ΂��)
	virtual void Render() = 0;
};

typedef DeferredRenderer* LpDeferredRenderer;

//�t�H���[�h�`��p�N���X(�����I�u�W�F�N�g�p)
class ForwardRenderer
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^�Ŏ����I�ɕ`������邽�߂̓o�^������
	ForwardRenderer();
	virtual ~ForwardRenderer();
	
	//���̕ϐ������Ƃɒl���Ⴂ���Ԃ�Sort����
	float m_SortZ;
	
	//Z�l�v�Z�����̊֐��Ŏ��s���邱�Ƃ��ł���
	virtual void CalcZ() = 0;

	//�`��(�����I�ɌĂ΂��)
	virtual void Render() = 0;
};
typedef ForwardRenderer* LpForwardRenderer;



//*************************************************
//	�`��}�l�[�W��
//*************************************************
class RendererManager
{
public:
	static RendererManager& GetInstance();
	static void Release();

	//�f�B�t�@�[�h�`��p�N���X�̒ǉ��E�폜
	bool AddDeferredRenderer(LpDeferredRenderer pDef);
	bool EraceDeferredRenderer(LpDeferredRenderer pDef);

	//�t�H���[�h�`��p�N���X�̒ǉ��E�폜
	bool AddForwardRenderer(LpForwardRenderer pFor);
	bool EraceForwardRenderer(LpForwardRenderer pFor);

	//�f�B�t�@�[�h�`��
	void DeferredRender();

	//�t�H���[�h�`��
	void ForwardRender();
private:
	RendererManager();
	~RendererManager();

	typedef std::map<LpDeferredRenderer, LpDeferredRenderer> DeferredRendererMap;
	typedef std::map<LpForwardRenderer, LpForwardRenderer> ForwardRendererMap;

	static RendererManager* m_pInstance;

	DeferredRendererMap m_DeferredRendererMap;
	ForwardRendererMap m_ForwardRendererMap;
};

#define DefRendererMgr (RendererManager::GetInstance())

#endif