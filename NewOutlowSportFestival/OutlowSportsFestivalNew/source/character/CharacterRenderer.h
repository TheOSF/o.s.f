#ifndef __CHARACTER_RENDERER_H__
#define __CHARACTER_RENDERER_H__

#include "../Render/Renderer.h"
#include "../brendanimation/BlendAnimationMesh.h"
#include <vector>

//*************************************************
//	�L�����N�^�p���b�V���N���X
//*************************************************

class CharacterRenderer :public DeferredRenderer
{
public:
	//�ʏ�R���X�g���N�^
	CharacterRenderer(
		BlendAnimationMesh* pAnimeMesh
		);

	//���ʃ��[�V����������ۂ�
	CharacterRenderer(
		BlendAnimationMesh*		pAnimeMesh,
		const std::vector<int>& UpBodyBoneNums,
		const std::vector<int>& DownBodyBoneNums
		);

	~CharacterRenderer();

	//�ʏ�̃��[�V�����Z�b�g
	void SetMotion(int m);

	//�㔼�g�E�����g���Ƃ̃{�[�V�����Z�b�g
	void SetBodyUpMotion(int m);
	void SetBodyDownMotion(int m);

	//�ʏ�̃��[�V�����X�s�[�h�Z�b�g
	void SetMotionSpeed(float t);

	//�㔼�g�E�����g���Ƃ̃X�s�[�h�Z�b�g
	void SetBodyUpMotionSpeed(float t);
	void SetBodyDownMotionSpeed(float t);

	//���[�V�����X�V
	void Update(float t);

	//�`��
	void Render();

	//���[���h�ϊ��s��
	Matrix& m_TransMatrix;
private:
	typedef std::vector<int> BoneNumArray;

	BlendAnimationMesh* m_pAnimeMesh;
	const bool m_UsePartsMotion;

	const BoneNumArray m_UpBodyBoneNumArray;
	const BoneNumArray m_DownBodyBoneNumArray;

	int m_BodyUpMotion;
	int m_BodyDownMotion;

	float m_BodyUpMotionSpeed;
	float m_BodyDownMotionSpeed;

	void Initialize();
};

#endif