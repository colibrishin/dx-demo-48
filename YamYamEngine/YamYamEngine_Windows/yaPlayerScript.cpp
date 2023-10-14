#include "yaPlayerScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaPlayer.h"
#include "yaRigidbody.h"

namespace ya
{
	Vector3 PlayerScript::mPlayerPos = Vector3::Zero;

	PlayerScript::PlayerScript()
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
	}

	void PlayerScript::Update()
	{
		GameObject* obj = GetOwner();
		Transform* tr = obj->GetComponent<Transform>();
		Rigidbody* rb = obj->GetComponent<Rigidbody>();

		//Player �̵�
		if (Input::GetKey(eKeyCode::W))
		{
			const auto velocity = rb->GetVelocity();
			rb->SetVelocity({velocity.x, 1.0f, velocity.z});
		}
		if (Input::GetKey(eKeyCode::A))
		{
			const auto velocity = rb->GetVelocity();
			rb->SetVelocity({-1.0f, velocity.y, velocity.z});
		}
		if (Input::GetKey(eKeyCode::S))
		{
			const auto velocity = rb->GetVelocity();
			rb->SetVelocity({velocity.x, -1.0f, velocity.z});
		}
		if (Input::GetKey(eKeyCode::D))
		{
			const auto velocity = rb->GetVelocity();
			rb->SetVelocity({1.0f, velocity.y, velocity.z});
		}

		//Mouse
		if (Input::GetKeyDown(eKeyCode::LBTN))
		{
			dynamic_cast<Player*>(obj)->SetState(Player::eState::MeleeAttack);
		}

		if (Input::GetKeyDown(eKeyCode::RBTN))
		{
			dynamic_cast<Player*>(obj)->SetState(Player::eState::RangeAttack);
		}

		if (Input::GetKeyDown(eKeyCode::N_1))
		{
			dynamic_cast<Player*>(obj)->SetPlayerAs(Player::ePlayerAs::Self);
		}
		else if(Input::GetKeyDown(eKeyCode::N_2))
		{
			dynamic_cast<Player*>(obj)->SetPlayerAs(Player::ePlayerAs::Shadow);
		}

		//��ȣ�ۿ�
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{

		}

		mPlayerPos = tr->GetPosition();
	}

	void PlayerScript::LateUpdate()
	{
	}

	void PlayerScript::Render()
	{
	}

}
