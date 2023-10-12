#include "IJ_BCO_Lighting.h"
#include "IJ_BCO_Light.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"
#include "yaCollider.h"


namespace IJ
{
	BCO_Lighting::BCO_Lighting(BCO_Light* origin) : m_origin_(origin)
	{
	}

	void BCO_Lighting::Initialize()
	{
		ButtonConnectedObject::Initialize();

		const auto tr = AddComponent<ya::Transform>();
		tr->SetScale(1.0f, m_origin_->m_light_range_, 1.0f);

		const auto mr = AddComponent<ya::MeshRenderer>();
		mr->SetMesh(ya::Resources::Find<ya::Mesh>(L"LightingMesh"));
		mr->SetShader(ya::Resources::Find<ya::Shader>(L"ColorShader"));
		mr->SetColor({ 1.0f, 1.0f, 1.0f, 0.5f });

		const auto cldr = AddComponent<ya::Collider>();
		cldr->SetSize({ 1.0f, m_origin_->m_light_range_, 1.0f });
		SetName(L"Lighting");
	}

	void BCO_Lighting::Update()
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

	void BCO_Lighting::LateUpdate()
	{
		if (m_origin_->GetBCOState() == ButtonConnectedObject::eBCOState::Activated)
			ButtonConnectedObject::LateUpdate();
	}

	void BCO_Lighting::Render()
	{
		if (m_origin_->GetBCOState() == ButtonConnectedObject::eBCOState::Activated)
			ButtonConnectedObject::Render();
	}

	void BCO_Lighting::OnCollisionEnter(ya::Collider* other)
	{
		if (m_origin_->GetBCOState() == ButtonConnectedObject::eBCOState::Activated)
			ButtonConnectedObject::OnCollisionEnter(other);
	}

	void BCO_Lighting::OnCollisionStay(ya::Collider* other)
	{
		if (m_origin_->GetBCOState() == ButtonConnectedObject::eBCOState::Activated)
			ButtonConnectedObject::OnCollisionStay(other);
	}

	void BCO_Lighting::OnCollisionExit(ya::Collider* other)
	{
		if (m_origin_->GetBCOState() == ButtonConnectedObject::eBCOState::Activated)
			ButtonConnectedObject::OnCollisionExit(other);
	}
}