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
			const auto tr = GetComponent<Transform>();
			const auto player_pos = m_player_->GetComponent<Transform>()->GetPosition();
			const auto player_scale = m_player_->GetComponent<Transform>()->GetScale();
			auto mouse_coord = Input::GetCoordinationMousePosition();

			tr->SetPosition(player_pos);
			mouse_coord.z = player_pos.z;

			assert(m_meeting_lights_.size() > 0);

			// 정사각형 높이, 정사각형 밑면으로 가는 길이, 
			const auto h = sqrtf(3) / 2;
			const auto tbm = sqrtf(3) / 6;

			// 근처에 있는 광원
			const auto light = GetClosestLight()->GetOrigin();

			// 마우스가 삼각형의 바닥을 기준으로 이동함
			const auto tri_bottom = player_pos - Vector3{0.0f, tbm, 0.0f};
			const auto mouse_dist = Vector3::Distance(mouse_coord, tri_bottom);

			// 광원이 제공하는 빛의 거리 이상으로는 그림자가 커지지 않음
			const auto shadow_casting = std::min(light->GetLightRange(), mouse_dist);
			// 밑변 x축 증가 상쇄용 비율
			const auto cancel_ratio = std::abs(1 / shadow_casting);
			const auto ratio = std::abs(shadow_casting);

			Vector3 mouse_norm;
			// 종점 - 시점
			(mouse_coord - tri_bottom).Normalize(mouse_norm);
			const auto angle = atan2f(mouse_norm.y, mouse_norm.x);
			const auto cldr = GetComponent<Collider>();
			const auto mesh = Resources::Find<ShadowMesh>(L"ShadowMesh");

			// 매쉬를 축소시켜서 크기 증가를 상쇄함
			const auto left = Vector3(-0.5f, -(sqrt(3) / 6), 0.f) * cancel_ratio;
			const auto right = Vector3(0.5f, -sqrt(3) / 6, 0.f) * cancel_ratio;
			tr->SetScale(1.0f * ratio, 1.0f * ratio, 1.0f);

			// 마우스 포인터가 아래에 있을 경우
			if(mouse_norm.y < 0)
			{
				// 히트박스 회전, 이동
				const auto bottom_fitting = (2 * h) / 3;
				cldr->SetPosition(player_pos - Vector3{0.0f, bottom_fitting + (h * ratio), 0.0f});
				cldr->SetSize({1.0f, 1.0f * ratio, 1.0f});
				cldr->SetRotation(Quaternion::CreateFromAxisAngle(Vector3::Forward, angle));

				// 뒷면 렌더링이 안되기 때문에 회전하고 바닥에 맞게 이동으로 우회
				tr->SetRotation(Quaternion::CreateFromAxisAngle(Vector3::Forward, Radian(180.0f)));
				tr->SetPosition(player_pos - Vector3{0.0f, bottom_fitting, 0.0f});
				// 2, 3 분면 각도를 1, 4 분면 각도로 변환해야 하여 분기 처리
				mesh->ChangeTopPosition({-cosf(angle) * h, -sinf(angle) * h - tbm, 0.0f});
			}
			else
			{
				cldr->SetPosition(player_pos + Vector3{0.0f, h * ratio, 0.0f});
				cldr->SetSize({1.0f, 1.0f * ratio, 1.0f});
				cldr->SetRotation(Quaternion::CreateFromAxisAngle(Vector3::Forward, angle));

				tr->SetPosition(player_pos);
				tr->SetRotation(Quaternion::Identity);
				mesh->ChangeTopPosition({cosf(angle) * h, sinf(angle) * h - tbm, 0.0f});
			}

			mesh->ChangeLeftPosition(left);
			mesh->ChangeRightPosition(right);
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
