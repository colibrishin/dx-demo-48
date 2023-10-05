#include "yaPortal.hpp"

#include "yaTime.h"

namespace ya
{
	Portal::Portal(GameObject* wall) : GameObject(), m_forward_{}, m_ptr_pair_(nullptr), m_ptr_wall_(wall)
	{
		AddComponent<Collider>();
		AddComponent<Transform>();

		// 포탈은 벽에 붙어있어야 함
		// TODO: GameObject가 벽인지 확인하기
		assert(wall != nullptr);
	}

	void Portal::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);

		// 짝이 되는 포탈이 없으면 정지
		if (m_ptr_pair_ == nullptr)
		{
			return;
		}

		// TODO: 만약 벽과 부딪히면 아무것도 안하기

		const auto& other_object = other->GetOwner();
		const auto& other_transform = other_object->GetComponent<Transform>();
		const auto& pair_position = m_ptr_pair_->GetComponent<Transform>()->GetPosition();

		// TODO: 만약 벽과 부딪히면 아무것도 안하기
		// 위치를 얻어올 수 없거나, 물리 효과가 적용되지 않는 물체면 아무것도 안함
		if(other_transform == nullptr || other_object->GetComponent<Rigidbody>() == nullptr)
		{
			return;
		}

		// 포탈이 쓰인지 얼마 안됐음
		if (m_timer_ < 1.0f)
		{
			return;
		}

		// 물체가 부딪히면 반대 포탈로 이동
		other_transform->SetPosition(pair_position);

		// 물체가 이동하던 방향을 반대 포탈의 방향에 맞게 전환
		const auto& velocity_zero = other_object->GetComponent<Rigidbody>()->GetVelocity();
		Vector3 velocity_one{};

		// TODO: 벽의 기울기 반영하기
		// TODO: 성분이 여러개인 경우?
		velocity_one = velocity_one.Length() * m_ptr_pair_->m_forward_;

		other_object->GetComponent<Rigidbody>()->SetVelocity(velocity_one);

		// 포탈이 사용됐으니 타이머 초기화 (반대편도 동시에 초기화)
		m_timer_ = 0.0f;
		m_ptr_pair_->m_timer_ = 0.0f;
	}

	void Portal::SetPosition(Vector2 position)
	{
		GetComponent<Transform>()->SetPosition({ position.x, position.y, 1 });
	}

	void Portal::Initialize()
	{
		GameObject::Initialize();
	}

	void Portal::Update()
	{
		GameObject::Update();

		// 오버플로우 방지
		if (m_timer_ < 1.0f)
		{
			// 마지막으로 포탈 사용된 시간 체크
			m_timer_ += Time::DeltaTime();
		}
		// 벽이 움직일 경우를 대비해 매 프레임마다 벽의 위치를 받아옴

		const auto wall = m_ptr_wall_->GetComponent<Transform>()->GetPosition();
		const auto portal = GetComponent<Transform>()->GetPosition();

		// 포탈의 앞방향 구하기
		Vector3 delta{};
		(portal - wall).Normalize(delta);

		// 벽이랑 같은 위치에 있을 경우 포탈의 앞방향을 구분할 수 없음
		assert(delta.x == 0.0f || delta.y == 0.0f);

		// 포탈이 벽보다 x축으로 앞에 있을 경우 => {1, 0}
		// 포탈이 벽보다 x축으로 뒤에 있을 경우 => {-1, 0}
		// 포탈이 벽보다 y축으로 앞에 있을 경우 => {0, 1}
		// 포탈이 벽보다 y축으로 뒤에 있을 경우 => {0, -1}
		m_forward_ = Vector3{ delta.x, delta.y, 0.0f };
	}

	void Portal::SetOtherPortal(Portal* portal)
	{
		m_ptr_pair_ = portal;
	}
}
