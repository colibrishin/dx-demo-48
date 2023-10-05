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
		void Update() override;
		void SetOtherPortal(Portal* portal);

	private:
		// 포탈이 사용된 시간
		float m_timer_;
		// 포탈과 벽의 각도
		float m_angle_;
		// 포탈의 앞 방향
		Vector3 m_forward_;
		// 짝이 되는 반대편 포탈
		Portal* m_ptr_pair_;
		// 포탈이 붙어있는 벽
		GameObject* m_ptr_wall_;
	};
}
