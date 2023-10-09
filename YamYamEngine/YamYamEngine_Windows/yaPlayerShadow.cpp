#include "yaPlayerShadow.h"
#include "yaPlayer.h"
#include "yaMath.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"
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
		tr->SetRotation(Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, Radian(180.0f)));
		tr->SetScale(1.0f, 1.0f, 1.0f);
		tr->SetPosition(m_player_->GetComponent<Transform>()->GetPosition() - math::Vector3(0.0f, 1.0f, 0.0f));

		const auto mesh = AddComponent<MeshRenderer>();
		mesh->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
		mesh->SetShader(Resources::Find<Shader>(L"ColorShader"));
		
	}

	void PlayerShadow::Update()
	{
		GameObject::Update();

		const auto tr = GetComponent<Transform>();
		const auto player_pos = m_player_->GetComponent<Transform>()->GetPosition();
		tr->SetPosition(player_pos - math::Vector3(0.0f, 1.0f, 0.0f));
	}
}
