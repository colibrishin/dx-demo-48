#include "yaPortal.hpp"

namespace ya
{
	Portal::Portal(GameObject* wall) : GameObject(), m_forward_{}, m_ptr_pair_(nullptr), m_ptr_wall_(wall)
	{
		AddComponent<Collider>();
		AddComponent<Transform>();
		GetComponent<Collider>()->SetSize({ 1.0f, 1.0f });

		// 포탈은 벽에 붙어있어야 함
		// TODO: GameObject가 벽인지 확인하기
		assert(wall != nullptr);
	}

	void Portal::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);

		// 짝이 되는 포탈이 없으면 무시
		if (m_ptr_pair_ == nullptr)
		{
			return;
		}

		const auto& other_object = other->GetOwner();
		const auto& other_transform = other_object->GetComponent<Transform>();
		const auto& pair_position = m_ptr_pair_->GetComponent<Transform>()->GetPosition();

		// TODO: 만약 벽과 부딪히면 아무것도 안하기
		// 위치를 얻어올 수 없거나, 물리 효과가 적용되지 않는 물체면 아무것도 안함
		if(other_transform == nullptr || other_object->GetComponent<Rigidbody>() == nullptr)
		{
			return;
		}

		// 물체가 부딪히면 반대 포탈로 이동
		other_transform->SetPosition(pair_position);

		// 물체가 이동하던 방향을 반대 포탈의 방향에 맞게 전환
		const auto& velocity_zero = other_object->GetComponent<Rigidbody>()->GetVelocity();
		Vector2 velocity_one{};

		// 두 포탈의 x축 앞 방향이 다른 경우, 가속도를 그대로 적용
		if (Sign(m_forward_.x) ^ Sign(m_ptr_pair_->m_forward_.x))
		{
			velocity_one.x = velocity_zero.x;
		}
		// 두 포탈의 x축 앞 방향이 같은 경우, 가속도를 반대로 적용
		else if (Sign(m_forward_.x) & Sign(m_ptr_pair_->m_forward_.x))
		{
			velocity_one.x = -velocity_zero.x;
		}

		// TODO: 중력가속도를 일반 가속도로 변환하기
		// 두 포탈의 y축 앞 방향이 다른 경우, 가속도를 그대로 적용
		if (Sign(m_forward_.y) ^ Sign(m_ptr_pair_->m_forward_.y))
		{
			velocity_one.y = velocity_zero.y;
		}
		// 두 포탈의 y축 앞 방향이 같은 경우, 가속도를 반대로 적용
		else if (Sign(m_forward_.y) & Sign(m_ptr_pair_->m_forward_.y))
		{
			velocity_one.y = -velocity_zero.y;
		}

		other_object->GetComponent<Rigidbody>()->SetVelocity(velocity_one);

		// TODO: 포탈을 빠져나온 물체가 다시 반대편 포탈에 바로 들어가지 않도록 방지
	}

	void Portal::SetOtherPortal(Portal* other_portal)
	{
		m_ptr_pair_ = other_portal;
	}

	void Portal::Initialize()
	{
		GameObject::Initialize();
	}

	void Portal::Update()
	{
		GameObject::Update();

		// Transform과 Collider의 위치 정보를 동기화
		const auto tr_position = GetComponent<Transform>()->GetPosition();
		GetComponent<Collider>()->SetPosition({ tr_position.x, tr_position.y });

		// 벽이 움직일 경우를 대비해 매 프레임마다 벽의 위치를 받아옴
		const auto wall = m_ptr_wall_->GetComponent<Transform>()->GetPosition();
		const auto portal = GetComponent<Transform>()->GetPosition();

		Vector3 delta{};
		(portal - wall).Normalize(delta);

		// 포탈이 벽보다 x축으로 앞에 있을 경우 => {0.9~, 0.~}
		// 포탈이 벽보다 x축으로 뒤에 있을 경우 => {-0.9~, 0.~}
		// 포탈이 벽보다 y축으로 앞에 있을 경우 => {0.~, 0.9~}
		// 포탈이 벽보다 y축으로 뒤에 있을 경우 => {0.~, -0.9~}
		// 기울어 있을 경우 두 성분이 섞여 있음
		m_forward_ = Vector2{ delta.x, delta.y };
	}

	void Portal::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Portal::Render()
	{
		GameObject::Render();
	}

	void Portal::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionStay(other);
	}

	void Portal::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionExit(other);
	}
}
