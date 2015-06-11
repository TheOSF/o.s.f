#include "BlendAnimationMesh.h"


//*****************************************************************************
//
//		�R�c�I�u�W�F�N�g
//
//*****************************************************************************

//*****************************************************************************
//		�������E���
//*****************************************************************************
//------------------------------------------------------
//	�R���X�g���N�^
//------------------------------------------------------
BlendAnimationMesh::BlendAnimationMesh(char* filename)
{

	MyAssert(LoadObject(filename), "�ǂݍ��݂Ɏ��s���܂����B�t�@�C���� %s \n", filename);

	for (int i = 0; i<16; i++) Param[i] = 0;

	bLoad = TRUE;
}

//------------------------------------------------------
//	�f�X�g���N�^
//------------------------------------------------------
BlendAnimationMesh::~BlendAnimationMesh()
{
	if (bLoad)
	{
		if (lpSkinInfo) lpSkinInfo->Release();
		delete[] BoneParent;
		delete[] lpBoneMatrix;
		delete[] lpOffsetMatrix;
		delete[] lpMatrix;

		delete[] orgPose;
		delete[] orgPos;
		delete[] CurPose;
		delete[] CurPos;

		delete[] lpVertex;



		//	�A�j���[�V�����f�[�^���
		for (DWORD i = 0; i<NumBone; i++){
			if (lpAnime[i].rotNum > 0)
			{
				delete[] lpAnime[i].rotFrame;
				delete[] lpAnime[i].rot;
			}
			if (lpAnime[i].posNum > 0)
			{
				delete[] lpAnime[i].posFrame;
				delete[] lpAnime[i].pos;
			}
			delete[]Motion[i];
			delete[]dwFrame[i];
			delete[]dwSpeed[i];
			delete[]dwWeight[i];
		}
		delete Motion;
		delete dwFrame;
		delete dwSpeed;
		delete dwWeight;

		delete[] dwFrameFlag;
		delete[] lpAnime;
	}
}

//------------------------------------------------------
//	�N���[���̍쐬
//------------------------------------------------------
BlendAnimationMesh*	BlendAnimationMesh::Clone()
{
	BlendAnimationMesh*	obj = new BlendAnimationMesh(*this);
	obj->SetLoadFlag(FALSE);
	return obj;
}

//*****************************************************************************
//	���ݒ�
//*****************************************************************************
//------------------------------------------------------
//	���[�V�����ݒ�
//------------------------------------------------------
void BlendAnimationMesh::SetMotion(int motion, int n, int l)
{
	int		param;

	if (M_Offset[motion] == 65535) return;
	Motion[n][l] = motion;
	dwFrame[n][l] = M_Offset[motion];
	bChanged = TRUE;

	param = dwFrameFlag[(int)dwFrame[n][l]];
	if ((param != 0xFFFF) && (param & 0x4000)) Param[(param & 0x0F00) >> 8] = (u8)(param & 0x00FF);
}

//*****************************************************************************
//		�X�V����
//*****************************************************************************
void BlendAnimationMesh::Update()
{
	/*	�X�L�����b�V���X�V	*/
	UpdateSkinMeshFrame();
	UpdateBoneMatrix();
	UpdateSkinMesh();

	iexMesh::Update();
	bChanged = FALSE;
}

//------------------------------------------------------
//	���[�V����
//------------------------------------------------------
void BlendAnimationMesh::Animation(float speed)
{
	int		param;
	u32	work;

	for (u32 i = 0; i < NumBone; ++i){
		for (int j = 0; j < max_line; ++j){
			work = (u32)dwFrame[i][j];
			param = dwFrameFlag[(int)dwFrame[i][j]];

			if (param & 0x4000) param = 0xFFFF;
			if (param != 0xFFFF){
				//	�A�j���[�V�����W�����v
				if (param & 0x8000){
					SetMotion(param & 0xFF, i, j);
				}
				else dwFrame[i][j] = (float)param;
			}
			else {
				dwFrame[i][j] += dwSpeed[i][j] * speed;
				if (dwFrame[i][j] >= NumFrame) dwFrame[i][j] = 0;
			}

			if ((int)dwFrame[i][j] != work) bChanged = TRUE;

			param = dwFrameFlag[(int)dwFrame[i][j]];
			if ((param != 0xFFFF) && (param & 0x4000)) Param[(param & 0x0F00) >> 8] = (u8)(param & 0x00FF);
		}
	}
}

