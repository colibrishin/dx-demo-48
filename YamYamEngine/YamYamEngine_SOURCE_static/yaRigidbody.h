#pragma once
#include "yaComponent.h"

namespace ya
{
	using namespace math;
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate() override;
		virtual void Render();

		void AddForce(Vector3 force) { mForce += force; }
		void SetMass(float mass) { mMass = mass; }
		void SetGround(bool ground) { mbGround = ground; }

		Vector3 GetVelocity() { return mVelocity; }
		void SetVelocity(Vector3 velocity) { mVelocity = velocity; }
		Vector3 GetGravity() { return mGravity; }
		void SetGravity(Vector3 gravity) { mGravity = gravity; }
		void SetFriction(float friction) { mFriction = friction; }

	private:
		float mMass;

		float mFriction;
		float mStaticFriction;
		float mKineticFrction;
		float mCoefficentFrction;

		Vector3 mForce;
		Vector3 mAccelation;
		Vector3 mVelocity;
		Vector3 mGravity;
		Vector3 mLimitedVelocty;

		bool mbGround;
	};
}



