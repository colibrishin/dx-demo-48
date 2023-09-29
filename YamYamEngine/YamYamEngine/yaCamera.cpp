#include "yaCamera.h"
#include "yaCamera.h"
#include "yaApplication.h"
#include "yaTransform.h"
#include "yaInput.h"
#include "yaTime.h"

//extern ya::Application application;
//
//namespace ya
//{
//	Vector2 Camera::mResolution = Vector2::Zero;
//	Vector2 Camera::mLookPosition = Vector2::Zero;
//	Vector2 Camera::mDistance = Vector2::Zero;
//	GameObject* Camera::mTarget = nullptr;
//
//
//	void Camera::Initalize()
//	{
//		mResolution.x = application.GetWidth();		// 해상도만큼 가로 세팅
//		mResolution.y = application.GetHeight();	// 해상도만큼 세로 세팅
//		mLookPosition = mResolution / 2.0f;			// 보는 위치를 창의 중앙으로 맞춤, /는 vector2의 오퍼레이터
//	}
//
//	void Camera::Update()
//	{
//		if (Input::GetKey(eKeyCode::W))
//		{
//			mLookPosition.y -= 
// .0f * Time::DeltaTime();
//		}
//		if (Input::GetKey(eKeyCode::A))
//		{
//			mLookPosition.x -= 300.0f * Time::DeltaTime();
//		}
//		if (Input::GetKey(eKeyCode::S))
//		{
//			mLookPosition.y += 300.0f * Time::DeltaTime();
//		}
//		if (Input::GetKey(eKeyCode::D))
//		{
//			mLookPosition.x += 300.0f * Time::DeltaTime();
//		}
//
//		if (mTarget)	// 타겟이 널이 아니면과 같은 의미
//		{
//			Transform* tr = mTarget->GetComponent<Transform>();
//			mLookPosition = tr->GetPosition();		// 바라볼 타겟(플레이어)이 있다면 그 타겟을 
//													// 카메라(mLookPosition)가 바라보게끔 세팅
//		}
//
//		mDistance = mLookPosition - (mResolution / 2.0f);	
//		// mDistance -> 윈도우 좌표계에서 카메라가 이동한 거리
//		// 가운데를 기준으로 0,0을 사용하겠다는 것
//		// 윈도우 좌표계에서의 원점을 포커스로
//		// 맞추는 작업
//	}
//}

