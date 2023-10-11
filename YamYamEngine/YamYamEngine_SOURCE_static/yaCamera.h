#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Camera
	{
	public:
		static void Initialize();
		static void Update();

		// 카메라의 위치, z 축으로 카메라를 앞뒤로 이동시킬 수 있음
		static void SetPosition(const Vector3& position) { mPosition = position; }
		// 카메라의 회전
		static void SetRotation(const Quaternion& rotation) { mRotation = rotation; }
		// 카메라가 바라보는 방향
		static void SetLookPosition(const Vector3& position) { mLookPosition = position; }
		// 추척하는 오브젝트, 설정될 경우 카메라의 위치가 오브젝트를 따라감
		static void SetTarget(GameObject* gameObject) { mGameObject = gameObject; }
		// 오브젝트 추적을 중단하고 카메라의 위치로 되돌아감.
		static void ResetTarget() { mGameObject = nullptr; }

		static Vector3 GetPosition() { return mPosition; }
		static XMMATRIX GetViewMatrix() { return mViewMatrix; }
		static XMMATRIX GetCameraPositionMatrix() { return XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z); }
		static XMMATRIX GetProjectionMatrix() { return mProjectionMatrix; }

	private:
		// 현재 카메라 파라메터를 상수 버퍼로 바인딩
		static void SetConstantBuffer();
		static void SetZoom(float zoom) { mZoom = zoom <= 0.0f ? 1.0f : zoom; }

		inline static GameObject* mGameObject{};

		inline static Vector3 mLookPosition{};	
		inline static Vector3 mPosition{};
		inline static Quaternion mRotation{};

		// 카메라 줌
		inline static float mZoom = 5.0f;

		// 카메라 글로벌 월드의 중심점
		inline static XMMATRIX mWorldMatrix{};
		// 화면에 따른 투영 행렬
		inline static XMMATRIX mProjectionMatrix{};
		// 카메라의 위치, 회전에 따른 뷰 행렬
		inline static XMMATRIX mViewMatrix{};
	};
}


