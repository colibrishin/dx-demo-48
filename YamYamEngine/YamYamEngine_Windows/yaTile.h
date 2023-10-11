#pragma once
#include "yaGameObject.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"

namespace ya
{
	using namespace math;
	
	class Tile : public GameObject
	{
	public:

		enum class eTileType
		{
			Triangle,
			Square,
			Circle,
			End,
		};

		static UINT mSelectedX;
		static UINT mSelectedY;

		Tile();
		~Tile();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		void SetSourceTileIdx(int x, int y) { mSourceIndexX = x;  mSourceIndexY = y; }
		void SetTileIdx(int x, int y) { mIndexX = x;  mIndexY = y; }
		Vector3 GetSourceTileIdx() { return Vector3(mSourceIndexX, mSourceIndexY, 1); }
		Vector3 GetTileIdx() { return Vector3(mIndexX, mIndexY, 1); }
		void SetTile(int x, int y);

		eTileType GetType() { return mType; }
		void SetType(eTileType type) { mType = type; }

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		UINT GetTileIndexX() const { return mIndexX; }
		UINT GetTileIndexY() const { return mIndexY; }

		void SetCircle(Tile* tile);
		void SetTriangle(Tile* tile);
		void SetSquare(Tile* tile);


	private:
		class MeshRenderer* mMeshRenderer;
		UINT mSourceIndexX;
		UINT mSourceIndexY;

		UINT mIndexX;
		UINT mIndexY;

		eTileType mType;

	};
}

