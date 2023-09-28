#include "yaCollider.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaScene.h"
#include "yaSceneManager.h"

//충돌을 하기 위한 하나의 도형
namespace ya
{
	Collider::Collider()
		:Component(COMPONENTTYPE::COLLIDER)
		, mSize(Vector2::Zero)
		, mOffset(Vector2::Zero)
		, mbIsCollision(false)
	{
	}

	Collider::~Collider()
	{
	}

	void Collider::Initialize()
	{
	}

	void Collider::Update()
	{
	}

	void Collider::Render()
	{
		
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		mbIsCollision = true;
		GetOwner()->OnCollisionEnter(other);
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}
	void Collider::OnCollisionExit(Collider* other)		// 막 빠져나갔을 때(충돌 X)
	{
		mbIsCollision = false;
		GetOwner()->OnCollisionExit(other);
	}

	void Collider::ColliderOff()
	{

	}
}
