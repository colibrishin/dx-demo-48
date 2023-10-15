#include "yaLighting.h"
#include "yaLight.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"
#include "yaCollider.h"

namespace ya
{
	Lighting::Lighting(Light* origin) : m_origin_(origin)
	{
	}

	void ya::Lighting::Initialize()
	{
		IJ::ButtonConnectedObject::Initialize();
		const auto tr = AddComponent<Transform>();
		tr->SetScale(1.0f, m_origin_->m_light_range_, 1.0f);

		const auto mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"LightingMesh"));
		mr->SetShader(Resources::Find<Shader>(L"ColorShader"));
		mr->SetColor({1.0f, 1.0f, 1.0f, 0.5f});

		const auto cldr = AddComponent<Collider>();
		cldr->SetSize({1.0f, m_origin_->m_light_range_, 1.0f});
		SetName(L"Lighting");
	}

	void Lighting::Update()
	{
		if (m_origin_->GetBCOState() == ButtonConnectedObject::eBCOState::Activated)
		{
			ButtonConnectedObject::Update();
			const auto tr = GetComponent<ya::Transform>();
			const auto light_origin_pos = m_origin_->GetComponent<ya::Transform>()->GetPosition();
			const auto light_origin_scale = m_origin_->GetComponent<ya::Transform>()->GetScale();

			tr->SetPosition(light_origin_pos - ya::Vector3(0.0f, light_origin_scale.y / 2, 0.0f));
			SetLayer(ya::LAYER::LIGHT);
		}
		else
		{
			
			SetLayer(ya::LAYER::NONE);
		}
	}

	void Lighting::LateUpdate()
	{
		IJ::ButtonConnectedObject::LateUpdate();
	}

	void Lighting::Render()
	{
		if (m_origin_->GetBCOState() == ButtonConnectedObject::eBCOState::Activated)
		{
			IJ::ButtonConnectedObject::Render();
		}
	}

	void Lighting::OnCollisionEnter(Collider* other)
	{
		IJ::ButtonConnectedObject::OnCollisionEnter(other);
	}

	void Lighting::OnCollisionStay(Collider* other)
	{
		IJ::ButtonConnectedObject::OnCollisionStay(other);
	}

	void Lighting::OnCollisionExit(Collider* other)
	{
		IJ::ButtonConnectedObject::OnCollisionExit(other);
	}
}
