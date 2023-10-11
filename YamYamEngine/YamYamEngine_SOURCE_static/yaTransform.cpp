#include "yaTransform.h"
#include "yaGraphicsDevice_DX11.h"
#include "yaRenderer.h"

namespace ya
{

	Transform::Transform()
		: Component(COMPONENTTYPE::TRANSFORM)
	{

	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
	}

	void Transform::LateUpdate()
	{
	}

	void Transform::Render()
	{
	}

	void Transform::SetConstantBuffer()
	{
		if(!IsEnabled())
		{
			return;
		}

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)graphics::eCBType::Transform];
		
		renderer::TransformCB data = {};
		data.pos = mPosition;
		data.scale = mScale;
		data.rotMatrix = XMMatrixTranspose(XMMatrixRotationQuaternion(mRotation));
		cb->SetData(&data);

		cb->Bind(graphics::eShaderStage::VS);
	}

}