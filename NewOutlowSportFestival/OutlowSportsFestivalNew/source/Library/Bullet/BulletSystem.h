#pragma once

//*****************************************************************
//          BulletSystem.h
//          IEX と連携して使えるようにしてあります
//          なんで Bullet Physics は右手系なんだ...
//*****************************************************************

// Bulletで new がオーバーロードされているため
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
//          RigidBodyクラス
//*****************************************************************
struct RigidBody
{
	// コリジョンタイプ
	enum CollisionTypes
	{
		ct_nothing = 0,                // Nothing
		ct_dynamic = (1 << 1),   // 動的オブジェクト
		ct_static = (1 << 2),        // 静的オブジェクト
		ct_kinematic = (1 << 3), // キネマティックオブジェクト
	};

	CollisionTypes        collisionType;       // コリジョンタイプ
	btCollisionShape*  pCollisionShape;  // CollisionShape
	btRigidBody*         pRigidBody;         // RigidBody
	btTriangleMesh*    pTriangleMeshes; // TriangleMeshes ※配列として扱う

	// コンストラクタ
	RigidBody();
	RigidBody(CollisionTypes collisionType, btCollisionShape* pCollisionShape, btRigidBody* pRigidBody);
	RigidBody(CollisionTypes collisionType, btCollisionShape* pCollisionShape, btRigidBody* pRigidBody, btTriangleMesh* pTriangleMeshes);
	
	// デストラクタ
	~RigidBody();

	// 転送行列を取得 ※スケーリングなし
	void Get_TransMatrix(Matrix& mat);

	// キネマティックオブジェクトを動かす
	bool TransformKinematicObject(const Vector3& pos, const Vector3& angle);

};

class iexMesh;
class BulletDebugDrawer;
//*****************************************************************
//          BulletSystemクラス
//*****************************************************************
class BulletSystem : public cSingleton<BulletSystem>
{
	typedef std::unordered_set<RigidBody*> RigidBodyList;
private:
	//-------------------------------------
	//     Singleton 関連
	//-------------------------------------
	friend cSingleton<BulletSystem>;
	BulletSystem(){}
	~BulletSystem(){}

	// Singleton 初期化
	bool Initialize()override;

	// Singleton 解放
	bool Release()override;

	//-------------------------------------
	//     メンバ変数
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
	//     メンバ関数
	//-------------------------------------

	// Bullet初期化
	bool InitializeBulletPhysics(const btVector3& gravity, IDirect3DDevice9* pDevice = nullptr);

	// Bullet解放
	bool ReleaseBulletPhysics();

	// 物理シミュレーションを進める
	void StepSimulation(float deltaTime);

	// iexMeshをワールドに配置
	RigidBody* AddRigidMesh(
		iexMesh* pMesh,
		float mass,
		RigidBody::CollisionTypes collisionType,
		float friction,
		float restitution,
		const Vector3&velocity,
		const Vector3& localInertia = Vector3(0, 0, 0)
		);

	// Boxをワールドに追加
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

	// Sphereをワールドに追加
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

	// RigidBodyをワールドから削除する
	void RemoveRigidBody(RigidBody* pRigidBody);

	// デバッグ描画
	void DebugDrawWorld();

};

// BulletSystem
#define DefBulletSystem (BulletSystem::GetInstance())


#if defined(DEBUG)||defined(_DEBUG)

// new の再定義
#ifndef new

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif

#endif
