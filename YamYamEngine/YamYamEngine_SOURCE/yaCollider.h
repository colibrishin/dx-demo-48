#pragma once
#include "yaComponent.h"

namespace ya
{
	using namespace math;
	class Collider : public Component
	{
	public:
		Collider();
		//Collider(Scene* Scene);
		~Collider();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		void OnCollisionEnter(Collider* other);		// 충돌 시작
		void OnCollisionStay(Collider* other);		// 충돌 중
		void OnCollisionExit(Collider* other);		// 충돌 빠져나감

		void ColliderOff();

		Vector2 GetSize() { return mSize; }
		void SetSize(Vector2 size) { mSize = size; }
		Vector2 GetOffset() { return mOffset; }
		void SetOffset(Vector2 offset) { mOffset = offset; }
		Vector2 GetPosition() { return mPosition; }
		void  SetPosition(Vector2 position) { mPosition = position; }

		UINT GetCollisionNumber() { return mCollisionNumber; }

	private:

		static UINT mCollisionCount;			// 고유번호 축적을 위한 변수

		Vector2 mSize;
		Vector2 mOffset;
		Vector2 mPosition;

		UINT mCollisionNumber;					// 충돌체가 각각의 고유 번호를 가짐	
		bool mbIsCollision;						// 충돌하는게 눈에 보이게 하고 싶었을 때 변수
	};
}