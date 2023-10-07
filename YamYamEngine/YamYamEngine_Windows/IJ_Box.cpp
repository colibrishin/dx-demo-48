#include "IJ_Box.h"
#include "yaTransform.h"
#include "yaRigidbody.h"
#include "yaCollider.h"

#include "yaTime.h"


namespace IJ
{
	GO_Box::GO_Box()
		: e_Current_Box_State(eBoxState::IDLE)
		, m_Grabber(nullptr)
	{
	}

	GO_Box::~GO_Box()
	{
	}

	void GO_Box::Initialize()
	{
		AddComponent<ya::Transform>();
		AddComponent<ya::Rigidbody>();
		AddComponent<ya::Collider>();

		ya::GameObject::Initialize();
	}

	void GO_Box::Update()
	{
		ya::GameObject::Update();

		switch (e_Current_Box_State)
		{
		case eBoxState::IDLE:
			Idle();
			break;
		case eBoxState::GRABBED:
			Grabbed();
			break;
		case eBoxState::END:
			break;
		default:
			break;
		}
	}

	void GO_Box::LateUpdate()
	{
		ya::GameObject::LateUpdate();
	}

	void GO_Box::Render()
	{
		ya::GameObject::Render();
	}

	void GO_Box::OnCollisionEnter(ya::Collider* other)
	{
		ya::GameObject::OnCollisionEnter(other);
	}

	void GO_Box::OnCollisionStay(ya::Collider* other)
	{
		ya::GameObject::OnCollisionStay(other);
	}

	void GO_Box::OnCollisionExit(ya::Collider* other)
	{
		ya::GameObject::OnCollisionExit(other);
	}

	void GO_Box::Idle()
	{
		// 보통 상태일 때엔 기본적으로 아무것도 안하기
	}

	void GO_Box::Grabbed()
	{
		// 아무도 나를 잡지 않았는데 이 상태에 들어왔다면 idle로 돌아감
		if (m_Grabber == nullptr)
		{
			SetBoxState(eBoxState::IDLE);
			return;
		}

		ya::Rigidbody* rigidbody_Box = GetComponent<ya::Rigidbody>();

		// 상자와 플레이어와의 거리 구하기
		ya::Transform* tr_Box = GetComponent<ya::Transform>();
		ya::Vector3 pos_Box = tr_Box->GetPosition();
		ya::Transform* tr_Player = m_Grabber->GetComponent<ya::Transform>();
		ya::Vector3 pos_Player = tr_Player->GetPosition();

		float m_Distance = ya::Vector3::DistanceSquared(pos_Box, pos_Player);

		// 나중에 구현 예정
		// 무언가에 끼어서 움직이지 못해 나를 잡은 플레이어와 거리가 멀어지면 idle로 돌아감
		//if (m_Distance > 0.5f)
		//{
		//	SetGrabber(nullptr);
		//}

		// 평상시엔 플레이어 옆으로 이동하게 하려고 했지만
		// 임시로 플레이어 바로 위로 이동하게 했습니다
		ya::Vector3 pos_Target = { pos_Player.x, pos_Player.y + 0.1f, pos_Player.z };
		ya::Vector3 m_Direction = pos_Target - pos_Box;
		m_Direction.normalize();
		rigidbody_Box->AddForce(m_Direction * 1.0f * ya::Time::DeltaTime());

		// 또한 중력을 상쇄하기 위해 중력의 반대 크기만큼 힘을 받습니다
		ya::Vector3 gravity_Box = rigidbody_Box->GetGravity();
		rigidbody_Box->AddForce(-gravity_Box * ya::Time::DeltaTime());
	}
}