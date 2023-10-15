#include "yaPlayer.h"

#include "yaBullet.h"
#include "yaInput.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaMeshRenderer.h"
#include "yaPlayerScript.h"
#include "yaResources.h"
#include "yaRigidbody.h"
#include "yaCollider.h"
#include "yaMeleeHitBox.hpp"
#include "yaRigidbody.h"
#include "yaSceneManager.h"

namespace ya
{
	Player::Player()
		: HP(100),
		//jumptime(0.f),
		rb{ nullptr },
		mState(eState::Idle)
	{
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		GameObject::Initialize();

		AddComponent<Transform>();
		AddComponent<Rigidbody>();
		AddComponent<Collider>();
		m_shadow_ = new PlayerShadow(this);
		m_shadow_->Initialize();

		rb = GetComponent<Rigidbody>();
		rb->SetGround(true);

		m_melee_hitbox_ = new MeleeHitBox(this);
		m_melee_hitbox_->Initialize();
	}

	void Player::Update()
	{
		GameObject::Update();
		m_shadow_->Update();

		m_melee_hitbox_->GetComponent<Transform>()->SetPosition(GetComponent<Transform>()->GetPosition());

		switch (mState)
		{
		case ya::Player::eState::Live:
			Live();
			break;

		case ya::Player::eState::Idle:
			Idle();
			break;

		case ya::Player::eState::MeleeAttack:
			MeleeAttack();
			break;

		case ya::Player::eState::RangeAttack:
			RangeAttack();
			break;

		case ya::Player::eState::Shoot:
			Shoot();
			break;

		case ya::Player::eState::Hit:
			Hit();
			break;

		case ya::Player::eState::Dead:
			Dead();
			break;

		case ya::Player::eState::End:
			break;
		default:
			break;
		}
	}
	void Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Player::Render()
	{
		GameObject::Render();
		m_shadow_->Render();
	}
	void Player::OnCollisionEnter(Collider* other)
	{
		const auto layer = other->GetOwner()->GetLayer();

		if (layer == LAYER::ATTACK || layer == LAYER::MONSTER)
		{
			if (other->GetOwner() == m_shadow_->m_melee_hitbox_ || 
				other->GetOwner() == m_melee_hitbox_)
			{
				return;
			}

			mState = eState::Hit;
		}

		// ��Ż �浹 �� 
		else if (layer == LAYER::PORTAL)
		{
			
		}

		else if (layer == LAYER::TILE)
		{
			
		}

		else if (layer == LAYER::ITEM)
		{

		}
		else if(const auto light = dynamic_cast<Lighting*>(other->GetOwner()); layer == LAYER::LIGHT)
		{
			m_shadow_->PlayerCollisionLightEnter(light);
		}

	}
	void Player::OnCollisionStay(Collider* other)
	{
		const auto layer = other->GetOwner()->GetLayer();

		if(const auto light = dynamic_cast<Lighting*>(other->GetOwner()); layer == LAYER::LIGHT)
		{
			m_shadow_->PlayerCollisionLightEnter(light);
		}
	}

	void Player::OnCollisionExit(Collider* other)
	{
		const auto layer = other->GetOwner()->GetLayer();

		if(const auto light = dynamic_cast<Lighting*>(other->GetOwner()); layer == LAYER::LIGHT)
		{
			m_shadow_->PlayerCollisionLightExit(dynamic_cast<Lighting*>(other->GetOwner()));
		}
	}
	void Player::Idle()
	{
	}

	void Player::Live()
	{
	}

	void Player::Shoot()
	{
	}

	void Player::DispatchShadowAttack()
	{
		m_shadow_->Attack();
	}

	void Player::MeleeAttack()
	{
		DispatchShadowAttack();
		MeleeHitBox::ProcessMeleeAttack(this, m_melee_hitbox_->GetHitObjects());

		mState = eState::Idle;
	}

	void Player::RangeAttack()
	{
		DispatchShadowAttack();
		const auto mouse_pos = Input::GetCoordinationMousePosition();


		Bullet::InstantiateBullet(GetComponent<Transform>(), (mouse_pos - GetComponent<Transform>()->GetPosition()).normalize(), 1.5f);

		mState = eState::Idle;
	}

	void Player::Hit()
	{
		if(HP != 0)
		{
			HP -= 20;
		}
		else
		{
			mState = eState::Dead;
		}
	}
	void Player::Dead()
	{
		Destroy(this);
	}
}
