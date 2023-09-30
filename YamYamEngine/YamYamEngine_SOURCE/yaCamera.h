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

	private:
		// 현재 카메라 파라메터를 상수 버퍼로 바인딩
		static void SetConstantBuffer();

		inline static Vector3 mLookPosition{};	
		inline static Vector3 mPosition{};
		inline static Quaternion mRotation{};

		// 카메라 글로벌 월드의 중심점
		inline static XMMATRIX mWorldMatrix{};
		// 화면에 따른 투영 행렬
		inline static XMMATRIX mProjectionMatrix{};
		// 카메라의 위치, 회전에 따른 뷰 행렬
		inline static XMMATRIX mViewMatrix{};
	};
}


