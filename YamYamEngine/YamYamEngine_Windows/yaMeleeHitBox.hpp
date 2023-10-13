#pragma once
#include "yaGameObject.h"
#include "yaPlayerShadow.h"
#include "yaRigidbody.h"

namespace ya
{
	class MeleeHitBox : public GameObject
	{
	public:
		MeleeHitBox(GameObject* player);
		~MeleeHitBox() override = default;

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		static void ProcessMeleeAttack(GameObject* player, const std::set<GameObject*>& hit_objects);

		const std::set<GameObject*>& GetHitObjects() const { return mHitObjects; }

		void OnCollisionEnter(class Collider* other) override;
		void OnCollisionStay(class Collider* other) override;
		void OnCollisionExit(class Collider* other) override;

	private:
		GameObject* mPlayer;
		std::set<GameObject*> mHitObjects;
	};
}
