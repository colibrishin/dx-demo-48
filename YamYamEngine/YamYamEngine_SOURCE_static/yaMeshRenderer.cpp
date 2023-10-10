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

		// 자를 타일의 가로 세로 사이즈
		if (mbTile)
		{
			GameObject* gameObj = GetOwner();
			Transform* tr = gameObj->GetComponent<Transform>();
			mTexture->Render(tr->GetPosition()
				, Vector3(TILE_WIDTH, TILE_HEIGHT)

				// cut area
				, Vector3(mTileIndexX * TILE_WIDTH
					, mTileIndexY * TILE_HEIGHT)
				, Vector3(TILE_WIDTH, TILE_HEIGHT)
				, Vector3::Zero
				, mScale
			/*, tr->GetRotation()*/);
		}
		else
		{
			GameObject* gameObj = GetOwner();
			Transform* tr = gameObj->GetComponent<Transform>();
			mTexture->Render(
				tr->GetPosition()
				, Vector2(mTexture->GetWidth(), mTexture->GetHeight())
				, Vector2(0.0f, 0.0f)
				, Vector2(mTexture->GetWidth(), mTexture->GetHeight())
				, Vector2::Zero
				, mScale
			);
		}

		if(mTexture != nullptr)
		{
			mTexture->Update();
		}

		mShader->Update();
		mMesh->Render();
	}
}

