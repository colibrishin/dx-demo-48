#pragma once
#include "yaComponent.h"



namespace ya
{
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetConstantBuffer();

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetRotation(Quaternion rotation) { mRotation = rotation; }
		void SetScale(Vector3 scale) { mScale = scale; }

		void SetPosition(float x, float y, float z) { mPosition = Vector3(x,y,z); }
		void SetRotation(float x, float y, float z) { mRotation = Quaternion::CreateFromYawPitchRoll(x, y, z); }
		void SetScale(float x, float y, float z) { mScale = Vector3(x, y, z); }

		Vector3 GetPosition() { return mPosition; }
		Quaternion GetRotation() { return mRotation; }
		Vector3 GetScale() { return mScale; }

	private:
		Vector3 mPosition;
		Quaternion mRotation;
		Vector3 mScale;
	};
}
