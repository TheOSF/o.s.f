


#include "BulletSystem.h"
#include "BulletDebug.h"

#include "../../utillity/SafeMethod.h"
#include <memory>

// Bullet�� new ���I�[�o�[���[�h����Ă��邽��
#if defined new
#undef new
#endif


//*****************************************************************
//          RigidBody�N���X
//*****************************************************************

// �R���X�g���N�^
RigidBody::RigidBody() :
collisionType(ct_nothing),
pCollisionShape(nullptr),
pRigidBody(nullptr),
pTriangleMeshes(nullptr)
{
}


// �R���X�g���N�^
RigidBody::RigidBody(
	CollisionTypes       collisionType,
	btCollisionShape* pCollisionShape,
	btRigidBody*        pRigidBody
	) :
	collisionType(collisionType),
	pCollisionShape(pCollisionShape),
	pRigidBody(pRigidBody),
	pTriangleMeshes(nullptr)
{

}


// �R���X�g���N�^
RigidBody::RigidBody(
	CollisionTypes       collisionType,
	btCollisionShape* pCollisionShape,
	btRigidBody*        pRigidBody,
	btTriangleMesh*   pTriangleMeshes
	) :
	collisionType(collisionType),
	pCollisionShape(pCollisionShape),
	pRigidBody(pRigidBody),
	pTriangleMeshes(pTriangleMeshes)
{

}


// �f�X�g���N�^
RigidBody::~RigidBody()
{
	safe_delete(pCollisionShape);
	safe_delete(pRigidBody);
	safe_array_delete(pTriangleMeshes);
}


// �]���s����擾 ���X�P�[�����O�Ȃ�
void RigidBody::Get_TransMatrix(Matrix& mat)
{
	Matrix R, T;
	btTransform transform = pRigidBody->getWorldTransform();
	btVector3 pos = transform.getOrigin();
	btQuaternion rot = transform.getRotation();

	D3DXQUATERNION r(rot.x(), rot.y(), rot.z(), -rot.w());

	D3DXMatrixIdentity(&T);
	D3DXMatrixIdentity(&R);

	D3DXMatrixTranslation(&T, pos.x(), pos.y(), pos.z());
	D3DXMatrixRotationQuaternion(&R, &r);
	
	mat = R*T;
}


// �L�l�}�e�B�b�N�I�u�W�F�N�g�𓮂���
bool RigidBody::TransformKinematicObject(const Vector3& pos, const Vector3& angle)
{
	if (collisionType != ct_kinematic)
	{// �L�l�}�e�B�b�N�I�u�W�F�N�g�ȊO�͓������Ȃ�
		return false;
	}

	btTransform transform;
	transform.setIdentity();

	// ���W�ݒ�
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z));

	// ��]�ݒ�
	// x���𔽓]���ĉE��n�ɂȂ��Ă�́H ��������...
	transform.setRotation(btQuaternion(-angle.x, angle.y, angle.z));

	// �K��
	pRigidBody->getMotionState()->setWorldTransform(transform);

	return true;
}



//*****************************************************************
//          BulletSystem�N���X
//*****************************************************************
//-------------------------------------
//     Singleton �֘A
//-------------------------------------

// Singleton ������
bool BulletSystem::Initialize()
{
	return true;
}


// Singleton ���
bool BulletSystem::Release()
{
	return true;
}


//-------------------------------------
//     �����o�֐�
//-------------------------------------

// Bullet������
bool BulletSystem::InitializeBulletPhysics(const btVector3& gravity, IDirect3DDevice9* pDevice)
{
	// �Փˌ��o���@�̑I��(�f�t�H���g��I��)
	m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
	m_pDispatcher = new btCollisionDispatcher(
		m_pCollisionConfiguration
		);

	// �u���[�h�t�F�[�Y�@�̐ݒ�(Dynamic AABB tree method)
	m_pOverlappingPairCache = new btDbvtBroadphase();

	// �S��(���̊ԃ����N)�̃\���o�ݒ�
	m_pSolver = new btSequentialImpulseConstraintSolver();

	// ���[���h����
	m_pDyamicsWorld = new btDiscreteDynamicsWorld(
		m_pDispatcher, 
		m_pOverlappingPairCache, 
		m_pSolver, 
		m_pCollisionConfiguration
		);

	// �d�͐ݒ�
	m_pDyamicsWorld->setGravity(gravity);

	
	if (pDevice != nullptr)
	{// �f�o�b�O�`��N���X�ݒ�
		m_pDebugDrawer = new BulletDebugDrawer(pDevice);
		m_pDyamicsWorld->setDebugDrawer(m_pDebugDrawer);
		m_pDebugDrawer->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	}
	else
	{
		m_pDebugDrawer = nullptr;
	}

	return true;
}


