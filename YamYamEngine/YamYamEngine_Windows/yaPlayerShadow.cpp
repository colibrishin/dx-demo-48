#include "yaPlayerShadow.h"

#include "yaCollider.h"
#include "yaInput.h"
#include "yaLight.h"
#include "yaLighting.h"
#include "yaPlayer.h"
#include "yaMath.h"
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
			const auto tr = GetComponent<Transform>();
			const auto player_pos = m_player_->GetComponent<Transform>()->GetPosition();

			assert(m_meeting_lights_.size() > 0);

			auto mouse_norm = Input::GetNormalizedMousePosition();
			const auto cldr = GetComponent<Collider>();
			const auto mesh = Resources::Find<ShadowMesh>(L"ShadowMesh");

			// 근처에서 가장 가까운 빛의 속성을 따라감.
			const auto light = GetClosestLight()->GetOrigin();

			// NOTE: D3D11_RASTERIZER_DESC에서 CullMode를 None으로 설정하면 반대편 삼각형도 그릴 수 있음.
			// 충돌처리 고려를 위해 삼각형 꼭지점 이동과 동시에 회전하고 움직인 Collider를 사용하기로 함.
			Vector3 flipped_mouse_norm = mouse_norm;
			FlipShadowIfLower(tr, player_pos, flipped_mouse_norm);
			const auto aspect_ratio = application.GetWidth() / static_cast<float>(application.GetHeight());
			const auto mouse_aspect = flipped_mouse_norm * aspect_ratio;

			// 플레이어가 항상 카메라 가운데 있을 것이라고 가정.
			const auto distance = std::sqrt(mouse_aspect.LengthSquared());

			if(distance > light->GetLightRange())
			{
				return;
			}

			// 마우스 방향으로 충돌 박스를 회전 (중심점은 삼각형의 중심)
			cldr->SetRotation(
				Quaternion::CreateFromAxisAngle(
					Vector3::Forward, atan2(mouse_norm.y, mouse_norm.x)));

			cldr->SetSize({1.0f, distance, 1.0f});

			if(distance > 1.0f)
			{
				tr->SetScale(1.0f, distance, 1.0f);

				if(mouse_norm.y < 0.0f) // 아래로 가면
				{
					tr->SetRotation(0.0f, 0.0f, Radian(180.0f));
					tr->SetPosition(player_pos.x, (player_pos.y - distance / 2) - 0.5f, player_pos.z);
				}
				else
				{
					tr->SetRotation(0, 0, 0);
					tr->SetPosition(player_pos.x, (player_pos.y + distance / 2) - 0.5f, player_pos.z);
				}
			}
			else
			{
				if(mouse_norm.y < 0.0f)
				{
					tr->SetRotation(0.0f, 0.0f, Radian(180.0f));
					tr->SetPosition(player_pos.x, player_pos.y - 1.0f, player_pos.z);
				}
				else
				{
					tr->SetRotation(0, 0, 0);
					tr->SetPosition(player_pos.x, player_pos.y, player_pos.z);
				}
			}

			mesh->ChangeTopPosition(mouse_aspect);
			mesh->Refresh();
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
