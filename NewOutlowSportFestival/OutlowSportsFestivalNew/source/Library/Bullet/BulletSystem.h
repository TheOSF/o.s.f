#pragma once

//*****************************************************************
//          BulletSystem.h
//          IEX �ƘA�g���Ďg����悤�ɂ��Ă���܂�
//          �Ȃ�� Bullet Physics �͉E��n�Ȃ�...
//*****************************************************************

// Bullet�� new ���I�[�o�[���[�h����Ă��邽��
#if defined new
#undef new
#endif


#include <btBulletDynamicsCommon.h>
#include "../../utillity/Singleton.h"
#include <unordered_set>

#if defined(DEBUG)||defined(_DEBUG)

#pragma comment(lib,"BulletCollision_Debug.lib")
#pragma comment(lib,"BulletDynamics_Debug.lib")
#pragma comment(lib,"LinearMath_Debug.lib")

#else

#pragma comment(lib,"BulletCollision.lib")
#pragma comment(lib,"BulletDynamics.lib")
#pragma comment(lib,"LinearMath.lib")

#endif


//*****************************************************************
//          RigidBody�N���X
//*****************************************************************
struct RigidBody
{
	// �R���W�����^�C�v
	enum CollisionTypes
	{
		ct_nothing = 0,                // Nothing
		ct_dynamic = (1 << 1),   // ���I�I�u�W�F�N�g
		ct_static = (1 << 2),        // �ÓI�I�u�W�F�N�g
		ct_kinematic = (1 << 3), // �L�l�}�e�B�b�N�I�u�W�F�N�g
	};

	CollisionTypes        collisionType;       // �R���W�����^�C�v
	btCollisionShape*  pCollisionShape;  // CollisionShape
	btRigidBody*         pRigidBody;         // RigidBody
	btTriangleMesh*    pTriangleMeshes; // TriangleMeshes ���z��Ƃ��Ĉ���

	// �R���X�g���N�^
	RigidBody();
	RigidBody(CollisionTypes collisionType, btCollisionShape* pCollisionShape, btRigidBody* pRigidBody);
	RigidBody(CollisionTypes collisionType, btCollisionShape* pCollisionShape, btRigidBody* pRigidBody, btTriangleMesh* pTriangleMeshes);
	
	// �f�X�g���N�^
	~RigidBody();

	// �]���s����擾 ���X�P�[�����O�Ȃ�
	void Get_TransMatrix(Matrix& mat);

	// �L�l�}�e�B�b�N�I�u�W�F�N�g�𓮂���
	bool TransformKinematicObject(const Vector3& pos, const Vector3& angle);

};

class iexMesh;
class BulletDebugDrawer;
//*****************************************************************
//          BulletSystem�N���X
//*****************************************************************
class BulletSystem : public cSingleton<BulletSystem>
{
	typedef std::unordered_set<RigidBody*> RigidBodyList;
private:
	//-------------------------------------
	//     Singleton �֘A
	//-------------------------------------
	friend cSingleton<BulletSystem>;
	BulletSystem(){}
	~BulletSystem(){}

	// Singleton ������
	bool Initialize()override;

	// Singleton ���
	bool Release()override;

	//-------------------------------------
	//     �����o�ϐ�
	//-------------------------------------
	BulletDebugDrawer*                                     m_pDebugDrawer;
	btDefaultCollisionConfiguration*                   m_pCollisionConfiguration;
	btCollisionDispatcher*                                   m_pDispatcher;
	btBroadphaseInterface*                               m_pOverlappingPairCache;
	btSequentialImpulseConstraintSolver*          m_pSolver;
	btDiscreteDynamicsWorld*                            m_pDyamicsWorld;
	btAlignedObjectArray<btCollisionShape*>    m_pCollisionShapes;
	RigidBodyList                                                  m_RigidBodyList;

public:
	//-------------------------------------
	//     �����o�֐�
	//-------------------------------------

	// Bullet������
	bool InitializeBulletPhysics(const btVector3& gravity, IDirect3DDevice9* pDevice = nullptr);

	// Bullet���
	bool ReleaseBulletPhysics();

	// �����V�~�����[�V������i�߂�
	void StepSimulation(float deltaTime);

	// iexMesh�����[���h�ɔz�u
	RigidBody* AddRigidMesh(
		iexMesh* pMesh,
		float mass,
		RigidBody::CollisionTypes collisionType,
		float friction,
		float restitution,
		const Vector3&velocity,
		const Vector3& localInertia = Vector3(0, 0, 0)
		);

	// Box�����[���h�ɒǉ�
	RigidBody* AddRigidBox(
		float mass, 
		RigidBody::CollisionTypes collisionType, 
		const Vector3& pos, 
		const Vector3& angle, 
		const Vector3& scale, 
		float friction, 
		float restitution,
		const Vector3&velocity
		);

	// Sphere�����[���h�ɒǉ�
	RigidBody* AddRigidSphere(
		float mass,
		RigidBody::CollisionTypes collisionType,
		const Vector3& pos,
		const Vector3& angle,
		float radius,
		float friction,
		float restitution,
		const Vector3& velocity
		);

	// RigidBody�����[���h����폜����
	void RemoveRigidBody(RigidBody* pRigidBody);

	// �f�o�b�O�`��
	void DebugDrawWorld();

};

// BulletSystem
#define DefBulletSystem (BulletSystem::GetInstance())


#if defined(DEBUG)||defined(_DEBUG)

// new �̍Ē�`
#ifndef new

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif

#endif
