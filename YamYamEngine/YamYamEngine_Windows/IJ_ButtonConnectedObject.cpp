#include "IJ_ButtonConnectedObject.h"


namespace IJ
{
	ButtonConnectedObject::ButtonConnectedObject()
		: m_Current_BCO_State(eBCOState::Disabled)
	{
	}

	ButtonConnectedObject::~ButtonConnectedObject()
	{
	}

	void ButtonConnectedObject::Initialize()
	{
		ya::GameObject::Initialize();
	}

	void ButtonConnectedObject::Update()
	{
		ya::GameObject::Update();
	}

	void ButtonConnectedObject::LateUpdate()
	{
		ya::GameObject::LateUpdate();
	}

	void ButtonConnectedObject::Render()
	{
		ya::GameObject::Render();
	}

	void ButtonConnectedObject::OnCollisionEnter(ya::Collider* other)
	{
		ya::GameObject::OnCollisionEnter(other);
	}

	void ButtonConnectedObject::OnCollisionStay(ya::Collider* other)
	{
		ya::GameObject::OnCollisionStay(other);
	}

	void ButtonConnectedObject::OnCollisionExit(ya::Collider* other)
	{
		ya::GameObject::OnCollisionExit(other);
	}
}
