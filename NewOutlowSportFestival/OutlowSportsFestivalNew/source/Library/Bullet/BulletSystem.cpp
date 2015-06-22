


#include "BulletSystem.h"
#include "BulletDebug.h"

#include "../../utillity/SafeMethod.h"
#include <memory>

// Bulletで new がオーバーロードされているため
#if defined new
#undef new
#endif


//*****************************************************************
//          RigidBodyクラス
//*****************************************************************

// コンストラクタ
RigidBody::RigidBody() :
collisionType(ct_nothing),
pCollisionShape(nullptr),
pRigidBody(nullptr),
pTriangleMeshes(nullptr)
{
}


// コンストラクタ
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


// コンストラクタ
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


// デストラクタ
RigidBody::~RigidBody()
{
	safe_delete(pCollisionShape);
	safe_delete(pRigidBody);
	safe_array_delete(pTriangleMeshes);
}


// キネマティックオブジェクトを動かす
bool RigidBody::TransformKinematicObject(const Vector3& pos, const Vector3& angle)
{
	if (collisionType != ct_kinematic)
	{// キネマティックオブジェクト以外は動かせない
		return false;
	}

	btTransform transform;
	transform.setIdentity();

	// 座標設定
	transform.setOrigin(btVector3(pos.x, pos.y, pos.z));

	// 回転設定
	// x軸を反転して右手系になってるの？ ※怪しい...
	transform.setRotation(btQuaternion(-angle.x, angle.y, angle.z));

	// 適応
	pRigidBody->getMotionState()->setWorldTransform(transform);

	return true;
}



//*****************************************************************
//          BulletSystemクラス
//*****************************************************************
//-------------------------------------
//     Singleton 関連
//-------------------------------------

// Singleton 初期化
bool BulletSystem::Initialize()
{
	return true;
}


// Singleton 解放
bool BulletSystem::Release()
{
	return true;
}


//-------------------------------------
//     メンバ関数
//-------------------------------------

