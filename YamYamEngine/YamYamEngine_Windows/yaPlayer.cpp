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
		//jumptime(0.f),
		mState(eState::Idle)
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

		rb = GetComponent<Rigidbody>();
		rb->SetGround(true);
		
		
	}
	void Player::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case ya::Player::eState::Live:
			Live();
			break;

		case ya::Player::eState::Idle:
			Idle();
			break;

		case ya::Player::eState::Jump:
			Jump();
			break;

		case ya::Player::eState::Fall:
			Fall();
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
		// �Ѿ� �浹 ��
		if (other->GetOwner()->GetLayer() == LAYER::ATTACK || other->GetOwner()->GetLayer() == LAYER::MONSTER)
		{
			mState = eState::Hit;
		}

		// ��Ż �浹 �� 
		else if (other->GetOwner()->GetLayer() == LAYER::PORTAL)
		{
			
		}

		else if (other->GetOwner()->GetLayer() == LAYER::TILE)
		{
			
		}

		else if (other->GetOwner()->GetLayer() == LAYER::ITEM)
		{

		}

	}
	void Player::OnCollisionStay(Collider* other)
	{
	
	}
	void Player::OnCollisionExit(Collider* other)
	{
	
	}
	void Player::Idle()
	{
		// ����
		if (Input::GetKeyDown(eKeyCode::W))
		{
			mState = eState::Jump;
		}
	}
	void Player::Live()
	{
	}
	void Player::Jump()
	{
		//jumptime += Time::DeltaTime();
		Transform* tr = GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		Vector3 velocity = rb->GetVelocity();
		velocity.y = +100.0f;
		rb->SetVelocity(velocity);
		rb->SetGround(false);

		tr->SetPosition(pos);

		if (Input::GetKeyUp(eKeyCode::W))
		{
			mState = eState::Fall;
		}
		
	}
	void Player::Fall()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		pos.y = -100.0f;
		//rb->SetGround(true);

		tr->SetPosition(pos);

		mState = eState::Idle;
	}
	void Player::Hit()
	{
		if(HP != 0)
		{
			HP -= 20;
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
