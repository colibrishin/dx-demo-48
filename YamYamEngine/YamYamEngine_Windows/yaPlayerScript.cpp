#include "yaPlayerScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaRigidbody.h"

namespace ya
{

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

		//Player 이동
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

		}
		if (Input::GetKeyDown(eKeyCode::RBTN))
		{

		}

		//상호작용
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{

		}
	}

	void PlayerScript::LateUpdate()
	{
	}

	void PlayerScript::Render()
	{
	}

}
