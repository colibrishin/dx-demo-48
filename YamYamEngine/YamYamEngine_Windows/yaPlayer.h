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
			MeleeAttack,
			RangeAttack,
			Hit,
			Dead,
			End,
		};

		enum class ePlayerAs
		{
			Self,
			Shadow
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
		void MeleeAttack();
		void RangeAttack();
		void Hit();
		void Dead();

		void SetState(eState state) { mState = state; }
		void SetPlayerAs(ePlayerAs player_as) { mPlayerAs = player_as; }

		eState GetState() const { return mState; }

		MeleeHitBox* GetMeleeHitBox() const { return m_melee_hitbox_; }
		PlayerShadow* GetPlayerShadow() const { return m_shadow_; }
		

	private:
		void DispatchShadowAttack();

		eState mState;
		ePlayerAs mPlayerAs;

		bool mBRUnlocked;
		bool mBGUnlocked;
		bool mBBUnlocked;

		int HP;
		Rigidbody* rb;
		//float jumptime;

		PlayerShadow* m_shadow_;
		MeleeHitBox* m_melee_hitbox_;
	};
}
