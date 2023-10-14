#pragma once
#include "yaGameObject.h"
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
			Floor,
			End,
		};

		static int mSelectedX;
		static int mSelectedY;

		Tile();
		~Tile();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		void SetTileIdx(int x, int y) { mIndexX = x;  mIndexY = y; }
		Vector3 GetTileIdx() { return Vector3(mIndexX, mIndexY, 1); }
		void SetTile(int x, int y);

		eTileType GetType() { return mType; }
		void SetType(eTileType type) { mType = type; }

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		int GetTileIndexX() const { return mIndexX; }
		int GetTileIndexY() const { return mIndexY; }

		void SetCircle(Tile* tile);
		void SetTriangle(Tile* tile);
		void SetSquare(Tile* tile);
		void SetFloor(Tile* tile);

		//Transform* GetPos() { return mTransform; }


	private:
		class MeshRenderer* mMeshRenderer;
		class Transform* mTransform;
		int mIndexX;
		int mIndexY;

		eTileType mType;

	};
}

