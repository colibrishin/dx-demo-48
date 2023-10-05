#pragma once
#include "yaGameObject.h"
#include "yaRigidbody.h"

namespace ya
{
	class Player : public GameObject
	{
	public:
		enum class eState
		{
			Live,
			Jump,
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

		void Live();
		void Jump();
		void Hit();
		void Dead();


	private:
		eState mState;
		int HP;
		Rigidbody* rb;
		float jumptime;

	};
}
