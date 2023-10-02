#include "IJ_BoxScript.h"
#include "IJ_Box.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaRigidbody.h"
#include "yaTime.h"

#include "yaPlayer.h"


namespace IJ
{
	BoxScript::BoxScript()
	{
	}

	BoxScript::~BoxScript()
	{
	}

	void BoxScript::Initialize()
	{
	}

	void BoxScript::Update()
	{
		ya::GameObject* gameobject = GetOwner();
		GO_Box* box = dynamic_cast<GO_Box*>(gameobject);

		if (box != nullptr)
		{
			GO_Box::eBoxState e_Box_State;
			e_Box_State = box->GetBoxState();

			switch (e_Box_State)
			{
			case GO_Box::Idle:
				Idle();
				break;
			case GO_Box::Grabbed:
				Grabbed();
				break;
			case GO_Box::END:
				break;
			default:
				break;
			}
		}
	}

	void BoxScript::LateUpdate()
	{
	}

	void BoxScript::Render()
	{
	}

	void BoxScript::Idle()
	{
		// 보통 상태일 때엔 기본적으로 아무것도 안하기
	}

	void BoxScript::Grabbed()
	{
		ya::GameObject* m_Owner = GetOwner();
		GO_Box* m_Owner_Box = dynamic_cast<GO_Box*>(m_Owner);

		// 무언가가 나를 잡았다면
		ya::GameObject* m_Grabber = m_Owner_Box->GetGrabber();
		ya::Player* m_Grabber_Player = dynamic_cast<ya::Player*>(m_Grabber);

		// 아무도 나를 잡지 않았는데 이 상태에 들어왔다면 idle로 돌아감
		if (m_Grabber == nullptr)
			m_Owner_Box->SetBoxState(GO_Box::eBoxState::Idle);

		if (m_Grabber_Player != nullptr)
		{
			ya::Rigidbody* rigidbody = m_Owner->GetComponent<ya::Rigidbody>();

			// 상자와 플레이어와의 거리 구하기
			ya::Transform* tr_Box = m_Owner->GetComponent<ya::Transform>();
			ya::Vector3 pos_Box = tr_Box->GetPosition();
			ya::Transform* tr_Player = m_Grabber->GetComponent<ya::Transform>();
			ya::Vector3 pos_Player = tr_Player->GetPosition();

			//float m_Distance = sqrtf(powf(pos_Box.x - pos_Player.x, 2) +
			//					powf(pos_Box.y - pos_Player.y, 2));
			float m_Distance = ya::Vector3::DistanceSquared(pos_Box, pos_Player);

			// 나중에 구현 예정
			// 무언가에 끼어서 움직이지 못해 나를 잡은 플레이어와 거리가 멀어지면 idle로 돌아감
			//if (m_Distance > 0.5f)
			//{
			//	m_Owner_Box->SetGrabber(nullptr);
			//}

			// 평상시엔 플레이어 옆으로 이동하게 하려고 했지만
			// 임시로 플레이어 바로 위로 이동하게 했습니다
			ya::Vector3 pos_Target = { pos_Player.x, pos_Player.y + 0.1f, pos_Player.z };
			ya::Vector3 m_Direction = pos_Target - pos_Box;
			m_Direction.normalize();
			ya::Vector2 m_Direction_2 = { m_Direction.x, m_Direction.y };
			rigidbody->AddForce(m_Direction_2 * 1.0f * ya::Time::DeltaTime());

			// 또한 중력을 상쇄하기 위해 중력의 크기만큼 위로 힘을 받습니다
			// 일단은 기본값인 800.0f 만큼만 힘을 줍니다
			rigidbody->AddForce({ 0.0f, -800.0f * ya::Time::DeltaTime()});
		}
	}
}