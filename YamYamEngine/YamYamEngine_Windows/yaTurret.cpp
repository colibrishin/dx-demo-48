#include "yaTurret.h"
#include "yaTransform.h"
#include "yaRigidbody.h"
#include "yaCollider.h"

namespace ya
{
	Turret::Turret()
		: mState(eState::Idle)
	{
		AddComponent<Transform>();
		AddComponent<Rigidbody>();
		AddComponent<Collider>();
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

		switch (mState)
		{
		case ya::Turret::eState::Idle:
			Idle();
			break;
		case ya::Turret::eState::Grabbed:
			Grabbed();
			break;
		case ya::Turret::eState::Distroy:
			Distroy();
			break;
		case ya::Turret::eState::End:
			break;
		default:
			break;
		}
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
	void Turret::Idle()
	{
	}
	void Turret::Grabbed()
	{
	}
	void Turret::Distroy()
	{
	}
}