#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Turret : public GameObject
	{
	public:
		enum class eState
		{
			Idle,
			Grabbed,
			Distroy,
			End,
		};

		Turret();
		virtual ~Turret();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void Idle();
		void Grabbed();
		void Distroy();

	private:
		eState mState;
	};
}
