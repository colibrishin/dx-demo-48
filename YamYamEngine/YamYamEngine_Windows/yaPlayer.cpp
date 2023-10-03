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
		: HP(100),
		mState(eState::Live)
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

		switch (mState)
		{
		case ya::Player::eState::Live:
			Live();
			break;
		case ya::Player::eState::Hit:
			Hit();
			break;
		case ya::Player::eState::Dead:
			Dead();
			break;

		case ya::Player::eState::End:
			break;
		default:
			break;
		}
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
		// �Ѿ˰� �浹�ϸ�
		if (other->GetOwner()->GetLayer() == LAYER::ATTACK)
		{
			mState = eState::Hit;
		}
	}
	void Player::OnCollisionStay(Collider* other)
	{
	
	}
	void Player::OnCollisionExit(Collider* other)
	{
	
	}
	void Player::Live()
	{
	}
	void Player::Hit()
	{
	}
	void Player::Dead()
	{
	}
}
