#include "yaBullet.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaMeshRenderer.h"

namespace ya
{
	Bullet::Bullet()
	{
	}
	Bullet::~Bullet()
	{
	}
	void Bullet::Initialize()
	{
		GameObject::Initialize();
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
}