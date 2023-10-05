#include "yaPlayer.h"
#include "yaInput.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaMeshRenderer.h"
#include "yaPlayerScript.h"
#include "yaResources.h"
#include "yaRigidbody.h"
#include "yaCollider.h"
#include "yaRigidbody.h"

namespace ya
{
	Player::Player()
		: HP(100),
		jumptime(0.f),
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

		rb = this->GetComponent<Rigidbody>();
		
	}
	void Player::Update()
	{
		GameObject::Update();

		// Á¡ÇÁ
		if (Input::GetKeyDown(eKeyCode::LCTRL))
		{
			mState = eState::Jump;
		}



		switch (mState)
		{
		case ya::Player::eState::Live:
			Live();
			break;

		case ya::Player::eState::Jump:
			Jump();
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
		// ï¿½Ñ¾Ë°ï¿½ ï¿½æµ¹ï¿½Ï¸ï¿½
		if (other->GetOwner()->GetLayer() == LAYER::ATTACK)
		{
			mState = eState::Hit;
		}

		// Æ÷Å» Ãæµ¹ ½Ã Ã³¸®
		if (other->GetOwner()->GetLayer() == LAYER::PORTAL)
		{
			
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
	void Player::Jump()
	{
		//jumptime += Time::DeltaTime();

		// if(jumptime < )
		Transform* tr = GetComponent<Transform>();
		Vector3 position = tr->GetPosition();
		
		Vector3 velocity = rb->GetVelocity();
		velocity.y = -500.0f;
		rb->SetVelocity(velocity);
		rb->SetGround(false);

		//jumptime = 0.f;
	}
	void Player::Hit()
	{
		if(HP != 0)
		{
			HP -= 10;
		}
		else
		{
			mState = eState::Dead;
		}
	}
	void Player::Dead()
	{
		Destroy(this);
	}
}
