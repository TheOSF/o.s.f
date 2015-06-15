#include "CharacterFunction.h"
#include "CharacterBase.h"


//À•W‚ÉˆÚ“®—Ê‚ðXV‚·‚é
void chr_func::PositionUpdate(CharacterBase* p)
{
	p->m_Params.pos += p->m_Params.move;
}

//‚w‚yŽ²‚ÅˆÚ“®—Ê‚ð‘«‚·(max_speed‚ð’´‚¦‚È‚¢‚æ‚¤‚ÉÝ’è‚³‚ê‚é)
void chr_func::AddXZMove(CharacterBase*p, float x, float z, float max_speed)
{
	p->m_Params.move.x += x;
	p->m_Params.move.z += z;

	SetMaxXZspeed(p, max_speed);
}

//‘O•ûŒü‚ÉˆÚ“®—Ê‚ðƒ^ƒX
void chr_func::AddMoveFront(CharacterBase*p, float speed, float max_speed)
{
	p->m_Params.move.x += sinf(p->m_Params.angle)*speed;
	p->m_Params.move.z += cosf(p->m_Params.angle)*speed;

	SetMaxXZspeed(p, max_speed);
}

//™X‚ÉŒ¸‘¬‚·‚é(t‚ð‚P‚É‚·‚é‚Æˆêu‚ÅŽ~‚Ü‚é,0‚ÅŒø‰Ê‚È‚µ)
void chr_func::XZMoveDown(CharacterBase*p, float t)
{
	t = min(t, 1);
	t = max(t, 0);
	t = 1 - t;

	p->m_Params.move.x *= t;
	p->m_Params.move.z *= t;
}

//‚w‚y•ûŒü‚ÌˆÚ“®—Ê‚ªmax_speed‚ð’´‚¦‚Ä‚¢‚½‚çAmax_speed‚ÉÝ’è‚·‚é
void chr_func::SetMaxXZspeed(CharacterBase*p, float max_speed)
{
	const float l = sqrtf(p->m_Params.move.x*p->m_Params.move.x + p->m_Params.move.z*p->m_Params.move.z);

	if (l > max_speed)
	{
		p->m_Params.move.x /= l;
		p->m_Params.move.x *= max_speed;

		p->m_Params.move.z /= l;
		p->m_Params.move.z *= max_speed;
	}
}


//Žw’è‚µ‚½êŠ‚ÉŒü‚­
void chr_func::AngleControll(CharacterBase* p, CrVector3 view_pos, float speed)
{
	Vector3 mepos = p->m_Params.pos;

	if (mepos.x == view_pos.x&&mepos.z == view_pos.z) return;

	float cos0, angle = p->m_Params.angle;

	Vector3 v1(sinf(angle), 0, cosf(angle)), v2(view_pos - mepos);

	v2.y = 0;

	float VectorLength = v1.Length()*v2.Length();

	if (VectorLength == 0.0f)
	{
		return;
	}

	cos0 = Vector3Dot(v1, v2) / VectorLength;
	cos0 = 1.0f - cos0;

	if (cos0>speed)cos0 = speed;

	if (v1.z*v2.x - v1.x*v2.z < 0)
	{
		angle -= cos0;
	}
	else{
		angle += cos0;
	}

	p->m_Params.angle = angle;
}


//Œ»Ý‚ÌˆÊ’uAŒ»Ý‚ÌangleAScale‚ð‚à‚Æ‚É•ÏŠ·s—ñ‚ð¶¬‚·‚é
void chr_func::CreateTransMatrix(CharacterBase* p, float Scale, Matrix* pOutMatrix)
{
	Matrix m;

	D3DXMatrixScaling(pOutMatrix, Scale, Scale, Scale);
	D3DXMatrixRotationY(&m, p->m_Params.angle);

	*pOutMatrix *= m;

	D3DXMatrixTranslation(
		&m,
		p->m_Params.pos.x,
		p->m_Params.pos.y,
		p->m_Params.pos.z
		);

	*pOutMatrix *= m;
}