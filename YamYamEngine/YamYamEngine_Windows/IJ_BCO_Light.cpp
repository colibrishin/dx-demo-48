#include "yaCollider.h"
#include "IJ_BCO_Light.h"

#include "yaMeshRenderer.h"
#include "yaResources.h"


namespace IJ
{
	BCO_Light::BCO_Light(float light_range) : m_light_range_(light_range)
	{
	}

	void BCO_Light::Initialize()
	{
		ButtonConnectedObject::Initialize();

		const auto tr = AddComponent<ya::Transform>();
		tr->SetScale(1.0f, 1.0f, 1.0f);

		const auto mr = AddComponent<ya::MeshRenderer>();
		mr->SetMesh(ya::Resources::Find<ya::Mesh>(L"CircleMesh"));
		mr->SetShader(ya::Resources::Find<ya::Shader>(L"ColorShader"));
		mr->SetTexture(ya::Resources::Find<ya::Texture>(L"Texture"));

		m_lightings_.push_back(new BCO_Lighting(this));
		m_lightings_[0]->Initialize();
		SetName(L"Light");
	}

	void BCO_Light::Update()
	{
		IJ::ButtonConnectedObject::Update();
		if (GetBCOState() == eBCOState::Activated)
		{
			for (const auto& child : m_lightings_)
			{
				child->Update();
			}
		}
	}

	void BCO_Light::LateUpdate()
	{
		IJ::ButtonConnectedObject::LateUpdate();
	}

	void BCO_Light::Render()
	{
		IJ::ButtonConnectedObject::Render();
		if (GetBCOState() == eBCOState::Activated)
		{
			for (const auto& child : m_lightings_)
			{
				child->Render();
			}
		}
	}

	void BCO_Light::OnCollisionEnter(ya::Collider* other)
	{
		ButtonConnectedObject::OnCollisionEnter(other);
	}

	void BCO_Light::OnCollisionStay(ya::Collider* other)
	{
		ButtonConnectedObject::OnCollisionStay(other);
	}

	void BCO_Light::OnCollisionExit(ya::Collider* other)
	{
		ButtonConnectedObject::OnCollisionExit(other);
	}
}