void BlendAnimationMesh::UsualAnimation()
{
	Animation(1);
}

void BlendAnimationMesh::Animation(int bone_num, float speed, int j)
{
	int		param;
	u32	work;

	const int i = bone_num;

	work = (u32)dwFrame[i][j];
	param = dwFrameFlag[(int)dwFrame[i][j]];

	if (param & 0x4000) param = 0xFFFF;
	if (param != 0xFFFF){
		//	�A�j���[�V�����W�����v
		if (param & 0x8000){
			SetMotion(param & 0xFF, i, j);
		}
		else dwFrame[i][j] = (float)param;
	}
	else {
		dwFrame[i][j] += dwSpeed[i][j] * speed;
		if (dwFrame[i][j] >= NumFrame) dwFrame[i][j] = 0;
	}

	if ((int)dwFrame[i][j] != work) bChanged = TRUE;

	param = dwFrameFlag[(int)dwFrame[i][j]];
	if ((param != 0xFFFF) && (param & 0x4000)) Param[(param & 0x0F00) >> 8] = (u8)(param & 0x00FF);

}

//**************************************************************************************************
//		�`��
//**************************************************************************************************


//------------------------------------------------------
//		�Œ�@�\�ʏ�`��
//------------------------------------------------------
void BlendAnimationMesh::Render()
{
	//	���X�V
	//if (RenderFrame != dwFrame) Update();
	//	���C���s��ݒ�
	iexMesh::Render();
}

//------------------------------------------------------
//		�Œ�@�\�t���O�w��
//------------------------------------------------------
void BlendAnimationMesh::Render(DWORD flag, float alpha)
{
	//	���X�V
	//if (RenderFrame != dwFrame) Update();
	//	���C���s��ݒ�
	iexMesh::Render(flag, alpha);
}

//------------------------------------------------------
//		�V�F�[�_�[�`��
//------------------------------------------------------
void BlendAnimationMesh::Render(iexShader* shader, char* name)
{
	//	���X�V
	//if (RenderFrame != dwFrame) Update();
	//	���C���s��ݒ�
	iexMesh::Render(shader, name);
}

//*****************************************************************************
//
//		�I�u�W�F�N�g�쐬
//
//*****************************************************************************

typedef struct tagIEMBONE1 {
	Matrix			BoneMatrix;			//	�{�[���s��
	u16				parent;				//	�e�{�[��

	Quaternion		orgPose;			//	��{�p��
	Vector3			orgPos;				//	��{���W

	u16				IndexNum;			//	�e�����_��
	u32				Index[1000];		//	�e�����_Index
	float			Influence[1000];	//	�e����
} IEMBONE1, *LPIEMBONE1;

typedef struct tagIEMMOTION1 {
	u16				NumRotate;			//	��]�L�[�t���[����
	u16				RotateFrame[512];	//	��]�L�[�t���[��
	Quaternion		Rotate[512];		//	�{�[���̏�ԃN�H�[�^�j�I��

	u16				NumPosition;		//	���W�L�[�t���[����
	u16				PositionFrame[512];	//	���W�L�[�t���[��
	Vector3			Position[512];		//	���W
} IEMMOTION1, *LPIEMMOTION1;

typedef struct tagIEMBONE {
	Matrix			BoneMatrix;			//	�{�[���s��
	u16				parent;				//	�e�{�[��

	Quaternion		orgPose;			//	��{�p��
	Vector3			orgPos;				//	��{���W

	u16				IndexNum;			//	�e�����_��
	u32*			Index;				//	�e�����_Index
	float*			Influence;			//	�e����
} IEMBONE, *LPIEMBONE;

typedef struct tagIEMMOTION {
	u16				NumRotate;			//	��]�L�[�t���[����
	u16*			RotateFrame;		//	��]�L�[�t���[��
	Quaternion*		Rotate;				//	�{�[���̏�ԃN�H�[�^�j�I��

	u16				NumPosition;		//	���W�L�[�t���[����
	u16*			PositionFrame;		//	���W�L�[�t���[��
	LPVECTOR3		Position;			//	���W
} IEMMOTION, *LPIEMMOTION;

