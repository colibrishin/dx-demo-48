#include "yaTurret.h"

namespace ya
{
	Turret::Turret()
	{
	}
	Turret::~Turret()
	{
	}
	void Turret::Initialize()
	{
		GameObject::Initialize();
	}
	void Turret::Update()
	{
		GameObject::Update();
	}
	void Turret::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Turret::Render()
	{
		GameObject::Render();
	}
	void Turret::OnCollisionEnter(Collider* other)
	{
	}
	void Turret::OnCollisionStay(Collider* other)
	{
	}
	void Turret::OnCollisionExit(Collider* other)
	{
	}
}