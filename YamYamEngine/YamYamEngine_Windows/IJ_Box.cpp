#include "IJ_Box.h"
#include "IJ_BoxScript.h"
#include "yaTransform.h"
#include "yaRigidbody.h"
#include "yaCollider.h"


namespace IJ
{
	GO_Box::GO_Box()
		: e_Current_Box_State(Idle)
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
		AddComponent<IJ::BoxScript>();

		ya::GameObject::Initialize();
	}

	void GO_Box::Update()
	{
		ya::GameObject::Update();
	}

	void GO_Box::LateUpdate()
	{
		ya::GameObject::LateUpdate();
	}

	void GO_Box::Render()
	{
		ya::GameObject::Render();
	}

	void GO_Box::OnCollisionEnter(Collider* other)
	{
	}

	void GO_Box::OnCollisionStay(Collider* other)
	{
	}

	void GO_Box::OnCollisionExit(Collider* other)
	{
	}
}