struct tagIEMFILE
{
	int				version;			//	�o�[�W����	
	//	���b�V�����
	u16				NumVertex;			//	���_��
	void*			lpVertex;			//	���_�o�b�t�@

	u16				NumFace;			//	�|���S����
	u16*			lpFace;				//	�|���S���C���f�b�N�X
	u32*			lpAtr;				//	�|���S���ގ�

	u16				NumMaterial;		//	�}�e���A����
	D3DMATERIAL9	Material[32];		//	�}�e���A��
	char			Texture[32][64];	//	�e�N�X�`���t�@�C��

	//	�{�[�����
	u16				NumBone;
	LPIEMBONE		lpBone;

	//	���[�V�������
	u16				MaxFrame;
	u16				NumMotion;
	u16				M_Offset[256];
	u16				FrameFlag[65535];

	LPIEMMOTION		lpMotion;
};


//------------------------------------------------------
//		�X�L�����쐬
//------------------------------------------------------
LPD3DXSKININFO	BlendAnimationMesh::CreateSkinInfo(LPIEMFILE lpIem)
{
	int				i;
	LPD3DXSKININFO	lpInfo;
	u32				Declaration = D3DFVF_MESHVERTEX;
	if (lpIem->version >= 4) Declaration = D3DFVF_MESHVERTEX2;

	//	�X�L�����쐬
	D3DXCreateSkinInfoFVF(lpIem->NumVertex, Declaration, lpIem->NumBone, &lpInfo);
	//	�{�[���ݒ�
	for (i = 0; i<lpIem->NumBone; i++){
		lpInfo->SetBoneInfluence(i, lpIem->lpBone[i].IndexNum, lpIem->lpBone[i].Index, lpIem->lpBone[i].Influence);
	}
	return lpInfo;
}

//------------------------------------------------------
//		DirectX���b�V���̍쐬
//------------------------------------------------------
LPD3DXMESH	BlendAnimationMesh::CreateMesh(LPIEMFILE lpIem)
{
	LPD3DXMESH	lpMesh;
	u8			*pVertex, *pFace;
	u32			*pData;

	if (lpIem->version < 4)
	{
		u32	Declaration = D3DFVF_MESHVERTEX;
		//	���b�V���쐬
		D3DXCreateMeshFVF(lpIem->NumFace, lpIem->NumVertex, D3DXMESH_MANAGED, Declaration, iexSystem::Device, &lpMesh);
		//	���_�ݒ�
		lpMesh->LockVertexBuffer(0, (void**)&pVertex);
		CopyMemory(pVertex, lpIem->lpVertex, sizeof(MESHVERTEX)*lpIem->NumVertex);
	}
	else {
		u32	Declaration = D3DFVF_MESHVERTEX2;
		//	���b�V���쐬
		D3DXCreateMeshFVF(lpIem->NumFace, lpIem->NumVertex, D3DXMESH_MANAGED, Declaration, iexSystem::Device, &lpMesh);
		//	���_�ݒ�
		lpMesh->LockVertexBuffer(0, (void**)&pVertex);
		CopyMemory(pVertex, lpIem->lpVertex, sizeof(MESHVERTEX2)*lpIem->NumVertex);
	}

	lpMesh->UnlockVertexBuffer();


	//	�ʐݒ�
	lpMesh->LockIndexBuffer(0, (void**)&pFace);
	CopyMemory(pFace, lpIem->lpFace, sizeof(u16)*lpIem->NumFace * 3);
	lpMesh->UnlockIndexBuffer();

	//	�����ݒ�
	lpMesh->LockAttributeBuffer(0, &pData);
	CopyMemory(pData, lpIem->lpAtr, sizeof(u32)*lpIem->NumFace);
	lpMesh->UnlockAttributeBuffer();

	return lpMesh;
}

