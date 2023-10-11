#include "yaTile.h"
#include "yaTile.h"
#include "yaMeshRenderer.h"
#include "yaCollider.h"
//#include "yaTexture.h"
#include "yaResources.h"
#include "yaCollisionManager.h"
#include "yaToolScene.h"


namespace ya
{
	UINT Tile::mSelectedX = 0;
	UINT Tile::mSelectedY = 0;


	Tile::Tile()
		: mMeshRenderer(nullptr)
		, mSourceIndexX(0)
		, mSourceIndexY(0)
		, mIndexX(0)
		, mIndexY(0)
		, mType(eTileType::Square)

	{
		AddComponent<Transform>();
		AddComponent<Collider>();

		mMeshRenderer = AddComponent<MeshRenderer>();

		mMeshRenderer->SetShader(Resources::Find<Shader>(L"TextureShader"));

		Transform* tr = GetComponent<Transform>();
		tr->SetPosition({ 1.0f, 1.0f, 1.0f });
		tr->SetScale(Vector3::One);

		Collider* collider = GetComponent<Collider>();
		collider->SetSize(Vector3::One);

	}

	Tile::~Tile()
	{
	}

	void Tile::Initialize()
	{
		GameObject::Initialize();
	}

	void Tile::Update()
	{
		GameObject::Update();
	}

	void Tile::Render()
	{
		GameObject::Render();
	}

	void Tile::SetTile(int x, int y)
	{
		mMeshRenderer->SetTile(x, y);
	}

	void Tile::OnCollisionEnter(Collider* other)
	{
	}
	void Tile::OnCollisionStay(Collider* other)
	{

	}
	void Tile::OnCollisionExit(Collider* other)
	{

	}

	void Tile::SetCircle(Tile* tile)
	{
		tile->mMeshRenderer->SetTexture(Resources::Find<Texture>(L"Tile_0"));
		tile->mMeshRenderer->SetMesh(Resources::Find<Mesh>(L"SquareMesh"));
		//tile->mMeshRenderer->SetShader(Resources::Find<Shader>(L"ColorShader"));
	}

	void Tile::SetTriangle(Tile* tile)
	{
		tile->mMeshRenderer->SetTexture(Resources::Find<Texture>(L"Tile_2"));
		tile->mMeshRenderer->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
	}

	void Tile::SetSquare(Tile* tile)
	{
		tile->mMeshRenderer->SetTexture(Resources::Find<Texture>(L"Tile_1"));
		tile->mMeshRenderer->SetMesh(Resources::Find<Mesh>(L"SquareMesh"));
	}


}