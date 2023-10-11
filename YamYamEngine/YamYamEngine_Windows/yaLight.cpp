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
		GameObject::Initialize();

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
		GameObject::Update();
		for (const auto& child : m_lightings_)
		{
			child->Update();
		}
	}

	void Light::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Light::Render()
	{
		GameObject::Render();
		for (const auto& child : m_lightings_)
		{
			child->Render();
		}
	}

	void Light::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void Light::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionStay(other);
	}

	void Light::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionExit(other);
	}
}