//------------------------------------------------------
//		�h�d�l����RD�I�u�W�F�N�g�쐬
//------------------------------------------------------
BOOL BlendAnimationMesh::CreateFromIEM(char* path, LPIEMFILE lpIem)
{
	u32		i, j;

	dwFrame = 0;

	{
		const int bone = lpIem->NumBone;

		Motion = new u8*[bone];

		dwFrame = new float*[bone];
		dwSpeed = new float*[bone];
		dwWeight = new float*[bone];

		for (int i = 0; i < bone; ++i)
		{
			Motion[i] = new u8[max_line];
			dwFrame[i] = new float[max_line];
			dwSpeed[i] = new float[max_line];
			dwWeight[i] = new float[max_line];

			for (int j = 0; j < max_line; ++j)
			{
				Motion[i][j] = 0;
				dwFrame[i][j] = 0;
				dwSpeed[i][j] = 1;
				dwWeight[i][j] = 0;
			}
			dwWeight[i][0] = 1;
		}
	}

	//	���b�V���쐬
	lpSkinInfo = CreateSkinInfo(lpIem);
	lpMesh = CreateMesh(lpIem);
	//	���_���R�s�[
	NumVertex = lpIem->NumVertex;

	if (lpIem->version < 4)
	{
		lpVertex = new MESHVERTEX[NumVertex];
		CopyMemory(lpVertex, lpIem->lpVertex, sizeof(MESHVERTEX)*NumVertex);
	}
	else {
		lpVertex = new MESHVERTEX2[NumVertex];
		CopyMemory(lpVertex, lpIem->lpVertex, sizeof(MESHVERTEX2)*NumVertex);
	}

	//	�}�e���A���ݒ�
	MaterialCount = lpIem->NumMaterial;
	lpMaterial = new D3DMATERIAL9[MaterialCount];
	CopyMemory(lpMaterial, lpIem->Material, sizeof(D3DMATERIAL9)*MaterialCount);
	//	�e�N�X�`���ݒ�
	lpTexture = new Texture2D*[MaterialCount];
	lpNormal = new Texture2D*[MaterialCount];
	lpSpecular = new Texture2D*[MaterialCount];
	lpHeight = new Texture2D*[MaterialCount];

	ZeroMemory(lpTexture, sizeof(Texture2D*)*MaterialCount);
	ZeroMemory(lpNormal, sizeof(Texture2D*)*MaterialCount);
	ZeroMemory(lpSpecular, sizeof(Texture2D*)*MaterialCount);
	ZeroMemory(lpHeight, sizeof(Texture2D*)*MaterialCount);

	for (i = 0; i<MaterialCount; i++){
		if (lpIem->Texture[i][0] == '\0') continue;
		//	�e�N�X�`���ǂݍ���
		char	temp[256];
		sprintf(temp, "%s%s", path, lpIem->Texture[i]);
		lpTexture[i] = iexTexture::Load(temp);

		sprintf(temp, "%sN%s", path, lpIem->Texture[i]);
		lpNormal[i] = iexTexture::Load(temp);

		sprintf(temp, "%sS%s", path, lpIem->Texture[i]);
		lpSpecular[i] = iexTexture::Load(temp);

		sprintf(temp, "%sH%s", path, lpIem->Texture[i]);
		lpHeight[i] = iexTexture::Load(temp);
	}

	//
	//	�{�[�����
	//
	NumBone = lpIem->NumBone;
	BoneParent = new WORD[NumBone];
	lpBoneMatrix = new Matrix[NumBone];
	lpOffsetMatrix = new Matrix[NumBone];
	lpMatrix = new Matrix[NumBone];

	orgPose = new Quaternion[NumBone];
	orgPos = new Vector3[NumBone];
	CurPose = new Quaternion[NumBone];
	CurPos = new Vector3[NumBone];

	//
	NumFrame = lpIem->MaxFrame;
	CopyMemory(M_Offset, lpIem->M_Offset, 2 * 256);
	dwFrameFlag = new u16[NumFrame];
	CopyMemory(dwFrameFlag, lpIem->FrameFlag, 2 * NumFrame);

	//	�A�j���[�V�����ݒ�
	lpAnime = new IEXANIME2[NumBone];

	for (i = 0; i<lpIem->NumBone; i++){
		BoneParent[i] = lpIem->lpBone[i].parent;		//	�e
		lpOffsetMatrix[i] = lpIem->lpBone[i].BoneMatrix;	//	����s��
		orgPos[i] = lpIem->lpBone[i].orgPos;		//	�W���ʒu
		orgPose[i] = lpIem->lpBone[i].orgPose;		//	�W���p��

		//	�N�H�[�^�j�I���R�s�[
		lpAnime[i].rotNum = lpIem->lpMotion[i].NumRotate;
		lpAnime[i].rotFrame = new WORD[lpAnime[i].rotNum];
		lpAnime[i].rot = new Quaternion[lpAnime[i].rotNum];
		for (j = 0; j<lpAnime[i].rotNum; j++){
			lpAnime[i].rotFrame[j] = lpIem->lpMotion[i].RotateFrame[j];
			lpAnime[i].rot[j] = lpIem->lpMotion[i].Rotate[j];
		}
		//	�|�W�V�����R�s�[
		lpAnime[i].posNum = lpIem->lpMotion[i].NumPosition;
		if (lpAnime[i].posNum > 0)
		{
			lpAnime[i].posFrame = new WORD[lpAnime[i].posNum];
			lpAnime[i].pos = new Vector3[lpAnime[i].posNum];
		}
		for (j = 0; j<lpAnime[i].posNum; j++){
			lpAnime[i].posFrame[j] = lpIem->lpMotion[i].PositionFrame[j];
			lpAnime[i].pos[j] = lpIem->lpMotion[i].Position[j];
		}
	}
	//	�����ݒ�
	SetPos(.0f, .0f, .0f);
	SetAngle(.0f, .0f, .0f);
	SetScale(1.0f, 1.0f, 1.0f);
	dwFlags = 0;
	iexMesh::Update();

	return TRUE;
}

