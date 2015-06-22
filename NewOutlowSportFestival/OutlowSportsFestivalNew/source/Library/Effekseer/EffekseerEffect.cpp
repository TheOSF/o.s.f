#include "EffekseerEffect.h"



// �R���X�g���N�^
EffekseerEffect::EffekseerEffect(Manager* pManager, const Handle handle) :
m_pManager(pManager),
m_Handle(handle),
m_Params()
{
	m_Params.Position = Vector3D(0, 0, 0);
	m_Params.Angle = Vector3D(0, 0, 0);
	m_Params.Scale = Vector3D(1, 1, 1);
}


// �f�X�g���N�^
EffekseerEffect::~EffekseerEffect()
{
	m_pManager->StopEffect(m_Handle);
}


// �������L�����ǂ���
bool EffekseerEffect::IsDead()const
{
	return !m_pManager->Exists(m_Handle);
}


// �X�V
void EffekseerEffect::Update()
{
	m_pManager->SetLocation(m_Handle, m_Params.Position);
	m_pManager->SetRotation(m_Handle, m_Params.Angle.X, m_Params.Angle.Y, m_Params.Angle.Z);
	m_pManager->SetScale(m_Handle, m_Params.Scale.X, m_Params.Scale.Y, m_Params.Scale.Z);
}

