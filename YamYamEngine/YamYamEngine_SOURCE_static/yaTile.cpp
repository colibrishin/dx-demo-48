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
		, mType(eType::None)

	{

	}

	Tile::~Tile()
	{
	}

	void Tile::Initialize()
	{
		mMeshRenderer = AddComponent<MeshRenderer>();
		//AddComponent<Collider>();

		// 타일 주석
		ya::Texture* Tile_
			= ya::Resources::Find<ya::Texture>(L"Tile");

		mMeshRenderer->SetImage(Tile_);
		mMeshRenderer->SetScale(Vector3(1.0f, 1.0f));
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
		if (other->GetOwner()->GetLayer() == LAYER::ATTACK)
		{
			// 부서지는 타일의 경우 콜라이더 컴포넌트를 Delete 해주는 함수가 필요
			// 충돌하게 되면 어떤 타일로 바뀌게 되는지 SetSourceTileIdx로 지정
			// 부서지게 되면 타일의 타입을 None으로 바꿔줌
			if (this->GetType() == eType::Crack)
			{
				if (this->GetSourceTileIdx() == Vector3(0, 0, 1) ||
					this->GetSourceTileIdx() == Vector3(1, 0, 1) ||
					this->GetSourceTileIdx() == Vector3(2, 0, 1))
				{
					this->SetSourceTileIdx(0, 1, 1);
					this->DeleteComponent<Collider>();
					mMeshRenderer->SetTile(0, 1);
					this->SetType(eType::None);
				}

				else if (this->GetSourceTileIdx() == Vector3(3, 2, 1) ||
					this->GetSourceTileIdx() == Vector3(4, 2, 1))
				{
					this->SetSourceTileIdx(1, 1, 1);
					this->DeleteComponent<Collider>();
					mMeshRenderer->SetTile(1, 1);
					this->SetType(eType::None);
				}

				else if (this->GetSourceTileIdx() == Vector3(3, 0, 1) ||
					this->GetSourceTileIdx() == Vector3(4, 0, 1))
				{
					this->SetSourceTileIdx(3, 4, 1);
					this->DeleteComponent<Collider>();
					mMeshRenderer->SetTile(3, 4);
					this->SetType(eType::None);
				}

			}
			else if (this->GetType() == eType::Uncrushable)
			{

			}
		}
	}
	void Tile::OnCollisionStay(Collider* other)
	{

	}
	void Tile::OnCollisionExit(Collider* other)
	{

	}


}