//*****************************************************************************************************************************
//	iEM�t�@�C���ǂݍ���
//*****************************************************************************************************************************
int		BlendAnimationMesh::LoadiEM(LPIEMFILE lpIem, LPSTR filename)
{
	HANDLE	hfile;
	u32		dum, FileID;
	int		version, i;

	hfile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);
	if (hfile == INVALID_HANDLE_VALUE) return 0;

	//	ID
	ReadFile(hfile, &FileID, 4, &dum, NULL);
	if (FileID == '1MEI') version = 1;
	else if (FileID == '2MEI') version = 2;
	else if (FileID == '3MEI') version = 3;
	else if (FileID == '4MEI') version = 4;
	else version = -1;

	lpIem->version = version;
	//	���_	
	ReadFile(hfile, &lpIem->NumVertex, sizeof(u16), &dum, NULL);
	if (version < 4)
	{
		lpIem->lpVertex = new MESHVERTEX[lpIem->NumVertex];
		ReadFile(hfile, lpIem->lpVertex, sizeof(MESHVERTEX)*lpIem->NumVertex, &dum, NULL);
	}
	else {
		lpIem->lpVertex = new MESHVERTEX2[lpIem->NumVertex];
		ReadFile(hfile, lpIem->lpVertex, sizeof(MESHVERTEX2)*lpIem->NumVertex, &dum, NULL);
	}
	//	�|���S��	
	ReadFile(hfile, &lpIem->NumFace, sizeof(u16), &dum, NULL);
	lpIem->lpFace = new u16[lpIem->NumFace * 3];
	lpIem->lpAtr = new u32[lpIem->NumFace];
	ReadFile(hfile, lpIem->lpFace, sizeof(u16)*lpIem->NumFace * 3, &dum, NULL);
	ReadFile(hfile, lpIem->lpAtr, sizeof(u32)*lpIem->NumFace, &dum, NULL);
	//	�}�e���A��	
	ReadFile(hfile, &lpIem->NumMaterial, sizeof(u16), &dum, NULL);
	ReadFile(hfile, lpIem->Material, sizeof(D3DMATERIAL9)*lpIem->NumMaterial, &dum, NULL);
	ReadFile(hfile, lpIem->Texture, sizeof(char)*lpIem->NumMaterial * 64, &dum, NULL);

	//	�{�[��
	ReadFile(hfile, &lpIem->NumBone, sizeof(u16), &dum, NULL);
	lpIem->lpBone = new IEMBONE[lpIem->NumBone];
	for (i = 0; i<lpIem->NumBone; i++){
		ReadFile(hfile, &lpIem->lpBone[i], sizeof(IEMBONE), &dum, NULL);

		lpIem->lpBone[i].Index = new DWORD[lpIem->lpBone[i].IndexNum];
		ReadFile(hfile, lpIem->lpBone[i].Index, sizeof(DWORD)*lpIem->lpBone[i].IndexNum, &dum, NULL);

		lpIem->lpBone[i].Influence = new float[lpIem->lpBone[i].IndexNum];
		ReadFile(hfile, lpIem->lpBone[i].Influence, sizeof(float)*lpIem->lpBone[i].IndexNum, &dum, NULL);
	}

	//	���[�V����
	ReadFile(hfile, &lpIem->NumMotion, sizeof(u16), &dum, NULL);
	ReadFile(hfile, &lpIem->MaxFrame, sizeof(u16), &dum, NULL);
	ReadFile(hfile, &lpIem->M_Offset, sizeof(u16)* 256, &dum, NULL);
	ReadFile(hfile, &lpIem->FrameFlag, sizeof(u16)*lpIem->MaxFrame, &dum, NULL);
	lpIem->lpMotion = new IEMMOTION[lpIem->NumBone];

	for (i = 0; i<lpIem->NumBone; i++){
		ReadFile(hfile, &lpIem->lpMotion[i], sizeof(IEMMOTION), &dum, NULL);

		lpIem->lpMotion[i].Rotate = new Quaternion[lpIem->lpMotion[i].NumRotate];
		lpIem->lpMotion[i].RotateFrame = new WORD[lpIem->lpMotion[i].NumRotate];
		ReadFile(hfile, lpIem->lpMotion[i].Rotate, sizeof(Quaternion)*lpIem->lpMotion[i].NumRotate, &dum, NULL);
		ReadFile(hfile, lpIem->lpMotion[i].RotateFrame, sizeof(WORD)*lpIem->lpMotion[i].NumRotate, &dum, NULL);

		lpIem->lpMotion[i].Position = new Vector3[lpIem->lpMotion[i].NumPosition];
		lpIem->lpMotion[i].PositionFrame = new WORD[lpIem->lpMotion[i].NumPosition];
		ReadFile(hfile, lpIem->lpMotion[i].Position, sizeof(Vector3)*lpIem->lpMotion[i].NumPosition, &dum, NULL);
		ReadFile(hfile, lpIem->lpMotion[i].PositionFrame, sizeof(WORD)*lpIem->lpMotion[i].NumPosition, &dum, NULL);
	}

	CloseHandle(hfile);

	return version;
}

