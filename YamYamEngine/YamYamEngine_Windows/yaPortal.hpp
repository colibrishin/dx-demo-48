#pragma once
#include "yaCollider.h"
#include "yaGameObject.h"
#include "yaRigidbody.h"
#include "yaTransform.h"

namespace ya
{
	class Portal : public GameObject
	{
	public:
		Portal(GameObject* wall);
		Portal(const Portal& other) = default;
		~Portal() override = default;

		void OnCollisionEnter(Collider* other) override;

		void SetPosition(Vector2 position);

		void Initialize() override;
	private:
		// 포탈의 앞 방향
		Vector2 m_forward_;
		// 짝이 되는 반대편 포탈
		Portal* m_ptr_pair_;
		// 붙어있는 벽
		GameObject* m_ptr_wall_;
	};
}
