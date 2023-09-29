//#pragma once
//#include "yaGameObject.h"

// 카메라는 어디서든 사용되어야 하므로 static

//namespace ya
//{
//	using namespace math;
//	class Camera
//	{
//	public:
//		static void Initalize();
//		static void Update();
//
//		// 카메라가 움직인 방향의 반대만큼 물체들이 움직이면 카메라가 움직인 것
//		static Vector2 CalculatePosition(Vector2 pos) { return pos - mDistance; }
//
//		static GameObject* GetTarget() { return mTarget; }
//		static void SetTarget(GameObject* target) { mTarget = target; }
//
//
//	private:
//		// 화면 해상도
//		static Vector2 mResolution;		
//		// 카메라가 바라보고 있는 위치(윈도우 좌표계 기준)
//		static Vector2 mLookPosition;	
//		// 가운데를 원점으로 이동한 거리
//		static Vector2 mDistance;			
//		// 카메라가 바라보는 게임 오브젝트
//		static GameObject* mTarget;	
//	};
//}


