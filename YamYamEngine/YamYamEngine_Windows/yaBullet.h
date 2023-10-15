#pragma once
#include "yaGameObject.h"
#include "yaPlayerScript.h"
#include "yaTransform.h"

namespace ya
{
	class Bullet : public GameObject
	{
	public:
		Bullet();
		virtual ~Bullet();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		static void InstantiateBullet(Transform* tr, Vector3 offset, float speed);
	};
}
