#include "yaPlayer.h"
#include "yaInput.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaMeshRenderer.h"
#include "yaPlayerScript.h"
#include "yaResources.h"
#include "yaRigidbody.h"
#include "yaCollider.h"

namespace ya
{
	Player::Player()
		: HP(100)
	{
		AddComponent<Transform>();
		AddComponent<Rigidbody>();
		AddComponent<Collider>();
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		GameObject::Initialize();
	}
	void Player::Update()
	{
		GameObject::Update();
	}
	void Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Player::Render()
	{
		GameObject::Render();
	}
	void Player::OnCollisionEnter(Collider* other)
	{
		int a = 0;
		HP -= 10;
	}
	void Player::OnCollisionStay(Collider* other)
	{
		int a = 0;
	}
	void Player::OnCollisionExit(Collider* other)
	{
		int a = 0;
	}
}
