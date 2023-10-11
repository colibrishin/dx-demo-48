#include "yaCollider.h"
#include "yaGameObject.h"
#include "yaScene.h"
#include "yaSceneManager.h"

//충돌을 하기 위한 하나의 도형
namespace ya
{
	Collider::Collider()
		:Component(COMPONENTTYPE::COLLIDER)
		, mSize(Vector3::Zero)
		, mOffset(Vector2::Zero)
		, mRotation()
		, mbIsCollision(false)
	{

		
	}

	Collider::~Collider()
	{
	}

	void Collider::Initialize()
	{
		UpdatePosition();
	}

	void Collider::Update()
	{
		UpdatePosition();
	}

	void Collider::LateUpdate()
	{
	}

	void Collider::Render()
	{
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		if(!IsEnabled())
		{
			return;
		}

		GetOwner()->OnCollisionEnter(other);
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		if(!IsEnabled())
		{
			return;
		}

		GetOwner()->OnCollisionStay(other);
	}
	void Collider::OnCollisionExit(Collider* other)		// 막 빠져나갔을 때(충돌 X)
	{
		if(!IsEnabled())
		{
			return;
		}

		GetOwner()->OnCollisionExit(other);
	}

	void Collider::ColliderOff()
	{

	}

	void Collider::UpdatePosition()
	{
		auto* tr = GetOwner()->GetComponent<Transform>();

		if(tr != nullptr)
		{
			SetPosition(tr->GetPosition());
			SetSize(tr->GetScale());
		}
	}
}
