#include "yaPlayerShadow.h"

#include "yaCollider.h"
#include "yaInput.h"
#include "yaLight.h"
#include "yaLighting.h"
#include "yaPlayer.h"
#include "yaMath.h"
#include "yaMeleeHitBox.hpp"
#include "yaMeshRenderer.h"
#include "yaResources.h"
#include "yaShadowMesh.hpp"
#include "yaTime.h"

namespace ya
{
	PlayerShadow::PlayerShadow(Player* target) : m_player_(target)
	{
	}

	void PlayerShadow::Initialize()
	{
		GameObject::Initialize();
		const auto tr = AddComponent<Transform>();
		tr->SetScale(1.0f, 1.0f, 1.0f);
		tr->SetPosition(m_player_->GetComponent<Transform>()->GetPosition());

		const auto mesh = AddComponent<MeshRenderer>();
		mesh->SetMesh(Resources::Find<Mesh>(L"ShadowMesh"));
		mesh->SetShader(Resources::Find<Shader>(L"ColorShader"));

		// TODO: 다른 그림자 또는 광원에 충돌했을떄의 처리
		AddComponent<Collider>()->SetSize({1.0f, 1.0f, 1.0f});

		m_melee_hitbox_ = new MeleeHitBox(m_player_);
		m_melee_hitbox_->Initialize();
		SetName(L"Shadow");
	}

	Lighting* PlayerShadow::GetClosestLight()
	{
		if (m_meeting_lights_.empty())
		{
			return nullptr;
		}

		Lighting* closest_light = *m_meeting_lights_.begin();
		const auto shadow_pos = GetComponent<Transform>()->GetPosition();
		float dist = Vector3::DistanceSquared(closest_light->GetComponent<Transform>()->GetPosition(), shadow_pos);

		for (const auto& light : m_meeting_lights_)
		{
			const auto pos = light->GetComponent<Transform>()->GetPosition();
			if (Vector3::DistanceSquared(pos, shadow_pos) < dist)
			{
				closest_light = light;
				dist = Vector3::DistanceSquared(pos, shadow_pos);
			}
		}

		return closest_light;
	}

	void PlayerShadow::FlipShadowIfLower(Transform* const tr, const Vector3 player_pos, Vector3& mouse_position)
	{
		if(mouse_position.y < 0.0f)
		{
			mouse_position = -mouse_position;
		}
	}


	void PlayerShadow::Update()
	{
		GameObject::Update();

		// 플레이어가 광원 아래에 있을 경우
		if(GetComponent<MeshRenderer>()->IsEnabled())
		{
			// TODO: 우회방식. 플레이어가 광원 위에 있는 상태에서 광원이 꺼질경우 그림자가 사라지도록 함.
			if(const auto light = GetClosestLight(); light != nullptr && light->GetLayer() == LAYER::NONE)
			{
				GetComponent<MeshRenderer>()->SetEnabled(false);
				m_meeting_lights_.erase(light);
				return;
			}

			const auto tr = GetComponent<Transform>();
			const auto player_pos = m_player_->GetComponent<Transform>()->GetPosition();
			const auto player_scale = m_player_->GetComponent<Transform>()->GetScale();
			auto mouse_coord = Input::GetCoordinationMousePosition();

			tr->SetPosition(player_pos);
			mouse_coord.z = player_pos.z;

			assert(m_meeting_lights_.size() > 0);

			const auto cldr = GetComponent<Collider>();
			const auto mesh = Resources::Find<ShadowMesh>(L"ShadowMesh");

			// 근처에서 가장 가까운 빛의 속성(최대 그림자의 거리)을 따라감.
			const auto light = GetClosestLight()->GetOrigin();

			// 마우스와 플레이어의 각을 구함.
			const auto norm = (player_pos - mouse_coord).normalize();

			// PI / 2는 꼭지점이 마우스를 향하도록 하기 위함.
			// TODO: 이걸 껐다 킬 수 있게 해서 방어용으로도 만들 수 있지 않을까?
			const auto angle = atan2(norm.y, norm.x) + XM_PI / 2;

			// 각도에 맞춰 Transform 그리고 충돌체를 회전
			tr->SetRotation(Quaternion::CreateFromAxisAngle(Vector3::Forward, angle));
			cldr->SetRotation(Quaternion::CreateFromAxisAngle(Vector3::Forward, angle));
			
			const auto distance = Vector3::Distance(player_pos, mouse_coord);
			// 그림자가 플레이어 주변을 겉돌게 하기 위해서 투영된 플레이어의 크기를 구함.
			const auto projected_scale = player_scale.Dot(Vector3::UnitX);

			if(distance > light->GetLightRange())
			{
				tr->SetPosition(player_pos - norm * (light->GetLightRange() - projected_scale));
				tr->SetScale(1.0f, light->GetLightRange(), 1.0f);
			}
			else
			{
				tr->SetPosition(player_pos - norm * (distance - projected_scale));
				tr->SetScale(1.0f, distance, 1.0f);
			}
		}
	}

	void PlayerShadow::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}

	void PlayerShadow::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionStay(other);
	}

	void PlayerShadow::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionExit(other);
	}

	void PlayerShadow::Attack()
	{
		MeleeHitBox::ProcessMeleeAttack(m_player_, m_melee_hitbox_->GetHitObjects());
	}

	void PlayerShadow::PlayerCollisionLightEnter(Lighting* light)
	{
		if (m_meeting_lights_.contains(light))
		{
			return;
		}

		const auto mesh = GetComponent<MeshRenderer>();
		mesh->SetEnabled(true);
		m_meeting_lights_.emplace(light);
	}

	void PlayerShadow::PlayerCollisionLightExit(Lighting* light)
	{
		const auto mesh = GetComponent<MeshRenderer>();
		mesh->SetEnabled(false);
		m_meeting_lights_.erase(light);
	}
}
