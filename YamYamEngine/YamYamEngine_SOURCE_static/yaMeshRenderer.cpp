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

		//// 자를 타일의 가로 세로 사이즈
		//if (mbTile)
		//{
		//	GameObject* gameObj = GetOwner();
		//	Transform* tr = gameObj->GetComponent<Transform>();
		//	mTexture->Render(hdc
		//		, tr->GetPosition()
		//		, Vector2(TILE_WIDTH, TILE_HEIGHT)

		//		// cut area
		//		, Vector2(mTileIndexX * TILE_WIDTH
		//			, mTileIndexY * TILE_HEIGHT)
		//		, Vector2(TILE_WIDTH, TILE_HEIGHT)
		//		, Vector2::Zero
		//		, mScale
		//		,
		//}

		mShader->Update();
		mMesh->Render();
	}
}

