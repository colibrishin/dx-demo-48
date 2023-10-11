#pragma once
#include "yaGameObject.h"
#include "yaLighting.h"
#include "yaTransform.h"
#include <set>

namespace ya
{
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

	private:
		friend class Player;

		void PlayerCollisionLightEnter(Lighting* light);
		void PlayerCollisionLightExit(Lighting* light);

		Lighting* GetClosestLight();
		void FlipShadowIfLower(Transform* tr, Vector3 player_pos, Vector3& mouse_position);
		void LimitShadowCasting(Vector3& mouse_position, Collider* const cldr, const float diff, const float light_range);

		std::set<Lighting*> m_meeting_lights_;
		Player*	m_player_;
	};
}
