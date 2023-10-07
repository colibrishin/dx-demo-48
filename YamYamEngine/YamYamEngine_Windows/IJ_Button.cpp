#include "IJ_Button.h"
#include "yaCollider.h"
#include "IJ_ButtonConnectedObject.h"


namespace IJ
{
	GO_Button::GO_Button()
		: m_Button_Type(eButtonType::Hold)
		, m_Current_Button_State(eButtonState::Idle)
		, Connected_GameObjects({})
	{
		Connected_GameObjects.reserve(5);
	}

	GO_Button::~GO_Button()
	{
	}

	void GO_Button::Initialize()
	{
		ya::GameObject::Initialize();
	}

	void GO_Button::Update()
	{
		ya::GameObject::Update();
	}

	void GO_Button::LateUpdate()
	{
		ya::GameObject::LateUpdate();
	}

	void GO_Button::Render()
	{
		ya::GameObject::Render();
	}

	void GO_Button::OnCollisionEnter(ya::Collider* other)
	{
		ya::GameObject::OnCollisionEnter(other);

		// 아무 물체에나 닿기만 한다면
		SetButtonState(eButtonState::Pressing);
		for (GameObject* go : GO_Button::Connected_GameObjects)
		{
			ButtonConnectedObject* bco = dynamic_cast<ButtonConnectedObject*>(go);
			if (bco == nullptr)
				continue;

			// 홀드 타입이라면 닿고 있는 동안에만 활성화
			if (m_Button_Type == eButtonType::Hold)
				bco->SetBCOState(ButtonConnectedObject::eBCOState::Activated);
			// 토글 타입이라면 닿을 때마다 활성화와 비활성화를 변경
			else if (m_Button_Type == eButtonType::Toggle)
			{
				ButtonConnectedObject::eBCOState bcostate = bco->GetBCOState();
				if (bcostate == ButtonConnectedObject::eBCOState::Activated)
					bco->SetBCOState(ButtonConnectedObject::eBCOState::Disabled);
				else if (bcostate == ButtonConnectedObject::eBCOState::Disabled)
					bco->SetBCOState(ButtonConnectedObject::eBCOState::Activated);
			}
			// 원스 타입이라면 한번만 반응
			else if (m_Button_Type == eButtonType::Once)
				bco->SetBCOState(ButtonConnectedObject::eBCOState::Activated);
		}
	}

	void GO_Button::OnCollisionStay(ya::Collider* other)
	{
		ya::GameObject::OnCollisionStay(other);
	}

	void GO_Button::OnCollisionExit(ya::Collider* other)
	{
		ya::GameObject::OnCollisionExit(other);

		// 이렇게 하면 두개이상의 물체와 닿는 중에 하나가 빠져나가면
		// 나머지 물체가 닿고있는 중임에도 홀드가 풀리는 문제가 발생할 것
		// 수정이 필요할 듯
		SetButtonState(eButtonState::Idle);
		for (GameObject* go : GO_Button::Connected_GameObjects)
		{
			ButtonConnectedObject* bco = dynamic_cast<ButtonConnectedObject*>(go);
			if (bco == nullptr)
				continue;

			if (m_Button_Type == eButtonType::Hold)
				bco->SetBCOState(ButtonConnectedObject::eBCOState::Disabled);
		}
	}
}