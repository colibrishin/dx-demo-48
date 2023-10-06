#include "IJ_PlayerAim_Temp.h"
#include "yaTransform.h"
#include "yaCollider.h"

#include "yaInput.h"

namespace IJ
{
	PlayerAim_Temp::PlayerAim_Temp()
		: m_Owner_Player(nullptr)
		, Boxes_In_Collision({})
		, m_Box_Grabbing(nullptr)
	{
		Boxes_In_Collision.reserve(10);
	}

	PlayerAim_Temp::~PlayerAim_Temp()
	{
	}

	void PlayerAim_Temp::Initialize()
	{
		AddComponent<ya::Transform>();
		AddComponent<ya::Collider>();

		ya::GameObject::Initialize();
	}

	void PlayerAim_Temp::Update()
	{
		ya::GameObject::Update();

		// space를 누르면 가장 가까운 상자를 집습니다
		// 이미 상자를 들고있다면 놓습니다
		// 가장 가까운 거 구하기는 나중에 구현 예정
		GO_Box* m_Most_Close_Box = nullptr;

		if (ya::Input::GetKeyDown(ya::eKeyCode::SPACE))
		{
			// 아무것도 들고있지 않은 상태라면
			if (m_Box_Grabbing == nullptr)
			{
				// 근처에 상자가 없다면 집지 않습니다
				if (m_Most_Close_Box != nullptr)
				{
					m_Box_Grabbing = m_Most_Close_Box;
					m_Box_Grabbing->SetBoxState(GO_Box::eBoxState::Grabbed);
					m_Box_Grabbing->SetGrabber(m_Owner_Player);
				}
			}
			// 이미 박스를 들고있으면
			else
			{
				m_Most_Close_Box->SetBoxState(GO_Box::eBoxState::Idle);
			}
		}
	}

	void PlayerAim_Temp::LateUpdate()
	{
		ya::GameObject::LateUpdate();
	}

	void PlayerAim_Temp::Render()
	{
		ya::GameObject::Render();
	}

	void PlayerAim_Temp::OnCollisionEnter(ya::Collider* other)
	{
		ya::GameObject* other_GO = other->GetOwner();
		GO_Box* other_Box = dynamic_cast<GO_Box*>(other_GO);

		Boxes_In_Collision.push_back(other_Box);
	}

	void PlayerAim_Temp::OnCollisionStay(ya::Collider* other)
	{
	}

	void PlayerAim_Temp::OnCollisionExit(ya::Collider* other)
	{
		ya::GameObject* other_GO = other->GetOwner();
		GO_Box* other_Box = dynamic_cast<GO_Box*>(other_GO);

		for (size_t i = 0; i < Boxes_In_Collision.size(); i++)
		{
			if (Boxes_In_Collision[i] == other_Box)
				Boxes_In_Collision.erase(Boxes_In_Collision.begin() + i);
		}
	}
}