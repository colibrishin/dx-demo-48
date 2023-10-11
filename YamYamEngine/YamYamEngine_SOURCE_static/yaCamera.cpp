#include "yaCamera.h"
#include "yaCamera.h"
#include "yaApplication.h"
#include "yaConstantBuffer.h"
#include "yaTransform.h"
#include "yaInput.h"
#include "yaRenderer.h"
#include "yaTime.h"

extern ya::Application application;

void ya::Camera::Initialize()
{
	// LookAtLH에서 z 값 0을 받지 않음
	mLookPosition = Vector3::Forward;
	mPosition = Vector3{0, 0, -2};
}

void ya::Camera::Update()
{
	mWorldMatrix = XMMatrixIdentity();

	// 시야 왜곡을 없애기 위해 투영행렬로 직교행렬을 사용함
	mProjectionMatrix = XMMatrixOrthographicLH(mZoom * ((float)application.GetWidth() / application.GetHeight()), mZoom, 1.0f, 1000.f);

	XMVECTOR upVector = XMLoadFloat3(&Vector3::Up);
	XMVECTOR lookAtVector = XMLoadFloat3(&mLookPosition);
	XMVECTOR positionVector = XMLoadFloat3(&mPosition);

	if (mGameObject != nullptr)
	{
		auto object_pos = mGameObject->GetComponent<Transform>()->GetPosition();
		object_pos.z = -2;
		positionVector = XMLoadFloat3(&object_pos);
	}

	// 쿼토니안 값에서 회전 행렬을 구함
	const XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(mRotation);

	// 회전 행렬을 이용해서 회전된 카메라의 바라보는 방향과 위를 구함
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	// 바라보는 위치에 카메라 위치를 더함
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	// 카메라에 의해 생기는 뷰 행렬을 구함
	mViewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	SetConstantBuffer();
}

void ya::Camera::SetConstantBuffer()
{
	graphics::ConstantBuffer* cb = renderer::constantBuffers[(UINT)graphics::eCBType::Perspective];

	// DirectX 11은 XMMATRIX를 Transpose해서 넘겨주어야 함
	renderer::PerspectiveCB data{
		XMMatrixTranspose(mWorldMatrix),
		XMMatrixTranspose(mViewMatrix),
		XMMatrixTranspose(mProjectionMatrix),
	};

	cb->SetData(&data);

	cb->Bind(graphics::eShaderStage::VS);
}