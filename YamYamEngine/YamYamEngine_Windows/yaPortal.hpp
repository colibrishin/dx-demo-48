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
		// ��Ż�� �� ����
		Vector2 m_forward_;
		// ¦�� �Ǵ� �ݴ��� ��Ż
		Portal* m_ptr_pair_;
		// �پ��ִ� ��
		GameObject* m_ptr_wall_;
	};
}
