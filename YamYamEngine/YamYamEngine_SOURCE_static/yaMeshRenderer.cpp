#include "yaMeshRenderer.h"
#include "yaGameObject.h"
#include "yaRenderer.h"
#include "yaTransform.h"

namespace ya
{
	MeshRenderer::MeshRenderer()
		: Component(COMPONENTTYPE::MESH), mMesh(nullptr), mShader(nullptr), mTexture(nullptr), mColor(Vector4(0.f, 0.f, 0.f, 1.f))
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::Initialize()
	{
		
	}

	void MeshRenderer::Update()
	{

	}

	void MeshRenderer::LateUpdate()
	{

	}

	void MeshRenderer::Render()
	{
		if(!IsEnabled())
		{
			return;
		}

		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();

		if(mTexture != nullptr)
		{
			mTexture->Update();
		}

		mShader->Update();
		mMesh->Render();
	}
}

