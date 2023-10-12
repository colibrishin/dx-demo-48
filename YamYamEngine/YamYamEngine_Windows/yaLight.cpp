#include "yaCollider.h"
#include "yaLight.h"

#include "yaMeshRenderer.h"
#include "yaResources.h"

namespace ya
{
	Light::Light(float light_range) : m_light_range_(light_range)
	{
	}

	void Light::Initialize()
	{
		IJ::ButtonConnectedObject::Initialize();

		const auto tr = AddComponent<Transform>();
		tr->SetScale(1.0f, 1.0f, 1.0f);

		const auto mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"CircleMesh"));
		mr->SetShader(Resources::Find<Shader>(L"ColorShader"));
		mr->SetTexture(Resources::Find<Texture>(L"Texture"));

		m_lightings_.push_back(new Lighting(this));
		m_lightings_[0]->Initialize();
		SetName(L"Light");
	}

	void Light::Update()
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

	void Light::LateUpdate()
	{
		IJ::ButtonConnectedObject::LateUpdate();
	}

	void Light::Render()
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

	void Light::OnCollisionEnter(Collider* other)
	{
		IJ::ButtonConnectedObject::OnCollisionEnter(other);
	}

	void Light::OnCollisionStay(Collider* other)
	{
		IJ::ButtonConnectedObject::OnCollisionStay(other);
	}

	void Light::OnCollisionExit(Collider* other)
	{
		IJ::ButtonConnectedObject::OnCollisionExit(other);
	}
}
