#pragma once
#include "yaGameObject.h"
#include "yaLighting.h"
#include "yaTransform.h"
#include <set>

namespace ya
{
	class MeleeHitBox;
	class Player;

	class PlayerShadow : public GameObject
	{
	public:
		PlayerShadow(Player* target);
		PlayerShadow(const PlayerShadow& other) = default;
		~PlayerShadow() override = default;

		void Initialize() override;
		void Update() override;
		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		void Attack();

		MeleeHitBox* GetMeleeHitBox() const { return m_melee_hitbox_; }

	private:
		friend class Player;

		void PlayerCollisionLightEnter(Lighting* light);
		void PlayerCollisionLightExit(Lighting* light);

		Lighting* GetClosestLight();
		void FlipShadowIfLower(Transform* const tr, const Vector3 player_pos, Vector3& mouse_position);

		std::set<Lighting*> m_meeting_lights_;

		Player*	m_player_;
		MeleeHitBox* m_melee_hitbox_;
	};
}