//*****************************************************************************************************************************
//	�I�u�W�F�N�g�ǂݍ���
//*****************************************************************************************************************************
BOOL	BlendAnimationMesh::LoadObject(char* filename)
{
	IEMFILE		iem;
	char		workpath[MAX_PATH];

	version = LoadiEM(&iem, filename);
	if (version <= 0)
	{
		return FALSE;
	}

	CopyMemory(workpath, filename, lstrlen(filename) + 1);
	for (int i = lstrlen(filename); i>0; i--){
		if (IsDBCSLeadByte(workpath[i - 2])){
			i--;
			continue;
		}
		if (workpath[i - 1] == '\\' || workpath[i - 1] == '/'){
			workpath[i] = '\0';
			break;
		}
	}
	CreateFromIEM(workpath, &iem);

	for (int i = 0; i<iem.NumBone; i++){
		delete[]	iem.lpBone[i].Index;
		delete[]	iem.lpBone[i].Influence;
		delete[]	iem.lpMotion[i].Rotate;
		delete[]	iem.lpMotion[i].RotateFrame;
		delete[]	iem.lpMotion[i].Position;
		delete[]	iem.lpMotion[i].PositionFrame;
	}
	delete[]	iem.lpVertex;
	delete[]	iem.lpFace;
	delete[]	iem.lpAtr;
	delete[]	iem.lpBone;
	delete[]	iem.lpMotion;

	bLoad = TRUE;

	return TRUE;
}


