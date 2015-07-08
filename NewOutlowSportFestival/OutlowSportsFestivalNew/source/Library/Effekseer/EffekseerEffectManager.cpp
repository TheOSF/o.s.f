#include "EffekseerEffectManager.h"
#include "EffekseerEffect.h"

//*****************************************************************
//          EffekseerEffectManager�N���X
//          �����̃G�t�F�N�g���Ǘ�����N���X
//*****************************************************************

// �R���X�g���N�^
EffekseerEffectManager::EffekseerEffectManager(Manager* pManager) :
m_pManager(pManager)
{
	
}


// �f�X�g���N�^
EffekseerEffectManager::~EffekseerEffectManager()
{
	// �G�t�F�N�g�̉��
	for (auto& it : m_Effects)
	{
		it.second->Release();
	}
	m_Effects.clear();

	// �}�l�[�W���[�̉��
	if (m_pManager != nullptr)
	{
		m_pManager->Destroy();
		m_pManager = nullptr;
	}
}


// �G�t�F�N�g�ǂݍ���
void EffekseerEffectManager::LoadEffect(EffectID id, const EFK_CHAR* file)
{
	// �`�F�b�N
	MyAssert(
		m_Effects.find(id) == m_Effects.end(), 
		"ID[%d]�ɂ͊��ɓo�^����Ă��܂��B\n",
		id
		);
	
	// �ǂݍ���
	Effect* pEffect = Effect::Create(m_pManager, file);

	MyAssertW(
		pEffect != nullptr,
		L"�t�@�C�� : %s �̓ǂݍ��݂Ɏ��s���܂����B\n", (const wchar_t*)file
		);

	// �o�^
	m_Effects.insert(
		std::pair<EffectID, Effect*>(id, pEffect)
		);
}


// �G�t�F�N�g�Đ�
EffekseerEffect* EffekseerEffectManager::PlayEffect(EffectID id)
{
	auto& it = m_Effects.find(id);

	// �`�F�b�N
	MyAssert(
		it != m_Effects.end(),
		"ID[%d]�ɃG�t�F�N�g���o�^����Ă��܂���B\n",
		id
		);

	// �C���X�^���X�n���h���擾
	EffekseerEffect::Handle handle = m_pManager->Play(it->second, 0, 0, 0);

	return new EffekseerEffect(
		m_pManager,
		handle
		);
}


// ���ׂẴC���X�^���X���X�V
// ���{���ōX�V���邩(60fps�)
void EffekseerEffectManager::UpdateAllInstances(float deltaFrame)
{
	m_pManager->Update(deltaFrame);
}


// ���ׂẴC���X�^���X��`��
void EffekseerEffectManager::RenderAllInstances()
{
	m_pManager->Draw();
}

