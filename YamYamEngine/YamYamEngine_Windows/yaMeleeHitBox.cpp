#include "yaMeleeHitBox.hpp"

#include "yaCollider.h"
#include "yaPlayer.h"

namespace ya
{
	MeleeHitBox::MeleeHitBox(GameObject* player) : mPlayer(player)
	{
		SetName(L"PlayerMeleeHitBox");
	}

	void MeleeHitBox::Initialize()
	{
		GameObject::Initialize();
		AddComponent<Transform>();
		AddComponent<Collider>();
		GetComponent<Transform>()->SetScale(mPlayer->GetComponent<Transform>()->GetScale() * 1.5f);
		SetLayer(LAYER::ATTACK);
	}

	void MeleeHitBox::Update()
	{
		GameObject::Update();
		GetComponent<Transform>()->SetPosition(mPlayer->GetComponent<Transform>()->GetPosition());
	}

	void MeleeHitBox::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void MeleeHitBox::Render()
	{
		GameObject::Render();
	}

	void MeleeHitBox::ProcessMeleeAttack(GameObject* player, const std::set<GameObject*>& hit_objects)
	{
		for (const auto& object : hit_objects)
		{
			if(object == player)
			{
				continue;
			}

			if (object->GetLayer() == LAYER::MONSTER)
			{
				// TODO: 체력 깎기
				//dynamic_cast<Monster*>(object)->Hit(damage);
				//dynamic_cast<Player*>(object)->Hit(damage);
			}
		}
	}

	void MeleeHitBox::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);

		if(other->GetOwner() == mPlayer)
		{
			return;
		}

		mHitObjects.insert(other->GetOwner());
	}

	void MeleeHitBox::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionStay(other);
	}

	void MeleeHitBox::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionExit(other);

		if(other->GetOwner() == mPlayer)
		{
			return;
		}

		mHitObjects.erase(other->GetOwner());
	}
}