//*****************************************************************************************************************************
//		�R�c�I�u�W�F�N�g�ۑ�
//*****************************************************************************************************************************
BOOL BlendAnimationMesh::SaveObject(LPIEMFILE lpIem, LPSTR filename)
{
	HANDLE	hfile;
	int		i;
	u32		dum;
	u32		FileID = '3MEI';

	if (lpIem->version == 4) FileID = '4MEI';

	hfile = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_WRITE, (LPSECURITY_ATTRIBUTES)NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);
	if (hfile == INVALID_HANDLE_VALUE) return FALSE;
	//	ID
	WriteFile(hfile, &FileID, 4, &dum, NULL);
	//	���_	
	WriteFile(hfile, &lpIem->NumVertex, sizeof(u16), &dum, NULL);
	if (lpIem->version < 4) WriteFile(hfile, (MESHVERTEX*)(lpIem->lpVertex), sizeof(MESHVERTEX)*lpIem->NumVertex, &dum, NULL);
	else WriteFile(hfile, (MESHVERTEX2*)(lpIem->lpVertex), sizeof(MESHVERTEX2)*lpIem->NumVertex, &dum, NULL);

	//	�|���S��	
	WriteFile(hfile, &lpIem->NumFace, sizeof(u16), &dum, NULL);
	WriteFile(hfile, lpIem->lpFace, sizeof(u16)*lpIem->NumFace * 3, &dum, NULL);
	WriteFile(hfile, lpIem->lpAtr, sizeof(u32)*lpIem->NumFace, &dum, NULL);
	//	�}�e���A��	
	WriteFile(hfile, &lpIem->NumMaterial, sizeof(u16), &dum, NULL);
	WriteFile(hfile, lpIem->Material, sizeof(D3DMATERIAL9)*lpIem->NumMaterial, &dum, NULL);
	WriteFile(hfile, lpIem->Texture, sizeof(char)*lpIem->NumMaterial * 64, &dum, NULL);

	//	�{�[��
	WriteFile(hfile, &lpIem->NumBone, sizeof(u16), &dum, NULL);
	for (i = 0; i<lpIem->NumBone; i++){
		WriteFile(hfile, &lpIem->lpBone[i], sizeof(IEMBONE), &dum, NULL);
		WriteFile(hfile, lpIem->lpBone[i].Index, sizeof(DWORD)*lpIem->lpBone[i].IndexNum, &dum, NULL);
		WriteFile(hfile, lpIem->lpBone[i].Influence, sizeof(float)*lpIem->lpBone[i].IndexNum, &dum, NULL);
	}

	//	���[�V����
	WriteFile(hfile, &lpIem->NumMotion, sizeof(u16), &dum, NULL);
	WriteFile(hfile, &lpIem->MaxFrame, sizeof(u16), &dum, NULL);
	WriteFile(hfile, &lpIem->M_Offset, sizeof(u16)* 256, &dum, NULL);
	WriteFile(hfile, &lpIem->FrameFlag, sizeof(u16)*lpIem->MaxFrame, &dum, NULL);

	for (i = 0; i<lpIem->NumBone; i++){
		WriteFile(hfile, &lpIem->lpMotion[i], sizeof(IEMMOTION), &dum, NULL);
		WriteFile(hfile, lpIem->lpMotion[i].Rotate, sizeof(D3DXQUATERNION)*lpIem->lpMotion[i].NumRotate, &dum, NULL);
		WriteFile(hfile, lpIem->lpMotion[i].RotateFrame, sizeof(WORD)*lpIem->lpMotion[i].NumRotate, &dum, NULL);
		WriteFile(hfile, lpIem->lpMotion[i].Position, sizeof(D3DXVECTOR3)*lpIem->lpMotion[i].NumPosition, &dum, NULL);
		WriteFile(hfile, lpIem->lpMotion[i].PositionFrame, sizeof(WORD)*lpIem->lpMotion[i].NumPosition, &dum, NULL);
	}

	CloseHandle(hfile);

	return TRUE;
}









//**************************************************************************************************
//
//		�X�L�����b�V���֘A
//
//**************************************************************************************************

