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
//		mResolution.x = application.GetWidth();		// �ػ󵵸�ŭ ���� ����
//		mResolution.y = application.GetHeight();	// �ػ󵵸�ŭ ���� ����
//		mLookPosition = mResolution / 2.0f;			// ���� ��ġ�� â�� �߾����� ����, /�� vector2�� ���۷�����
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
//		if (mTarget)	// Ÿ���� ���� �ƴϸ�� ���� �ǹ�
//		{
//			Transform* tr = mTarget->GetComponent<Transform>();
//			mLookPosition = tr->GetPosition();		// �ٶ� Ÿ��(�÷��̾�)�� �ִٸ� �� Ÿ���� 
//													// ī�޶�(mLookPosition)�� �ٶ󺸰Բ� ����
//		}
//
//		mDistance = mLookPosition - (mResolution / 2.0f);	
//		// mDistance -> ������ ��ǥ�迡�� ī�޶� �̵��� �Ÿ�
//		// ����� �������� 0,0�� ����ϰڴٴ� ��
//		// ������ ��ǥ�迡���� ������ ��Ŀ����
//		// ���ߴ� �۾�
//	}
//}

