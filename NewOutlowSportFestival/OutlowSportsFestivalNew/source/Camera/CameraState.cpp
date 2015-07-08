#include "CameraState.h"
#include "../character/CharacterManager.h"
#include "../character/CharacterFunction.h"
#include "../character/CharacterBase.h"

//�������̃J�����X�e�[�g


void CameraStateGamePlay::Enter(Camera* c)
{

}

void CameraStateGamePlay::Execute(Camera* c)
{

	const Vector3 first_pos(0, 40, -55);	//�K��
	const CharacterManager::CharacterMap& chr_map = DefCharacterMgr.GetCharacterMap();

	//�L�����N�^�����Ȃ��ꍇ�ړ��ł��Ȃ�
	if (chr_map.empty())
	{
		return;
	}

	Vector3 center(0, 0, 0);
	int livecnt = 0;
	const float viewangle = PI / 4.5f;	//�J�����̎���p
	float dRightLen = 0;

	//�S�L�����N�^���W�̕��ύ��W���Z�o����
	for (auto it = chr_map.begin();
		it != chr_map.end();
		++it)
	{
		if (chr_func::isDie(it->first))continue;
		center += it->first->m_Params.pos;
		livecnt++;
	}

	if (livecnt > 1)
	{
		center /= (float)livecnt;
	}
	center.z -= 4;	//�኱��O��

	//�J�����̃^�[�Q�b�g����
	c->m_Target += (center - c->m_Target)*0.02f;



	//�ǂꂾ���J���������������Z�o����
	for (auto it = chr_map.begin();
		it != chr_map.end();
		++it)
	{
		if (chr_func::isDie(it->first))continue;
		CrVector3 chrpos = it->first->m_Params.pos;

		//�J���������_����̋��������߂�
		float rlen = Vector3Length(chrpos - center);
		rlen += 17;	//������Ƒ傫�߂Ɉ�������

		if (dRightLen < rlen)dRightLen = rlen;	//�ő�Ȃ�X�V
	}

	Vector3 mVec = first_pos - center;
	Vector3 moveTarget;
	mVec.Normalize();

	//����p��tan����ڕW������ɓ���邽�߂̌���������Z�o
	float b = dRightLen / tanf(viewangle);

	//�ړ��ڕW���v�Z
	moveTarget = center + mVec*b;

	//��Ԃ���
	c->m_Position += (moveTarget - c->m_Position)*0.04f;

}

void CameraStateGamePlay::Exit(Camera* c)
{


}