//*****************************************************************************
//	�t���[���X�V
//*****************************************************************************
void	BlendAnimationMesh::UpdateSkinMeshFrame()
{
	u32			i, j;	//int
	int			tt;
	LPIEXANIME2	lpAnime;
	float		t;
	Quaternion tmpq[2];
	Vector3 tmpp;
	float frame;

	for (i = 0; i<NumBone; i++)
	{	//�{�[���̐���������

		lpAnime = &this->lpAnime[i];

		for (tt = 0; tt<2; tt++)
			tmpq[tt].x = tmpq[tt].y = tmpq[tt].z = tmpq[tt].w = 0;

		tmpp.x = tmpp.y = tmpp.z = 0;

		for (int l = 0; l < max_line; ++l)
		{
			frame = dwFrame[i][l];
			//	�|�[�Y�ݒ�
			if (lpAnime->rotNum == 0) CurPose[i] = orgPose[i];
			else if (lpAnime->rotNum == 1) CurPose[i] = lpAnime->rot[0];
			else {
				//	��]�L�[���
				for (j = 0; j < lpAnime->rotNum - 1; j++)
				{
					//	���݈ʒu����
					if ((frame >= lpAnime->rotFrame[j]) && (frame < lpAnime->rotFrame[j + 1]))
					{
						//	�o�߃t���[���v�Z
						t = (float)(frame - lpAnime->rotFrame[j]) / (float)(lpAnime->rotFrame[j + 1] - lpAnime->rotFrame[j]);
						//	���
						CurPose[i] = QuaternionSlerp(lpAnime->rot[j], lpAnime->rot[j + 1], t);
						break;
					}
				}
				if (j == lpAnime->rotNum - 1) CurPose[i] = lpAnime->rot[lpAnime->rotNum - 1];
			}
			tmpq[l] = CurPose[i];

		}

		D3DXQuaternionSlerp(
			(D3DXQUATERNION*)&CurPose[i],
			(D3DXQUATERNION*)&tmpq[0],
			(D3DXQUATERNION*)&tmpq[1],
			dwWeight[i][1]
			);

		float pt[max_line] =
		{
			1 - dwWeight[i][1],
			dwWeight[i][1]
		};

		for (int l = 0; l < max_line; ++l)
		{
			frame = dwFrame[i][l];
			//	���W�ݒ�
			if (lpAnime->posNum == 0) CurPos[i] = orgPos[i];
			else {
				//	�ʒu���
				for (j = 0; j < lpAnime->posNum - 1; j++)
				{
					//	���݈ʒu����
					if ((frame >= lpAnime->posFrame[j]) && (frame < lpAnime->posFrame[j + 1]))
					{
						//	�o�߃t���[���v�Z
						t = (float)(frame - lpAnime->posFrame[j]) / (float)(lpAnime->posFrame[j + 1] - lpAnime->posFrame[j]);
						//	���
						CurPos[i] = lpAnime->pos[j] + (lpAnime->pos[j + 1] - lpAnime->pos[j])*t;
						break;
					}
				}
				if (j == lpAnime->posNum - 1) CurPos[i] = lpAnime->pos[lpAnime->posNum - 1];
			}
			tmpp += CurPos[i] * pt[l];
		}
		CurPos[i] = tmpp;
	}
}

//*****************************************************************************
//	�{�[���s��X�V
//*****************************************************************************
void BlendAnimationMesh::UpdateBoneMatrix()
{
	u32			i;

	//	�{�[���X�V
	for (i = 0; i<NumBone; i++)
	{
		CurPose[i].toMatrix(lpBoneMatrix[i]);
		//	�ʒu���R�s�[
		lpBoneMatrix[i]._41 = CurPos[i].x;
		lpBoneMatrix[i]._42 = CurPos[i].y;
		lpBoneMatrix[i]._43 = CurPos[i].z;

		if (BoneParent[i] != 0xFFFF) lpBoneMatrix[i] *= lpBoneMatrix[BoneParent[i]];
	}
	for (i = 0; i<NumBone; i++)
	{
		lpMatrix[i] = lpOffsetMatrix[i] * lpBoneMatrix[i];
	}
}


//*****************************************************************************
//	�X�L�����b�V���X�V
//*****************************************************************************
void	BlendAnimationMesh::UpdateSkinMesh()
{
	//	���b�V���X�V
	void*	pVertex;
	lpMesh->LockVertexBuffer(D3DLOCK_DISCARD, &pVertex);
	lpSkinInfo->UpdateSkinnedMesh(lpMatrix, NULL, lpVertex, pVertex);
	lpMesh->UnlockVertexBuffer();
}
