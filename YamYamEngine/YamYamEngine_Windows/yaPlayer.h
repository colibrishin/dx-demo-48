#pragma once
#include "yaGameObject.h"
#include "yaMeleeHitBox.hpp"
#include "yaPlayerShadow.h"
#include "yaRigidbody.h"

namespace ya
{
	class Player : public GameObject
	{
	public:
		enum class eState
		{
			Idle,
			Live,
			Shoot,
			Attack,
			Hit,
			Dead,
			End,
		};

		Player();
		virtual ~Player();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void Idle();
		void Live();
		void Shoot();
		void Attack();
		void Fall();
		void Hit();
		void Dead();

		void SetState(eState state) { mState = state; }

		MeleeHitBox* GetMeleeHitBox() const { return m_melee_hitbox_; }
		PlayerShadow* GetPlayerShadow() const { return m_shadow_; }

	private:
		void DispatchShadowAttack();

		eState mState;
		int HP;
		Rigidbody* rb;
		//float jumptime;

		PlayerShadow* m_shadow_;
		MeleeHitBox* m_melee_hitbox_;
	};
}