// Bullet���
bool BulletSystem::ReleaseBulletPhysics()
{
	// ���X�g�̒��g�����
	for (auto& it : m_RigidBodyList)
	{
		RigidBody* p = it;

		m_pDyamicsWorld->removeRigidBody(p->pRigidBody);

		delete p->pRigidBody->getMotionState();
		
		safe_delete(p);
	}

	m_RigidBodyList.clear();

	//delete collision shapes
	btCollisionShape* pShape;
	int size = m_pCollisionShapes.size();
	for (int i = 0; i < size; i++)
	{
		pShape = m_pCollisionShapes[i];
		m_pCollisionShapes[i] = nullptr;
		safe_delete(pShape);
	}

	//delete dynamics world
	safe_delete(m_pDyamicsWorld);

	//delete solver
	safe_delete(m_pSolver);

	//delete broadphase
	safe_delete(m_pOverlappingPairCache);

	//delete dispatcher
	safe_delete(m_pDispatcher);

	//delete collision configuration
	safe_delete(m_pCollisionConfiguration);

	//delete debug drawer
	safe_delete(m_pDebugDrawer);

	m_pCollisionShapes.clear();

	return true;
}


// �����V�~�����[�V������i�߂�
void BulletSystem::StepSimulation(float deltaTime)
{
	m_pDyamicsWorld->stepSimulation(deltaTime, 1, deltaTime);
}


// iexMesh�����[���h�ɐÓI�I�u�W�F�N�g�Ƃ��Ĕz�u
RigidBody* BulletSystem::AddRigidMesh(
	iexMesh* pMesh,
	float m,
	RigidBody::CollisionTypes collisionType,
	float friction,
	float restitution,
	const Vector3&velocity,
	const Vector3& localInertia
	)
{
	// ���b�V���擾
	LPD3DXMESH mesh = pMesh->GetMesh();

	//	���擾	
	u32 fvf = mesh->GetFVF();

	//	���_�T�C�Y�v�Z
	int VertexSize = D3DXGetFVFVertexSize(fvf) / sizeof(float);

	// �|���S�����擾
	u32 NumIndices = mesh->GetNumFaces();

	
	float	*pVertices; // ���_
	u16 *pIndices;   // �C���f�b�N�X

	//	�o�b�t�@���b�N
	mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);
	mesh->LockIndexBuffer(D3DLOCK_READONLY, (void**)&pIndices);

	// �O�p�`���X�g�ō��̂𐶐�����
	btTriangleMesh* pbtTriangleMesh = new btTriangleMesh();
	Vector3 scale = pMesh->GetScale();

	// �O�p�`�̒��_
	Vector3 v1, v2, v3;

	for (u32 i = 0; i < NumIndices; i++)
	{
		//	�ʒ��_�擾
		int a = pIndices[i * 3 + 0] * VertexSize;
		v1.x = pVertices[a] * scale.x;	v1.y = pVertices[a + 1] * scale.y;	v1.z = pVertices[a + 2] * scale.z;

		int b = pIndices[i * 3 + 1] * VertexSize;
		v2.x = pVertices[b] * scale.x;	v2.y = pVertices[b + 1] * scale.y;	v2.z = pVertices[b + 2] * scale.z;

		int c = pIndices[i * 3 + 2] * VertexSize;
		v3.x = pVertices[c] * scale.x;	v3.y = pVertices[c + 1] * scale.y;	v3.z = pVertices[c + 2] * scale.z;

		pbtTriangleMesh->addTriangle(
			btVector3(v1.x, v1.y, v1.z),
			btVector3(v2.x, v2.y, v2.z),
			btVector3(v3.x, v3.y, v3.z)
			);
	}

	// �o�b�t�@�A�����b�N
	mesh->UnlockVertexBuffer();
	mesh->UnlockIndexBuffer();

	//�O�p�`���b�V���ŃV�F�C�v���쐬
	btBvhTriangleMeshShape* pbtShape = new btBvhTriangleMeshShape(pbtTriangleMesh, true);

	// �ÓI�I�u�W�F�N�g�Ȃ̂Ŏ���0
	btScalar mass(m);

	btTransform transform;
	transform.setIdentity();

	// ���W�ݒ�
	Vector3 pos = pMesh->GetPos();
	transform.setOrigin(
		btVector3(pos.x, pos.y, pos.z)
		);

	// ��]�ݒ�
	Vector3 angle = pMesh->GetAngle();

	transform.setRotation(
		btQuaternion(-angle.x, angle.y, angle.z)
		);

	// btRigidBody����
	btCollisionShape* pbtCollisionShape = pbtShape;


	btRigidBody::btRigidBodyConstructionInfo rigidBodyInfo(
		mass,
		new btDefaultMotionState(transform),
		pbtCollisionShape,
		btVector3(localInertia.x, localInertia.y, localInertia.z)
		);

	// �����W��
	rigidBodyInfo.m_restitution = restitution;

	// ���C
	rigidBodyInfo.m_friction = friction;

	btRigidBody* pbtRigidBody = new btRigidBody(rigidBodyInfo);


	int maskType = 0;
	switch (collisionType)
	{
	case RigidBody::ct_dynamic:
		//----------------------------------
		// ���I����
		//----------------------------------

		// �}�X�N�^�C�v�ݒ�
		maskType = RigidBody::ct_dynamic | RigidBody::ct_kinematic | RigidBody::ct_static;

		// �ړ����x
		pbtRigidBody->setLinearVelocity(
			btVector3(velocity.x, velocity.y, velocity.z)
			);

		// ��]���x
		pbtRigidBody->setAngularVelocity(btVector3(0, 0, 0));
		break;

	case RigidBody::ct_static:
		//----------------------------------
		// �ÓI����
		//----------------------------------

		// �}�X�N�^�C�v�ݒ�
		maskType = RigidBody::ct_dynamic;

		// �ÓI���̂ɐݒ�
		pbtRigidBody->setCollisionFlags(
			pbtRigidBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT
			);

		break;


	case RigidBody::ct_kinematic:
		//----------------------------------
		// �L�l�}�e�B�b�N����
		//----------------------------------

		// �}�X�N�^�C�v�ݒ�
		maskType = RigidBody::ct_dynamic;

		// �L�l�}�e�B�b�N���̂ɐݒ�
		pbtRigidBody->setCollisionFlags(
			pbtRigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT
			);
		pbtRigidBody->setActivationState(DISABLE_DEACTIVATION);
		break;

	default:
		break;
	}

	// ���[���h�ɒǉ�
	m_pDyamicsWorld->addRigidBody(
		pbtRigidBody, 
		(short)collisionType, 
		(short)maskType
		);

	// RigidBody�N���X����
	RigidBody* pRigidBody = new RigidBody(
		collisionType, 
		pbtCollisionShape,
		pbtRigidBody, 
		pbtTriangleMesh
		);

	// ���X�g�ɒǉ�
	m_RigidBodyList.insert(pRigidBody);

	return pRigidBody;
}


