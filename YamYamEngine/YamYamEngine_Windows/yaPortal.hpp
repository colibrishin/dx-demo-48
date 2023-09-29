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
		// 포탈이 사용된 시간
		float m_timer_;
		// 포탈과 벽의 각도
		float m_angle_;
		// 포탈의 앞 방향
		Vector2 m_forward_;
		// ¦�� �Ǵ� �ݴ��� ��Ż
		Portal* m_ptr_pair_;
		// �پ��ִ� ��
		GameObject* m_ptr_wall_;
	};
}
