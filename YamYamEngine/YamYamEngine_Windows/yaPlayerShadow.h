#pragma once
#include "yaGameObject.h"
#include "yaTransform.h"

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
		Player*	m_player_;
	};
}
