#ifndef __BLEND_ANIMATION_MESH_H__
#define __BLEND_ANIMATION_MESH_H__

#include "iextreme.h"

class BlendAnimationMesh : public iexMesh
{
protected:
	static const int max_line=2;
	u8				version;
	u8				Param[16];

	u8**			Motion;			//	現在のモーション番号(骨,ライン)
	u16				M_Offset[256];	//	モーション先頭フレーム

	float**			dwFrame;		//	現在のフレーム(骨,ライン)
	float**			dwSpeed;		//	現在のフレームスピード(骨,ライン)
	float**			dwWeight;		//	現在のラインごとの重み(骨,ライン)

	u32				NumFrame;		//	総フレーム数
	u16*			dwFrameFlag;	//	フレーム情報

	u32				RenderFrame;	//	レンダリングフレーム

	LPIEXANIME2		lpAnime;		//	ボーンアニメーション

	//	頂点情報
	DWORD			NumVertex;
	void*			lpVertex;

	// スキンメッシュ関係
	LPD3DXSKININFO		lpSkinInfo;	// スキン情報

	u32				NumBone;
	LPWORD			BoneParent;
	Matrix*			lpBoneMatrix;
	Matrix*			lpOffsetMatrix;
	Matrix*			lpMatrix;

	Quaternion*		orgPose;
	Vector3*		orgPos;

	Quaternion*		CurPose;
	Vector3*		CurPos;

public:
	void	SetLoadFlag(BOOL bLoad){ this->bLoad = bLoad; }
	BlendAnimationMesh(){
		bLoad = FALSE;
		for (int i = 0; i<16; i++) Param[i] = 0;
	}
	BlendAnimationMesh(char* filename);
	~BlendAnimationMesh();

	BlendAnimationMesh*	Clone();

	BOOL LoadObject(char* filename);
	int LoadiEM(LPIEMFILE lpIem, LPSTR filename);
	BOOL CreateFromIEM(char* path, LPIEMFILE lpIem);

	LPD3DXSKININFO	CreateSkinInfo(LPIEMFILE lpIem);
	LPD3DXMESH	CreateMesh(LPIEMFILE lpIem);

	Quaternion& GetRot(int n){ return CurPose[n]; }

	static BOOL SaveObject(LPIEMFILE lpIem, LPSTR filename);

	void Update();
	void SetMotion(int motion, int n, int l);
	inline int GetMotion(int n,int l){ return Motion[n][l]; }
	inline WORD GetMotionOffset(int m){ return M_Offset[m]; }

	inline void SetFrame(float frame, int n, int l){ dwFrame[n][l] = frame; }
	inline void SetWeight(int n, int line, RATIO r){ dwWeight[n][line] = r; }
	inline void SetSpeed(int n, int line, RATIO speed){ dwSpeed[n][line] = speed; }
	inline float GetFrame(int n, int l){ return dwFrame[n][l]; }
	inline float GetWeight(int n, int l){ return dwWeight[n][l]; }

	void Animation(float speed);
	void UsualAnimation();
	void Animation(int bone_num,float speed,int line);

	void Render();
	void Render(DWORD flag, float alpha = -1);
	void Render(iexShader* shader, char* name);

	inline int GetParam(int n){ return Param[n]; }
	inline void SetParam(int n, int p){ Param[n] = p; }

	inline WORD GetFrameFlag(int frame){ return dwFrameFlag[frame]; }
	inline void SetFrameFlag(int frame, WORD p){ dwFrameFlag[frame] = p; }

	inline int GetNumFrame(){ return NumFrame; }

	inline Quaternion*	GetPose(int n){ return &CurPose[n]; }
	inline Vector3*		GetBonePos(int n){ return &CurPos[n]; }
	inline int	GetNumBone(){ return NumBone; }
	inline Matrix*	GetBone(int n){ return &lpBoneMatrix[n]; }
	
	void UpdateSkinMeshFrame();
	void UpdateBoneMatrix();
	void UpdateSkinMesh();
};


#endif