// Bullet初期化
bool BulletSystem::InitializeBulletPhysics(const btVector3& gravity, IDirect3DDevice9* pDevice)
{
	// 衝突検出方法の選択(デフォルトを選択)
	m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
	m_pDispatcher = new btCollisionDispatcher(
		m_pCollisionConfiguration
		);

	// ブロードフェーズ法の設定(Dynamic AABB tree method)
	m_pOverlappingPairCache = new btDbvtBroadphase();

	// 拘束(剛体間リンク)のソルバ設定
	m_pSolver = new btSequentialImpulseConstraintSolver();

	// ワールド生成
	m_pDyamicsWorld = new btDiscreteDynamicsWorld(
		m_pDispatcher, 
		m_pOverlappingPairCache, 
		m_pSolver, 
		m_pCollisionConfiguration
		);

	// 重力設定
	m_pDyamicsWorld->setGravity(gravity);

	
	if (pDevice != nullptr)
	{// デバッグ描画クラス設定
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


// Bullet解放
bool BulletSystem::ReleaseBulletPhysics()
{
	// リストの中身を解放
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


// 物理シミュレーションを進める
void BulletSystem::StepSimulation(float deltaTime)
{
	m_pDyamicsWorld->stepSimulation(deltaTime, 1, deltaTime);
}


// iexMeshをワールドに静的オブジェクトとして配置
RigidBody* BulletSystem::AddRigidMesh(
	iexMesh* pMesh,
	float m,
	RigidBody::CollisionTypes collisionType,
	float friction,
	float restitution,
	const Vector3&velocity
	)
{
	// メッシュ取得
	LPD3DXMESH mesh = pMesh->GetMesh();

	//	情報取得	
	u32 fvf = mesh->GetFVF();

	//	頂点サイズ計算
	int VertexSize = D3DXGetFVFVertexSize(fvf) / sizeof(float);

	// ポリゴン数取得
	u32 NumIndices = mesh->GetNumFaces();

	
	float	*pVertices; // 頂点
	u16 *pIndices;   // インデックス

	//	バッファロック
	mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertices);
	mesh->LockIndexBuffer(D3DLOCK_READONLY, (void**)&pIndices);

	// 三角形リストで剛体を生成する
	btTriangleMesh* pbtTriangleMesh = new btTriangleMesh();
	Vector3 scale = pMesh->GetScale();

	// 三角形の頂点
	Vector3 v1, v2, v3;

	for (u32 i = 0; i < NumIndices; i++)
	{
		//	面頂点取得
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

	// バッファアンロック
	mesh->UnlockVertexBuffer();
	mesh->UnlockIndexBuffer();

	//三角形メッシュでシェイプを作成
	btBvhTriangleMeshShape* pbtShape = new btBvhTriangleMeshShape(pbtTriangleMesh, true);

	// 静的オブジェクトなので質量0
	btScalar mass(m);

	btTransform transform;
	transform.setIdentity();

	// 座標設定
	Vector3 pos = pMesh->GetPos();
	transform.setOrigin(
		btVector3(pos.x, pos.y, pos.z)
		);

	// 回転設定
	Vector3 angle = pMesh->GetAngle();
	transform.setRotation(
		btQuaternion(-angle.x, angle.y, angle.z)
		);

	// btRigidBody生成
	btCollisionShape* pbtCollisionShape = pbtShape;


	btVector3 localInertia(0, 0, 0);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyInfo(
		mass, 
		new btDefaultMotionState(transform), 
		pbtCollisionShape,
		localInertia
		);

	// 反発係数
	rigidBodyInfo.m_restitution = restitution;

	// 摩擦
	rigidBodyInfo.m_friction = friction;

	btRigidBody* pbtRigidBody = new btRigidBody(rigidBodyInfo);


	int maskType = 0;
	switch (collisionType)
	{
	case RigidBody::ct_dynamic:
		//----------------------------------
		// 動的剛体
		//----------------------------------

		// マスクタイプ設定
		maskType = RigidBody::ct_dynamic | RigidBody::ct_kinematic | RigidBody::ct_static;

		// 移動速度
		pbtRigidBody->setLinearVelocity(
			btVector3(velocity.x, velocity.y, velocity.z)
			);

		// 回転速度
		pbtRigidBody->setAngularVelocity(btVector3(0, 0, 0));
		break;

	case RigidBody::ct_static:
		//----------------------------------
		// 静的剛体
		//----------------------------------

		// マスクタイプ設定
		maskType = RigidBody::ct_dynamic;
		break;


	case RigidBody::ct_kinematic:
		//----------------------------------
		// キネマティック剛体
		//----------------------------------

		// マスクタイプ設定
		maskType = RigidBody::ct_dynamic;

		// キネマティック剛体に設定
		pbtRigidBody->setCollisionFlags(
			pbtRigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT
			);
		pbtRigidBody->setActivationState(DISABLE_DEACTIVATION);
		break;

	default:
		break;
	}

	// ワールドに追加
	m_pDyamicsWorld->addRigidBody(
		pbtRigidBody, 
		(short)collisionType, 
		(short)maskType
		);

	// RigidBodyクラス生成
	RigidBody* pRigidBody = new RigidBody(
		RigidBody::ct_kinematic, 
		pbtCollisionShape,
		pbtRigidBody, 
		pbtTriangleMesh
		);

	// リストに追加
	m_RigidBodyList.insert(pRigidBody);

	return pRigidBody;
}


// Boxをワールドに追加
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
	// 質量
	btScalar mass(m);

	btTransform transform;
	transform.setIdentity();

	// 座標設定
	transform.setOrigin(
		btVector3(pos.x, pos.y, pos.z)
		);

	// 回転設定
	transform.setRotation(
		btQuaternion(-angle.x, angle.y, angle.z)
		);

	// BoxShape生成
	btCollisionShape* pbtCollisionShape = new btBoxShape(
		btVector3(scale.x, scale.y, scale.z)
		);

	// 慣性モーメントの計算
	btVector3 localInertia;
	pbtCollisionShape->calculateLocalInertia(mass, localInertia);

	// btRigidBody生成
	btRigidBody::btRigidBodyConstructionInfo rigidBodyInfo(
		mass,
		new btDefaultMotionState(transform),
		pbtCollisionShape,
		localInertia
		);

	// 反発係数
	rigidBodyInfo.m_restitution = restitution;

	// 摩擦
	rigidBodyInfo.m_friction = friction;

	btRigidBody* pbtRigidBody = new btRigidBody(rigidBodyInfo);


	int maskType = 0;
	switch (collisionType)
	{
	case RigidBody::ct_dynamic:  
		//----------------------------------
		// 動的剛体
		//----------------------------------

		// マスクタイプ設定
		maskType = RigidBody::ct_dynamic | RigidBody::ct_kinematic | RigidBody::ct_static;

		// 移動速度
		pbtRigidBody->setLinearVelocity(
			btVector3(velocity.x, velocity.y, velocity.z)
			);

		// 回転速度
		pbtRigidBody->setAngularVelocity(btVector3(0, 0, 0));
		break;
		
	case RigidBody::ct_static:
		//----------------------------------
		// 静的剛体
		//----------------------------------

		// マスクタイプ設定
		maskType = RigidBody::ct_dynamic;
		break;

		
	case RigidBody::ct_kinematic:
		//----------------------------------
		// キネマティック剛体
		//----------------------------------
		
		// マスクタイプ設定
		maskType = RigidBody::ct_dynamic;

		// キネマティック剛体に設定
		pbtRigidBody->setCollisionFlags(
			pbtRigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT
			);
		pbtRigidBody->setActivationState(DISABLE_DEACTIVATION);
		break;

	default:
		break;
	}

	// ワールドに追加
	m_pDyamicsWorld->addRigidBody(pbtRigidBody, (short)collisionType, (short)maskType);

	// RigidBody生成
	RigidBody* pRigidBody = new RigidBody(
		collisionType,
		pbtCollisionShape,
		pbtRigidBody
		);

	// リストに追加
	m_RigidBodyList.insert(pRigidBody);

	return pRigidBody;
}


// Sphereをワールドに追加
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
	// 質量
	btScalar mass(m);

	btTransform transform;
	transform.setIdentity();

	// 座標設定
	transform.setOrigin(
		btVector3(pos.x, pos.y, pos.z)
		);

	// 回転設定
	transform.setRotation(
		btQuaternion(-angle.x, angle.y, angle.z)
		);

	// BoxShape生成
	btCollisionShape* pbtCollisionShape = new btSphereShape(radius);

	// 慣性モーメントの計算
	btVector3 localInertia;
	pbtCollisionShape->calculateLocalInertia(mass, localInertia);

	// btRigidBody生成
	btRigidBody::btRigidBodyConstructionInfo rigidBodyInfo(
		mass,
		new btDefaultMotionState(transform),
		pbtCollisionShape,
		localInertia
		);

	// 反発係数
	rigidBodyInfo.m_restitution = restitution;

	// 摩擦
	rigidBodyInfo.m_friction = friction;

	btRigidBody* pbtRigidBody = new btRigidBody(rigidBodyInfo);


	int maskType = 0;
	switch (collisionType)
	{
	case RigidBody::ct_dynamic:
		//----------------------------------
		// 動的剛体
		//----------------------------------

		// マスクタイプ設定
		maskType = RigidBody::ct_dynamic | RigidBody::ct_kinematic | RigidBody::ct_static;

		// 移動速度
		pbtRigidBody->setLinearVelocity(
			btVector3(velocity.x, velocity.y, velocity.z)
			);

		// 回転速度
		pbtRigidBody->setAngularVelocity(btVector3(0, 0, 0));
		break;

	case RigidBody::ct_static:
		//----------------------------------
		// 静的剛体
		//----------------------------------

		// コリジョンタイプ設定
		maskType = RigidBody::ct_dynamic;
		break;


	case RigidBody::ct_kinematic:
		//----------------------------------
		// キネマティック剛体
		//----------------------------------

		// コリジョンタイプ設定
		maskType = RigidBody::ct_dynamic;

		// キネマティック剛体に設定
		pbtRigidBody->setCollisionFlags(
			pbtRigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT
			);
		pbtRigidBody->setActivationState(DISABLE_DEACTIVATION);
		break;

	default:
		break;
	}

	// ワールドに追加
	m_pDyamicsWorld->addRigidBody(pbtRigidBody, (short)collisionType, (short)maskType);

	// RigidBody生成
	RigidBody* pRigidBody = new RigidBody(
		collisionType,
		pbtCollisionShape,
		pbtRigidBody
		);

	// リストに追加
	m_RigidBodyList.insert(pRigidBody);

	return pRigidBody;
}


// RigidBodyをワールドから削除する
void BulletSystem::RemoveRigidBody(RigidBody* pRigidBody)
{
	if (!pRigidBody)
	{
		return;
	}

	// 剛体を削除
	m_pDyamicsWorld->removeRigidBody(pRigidBody->pRigidBody);

	delete pRigidBody->pRigidBody->getMotionState();

	m_RigidBodyList.erase(pRigidBody);

	safe_delete(pRigidBody);

}


// デバッグ描画
void BulletSystem::DebugDrawWorld()
{
	m_pDyamicsWorld->debugDrawWorld();
}



// いるのかどうか微妙
#if defined(DEBUG)||defined(_DEBUG)

// new の再定義
#ifndef new

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif

#endif
