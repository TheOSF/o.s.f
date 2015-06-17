#ifndef __CHARACTER_RENDERER_H__
#define __CHARACTER_RENDERER_H__

#include "../Render/Renderer.h"
#include "../brendanimation/BlendAnimationMesh.h"
#include <vector>

//*************************************************
//	キャラクタ用メッシュクラス
//*************************************************

class CharacterRenderer :public DeferredRenderer
{
public:
	//通常コンストラクタ
	CharacterRenderer(
		BlendAnimationMesh* pAnimeMesh
		);

	//部位モーションをする際に
	CharacterRenderer(
		BlendAnimationMesh*		pAnimeMesh,
		const std::vector<int>& UpBodyBoneNums,
		const std::vector<int>& DownBodyBoneNums
		);

	~CharacterRenderer();

	//通常のモーションセット
	void SetMotion(int m);

	//上半身・下半身ごとのボーションセット
	void SetBodyUpMotion(int m);
	void SetBodyDownMotion(int m);

	//通常のモーションスピードセット
	void SetMotionSpeed(float t);

	//上半身・下半身ごとのスピードセット
	void SetBodyUpMotionSpeed(float t);
	void SetBodyDownMotionSpeed(float t);

	//モーション更新
	void Update(float t);

	//描画
	void Render();

	//ワールド変換行列
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