// Box�����[���h�ɒǉ�
RigidBody* BulletSystem::AddRigidBox(
	float m,
	RigidBody::CollisionTypes collisionType,
	const Vector3& pos,
	const Vector3& angle,
	const Vector3& scale,
	float friction,
	float restitution,
	const Vector3&velocity
	)
{
	// ����
	btScalar mass(m);

	btTransform transform;
	transform.setIdentity();

	// ���W�ݒ�
	transform.setOrigin(
		btVector3(pos.x, pos.y, pos.z)
		);

	// ��]�ݒ�
	transform.setRotation(
		btQuaternion(-angle.x, angle.y, angle.z)
		);

	// BoxShape����
	btCollisionShape* pbtCollisionShape = new btBoxShape(
		btVector3(scale.x, scale.y, scale.z)
		);

	// �������[�����g�̌v�Z
	btVector3 localInertia;
	pbtCollisionShape->calculateLocalInertia(mass, localInertia);

	// btRigidBody����
	btRigidBody::btRigidBodyConstructionInfo rigidBodyInfo(
		mass,
		new btDefaultMotionState(transform),
		pbtCollisionShape,
		localInertia
		);

	// �����W��
	rigidBodyInfo.m_restitution = restitution;

	// ���C
	rigidBodyInfo.m_friction = friction;

	btRigidBody* pbtRigidBody = new btRigidBody(rigidBodyInfo);


	int maskType = 0;
	switch (collisionType)
	{
	case RigidBody::ct_dynamic:  
		//----------------------------------
		// ���I����
		//----------------------------------

		// �}�X�N�^�C�v�ݒ�
		maskType = RigidBody::ct_dynamic | RigidBody::ct_kinematic | RigidBody::ct_static;

		// �ړ����x
		pbtRigidBody->setLinearVelocity(
			btVector3(velocity.x, velocity.y, velocity.z)
			);

		// ��]���x
		pbtRigidBody->setAngularVelocity(btVector3(0, 0, 0));
		break;
		
	case RigidBody::ct_static:
		//----------------------------------
		// �ÓI����
		//----------------------------------

		// �}�X�N�^�C�v�ݒ�
		maskType = RigidBody::ct_dynamic;
		break;

		
	case RigidBody::ct_kinematic:
		//----------------------------------
		// �L�l�}�e�B�b�N����
		//----------------------------------
		
		// �}�X�N�^�C�v�ݒ�
		maskType = RigidBody::ct_dynamic;

		// �L�l�}�e�B�b�N���̂ɐݒ�
		pbtRigidBody->setCollisionFlags(
			pbtRigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT
			);
		pbtRigidBody->setActivationState(DISABLE_DEACTIVATION);
		break;

	default:
		break;
	}

	// ���[���h�ɒǉ�
	m_pDyamicsWorld->addRigidBody(pbtRigidBody, (short)collisionType, (short)maskType);

	// RigidBody����
	RigidBody* pRigidBody = new RigidBody(
		collisionType,
		pbtCollisionShape,
		pbtRigidBody
		);

	// ���X�g�ɒǉ�
	m_RigidBodyList.insert(pRigidBody);

	return pRigidBody;
}


