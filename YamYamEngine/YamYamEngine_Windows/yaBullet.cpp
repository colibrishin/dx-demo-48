#include "yaBullet.h"

#include "yaBulletScript.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"
#include "yaSceneManager.h"

namespace ya
{
	Bullet::Bullet()
		: mBulletPos(Vector3::Zero)
		, mPlayerPos(Vector3::Zero)
		, mOrbit(Vector3::Zero)
		, playerSC{ nullptr }
	{
	}
	Bullet::~Bullet()
	{
	}
	void Bullet::Initialize()
	{
		GameObject::Initialize();

		mPlayerPos = playerSC->GetPosition();
		mBulletPos = AddComponent<Transform>()->GetPosition();

		mOrbit = { (mPlayerPos.x - mBulletPos.x), (mPlayerPos.y - mBulletPos.y), 1.0f };
		mOrbit.normalize();
	}
	void Bullet::Update()
	{
		GameObject::Update();
	}
	void Bullet::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Bullet::Render()
	{
		GameObject::Render();
	}
	void Bullet::OnCollisionEnter(Collider* other)
	{
	}
	void Bullet::OnCollisionStay(Collider* other)
	{
	}
	void Bullet::OnCollisionExit(Collider* other)
	{
	}

	void Bullet::InstantiateBullet(Transform* tr)
	{
		Bullet* bullet = new Bullet();
		bullet->Initialize();

		Transform* bullettr = bullet->AddComponent<Transform>();
		bullettr->SetPosition(tr->GetPosition());
		bullettr->SetScale(Vector3(0.5f, 0.5f, 1.0f));
		bullet->AddComponent<BulletScript>();

		MeshRenderer* bulletmr = bullet->AddComponent<MeshRenderer>();
		bulletmr->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
		bulletmr->SetShader(Resources::Find<Shader>(L"ColorShader"));

		SceneManager::GetActiveScene()->AddGameObject(bullet, LAYER::TURRET);
	}
}
