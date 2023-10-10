#pragma once
#include "yaGameObject.h"
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
			Jump,
			Fall,
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
		void Jump();
		void Fall();
		void Hit();
		void Dead();


	private:
		eState mState;
		int HP;
		Rigidbody* rb;
		//float jumptime;
		PlayerShadow* m_shadow_;

	};
}