// Sphere�����[���h�ɒǉ�
RigidBody* BulletSystem::AddRigidSphere(
	float m,
	RigidBody::CollisionTypes collisionType,
	const Vector3& pos,
	const Vector3& angle,
	float radius,
	float friction,
	float restitution,
	const Vector3& velocity
	)
{
	// ����
	btScalar mass(m);

	btTransform transform;
	transform.setIdentity();

	// ���W�ݒ�
	transform.setOrigin(
		btVector3(pos.x, pos.y, pos.z)
		);

	// ��]�ݒ�
	transform.setRotation(
		btQuaternion(-angle.x, angle.y, angle.z)
		);

	// BoxShape����
	btCollisionShape* pbtCollisionShape = new btSphereShape(radius);

	// �������[�����g�̌v�Z
	btVector3 localInertia;
	pbtCollisionShape->calculateLocalInertia(mass, localInertia);

	// btRigidBody����
	btRigidBody::btRigidBodyConstructionInfo rigidBodyInfo(
		mass,
		new btDefaultMotionState(transform),
		pbtCollisionShape,
		localInertia
		);

	// �����W��
	rigidBodyInfo.m_restitution = restitution;

	// ���C
	rigidBodyInfo.m_friction = friction;

	btRigidBody* pbtRigidBody = new btRigidBody(rigidBodyInfo);


	int maskType = 0;
	switch (collisionType)
	{
	case RigidBody::ct_dynamic:
		//----------------------------------
		// ���I����
		//----------------------------------

		// �}�X�N�^�C�v�ݒ�
		maskType = RigidBody::ct_dynamic | RigidBody::ct_kinematic | RigidBody::ct_static;

		// �ړ����x
		pbtRigidBody->setLinearVelocity(
			btVector3(velocity.x, velocity.y, velocity.z)
			);

		// ��]���x
		pbtRigidBody->setAngularVelocity(btVector3(0, 0, 0));
		break;

	case RigidBody::ct_static:
		//----------------------------------
		// �ÓI����
		//----------------------------------

		// �R���W�����^�C�v�ݒ�
		maskType = RigidBody::ct_dynamic;
		break;


	case RigidBody::ct_kinematic:
		//----------------------------------
		// �L�l�}�e�B�b�N����
		//----------------------------------

		// �R���W�����^�C�v�ݒ�
		maskType = RigidBody::ct_dynamic;

		// �L�l�}�e�B�b�N���̂ɐݒ�
		pbtRigidBody->setCollisionFlags(
			pbtRigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT
			);
		pbtRigidBody->setActivationState(DISABLE_DEACTIVATION);
		break;

	default:
		break;
	}

	// ���[���h�ɒǉ�
	m_pDyamicsWorld->addRigidBody(pbtRigidBody, (short)collisionType, (short)maskType);

	// RigidBody����
	RigidBody* pRigidBody = new RigidBody(
		collisionType,
		pbtCollisionShape,
		pbtRigidBody
		);

	// ���X�g�ɒǉ�
	m_RigidBodyList.insert(pRigidBody);

	return pRigidBody;
}


// RigidBody�����[���h����폜����
void BulletSystem::RemoveRigidBody(RigidBody* pRigidBody)
{
	if (!pRigidBody)
	{
		return;
	}

	// ���̂��폜
	m_pDyamicsWorld->removeRigidBody(pRigidBody->pRigidBody);

	delete pRigidBody->pRigidBody->getMotionState();

	m_RigidBodyList.erase(pRigidBody);

	safe_delete(pRigidBody);

}


// �f�o�b�O�`��
void BulletSystem::DebugDrawWorld()
{
	m_pDyamicsWorld->debugDrawWorld();
}



// ����̂��ǂ�������
#if defined(DEBUG)||defined(_DEBUG)

// new �̍Ē�`
#ifndef new

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif

#endif
