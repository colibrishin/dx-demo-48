#pragma once
#include "yaGameObject.h"

namespace ya
{
	using namespace math;
	
	class Tile : public GameObject
	{
	public:

		enum class eType
		{
			// 포탈 부착이 가능한 타일

			// floor 같이 충돌체가 없는 타일
			None,
			// 부서지며 충돌체가 있는 타일
			Crack,
			// 부서지지는 않지만 충돌체는 있는 타입
			Uncrushable,

			End,
		};

		static UINT mSelectedX;
		static UINT mSelectedY;

		Tile();
		~Tile();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		void SetSourceTileIdx(int x, int y, int z) { mSourceIndexX = x;  mSourceIndexY = y; }
		void SetTileIdx(int x, int y, int z) { mIndexX = x;  mIndexY = y; }
		Vector3 GetSourceTileIdx() { return Vector3(mSourceIndexX, mSourceIndexY, 1); }
		Vector3 GetTileIdx() { return Vector3(mIndexX, mIndexY, 1); }
		void SetTile(int x, int y, int z);

		eType GetType() { return mType; }
		void SetType(eType type) { mType = type; }

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		UINT GetTileIndexX() const { return mIndexX; }
		UINT GetTileIndexY() const { return mIndexY; }


		

	private:
		class MeshRenderer* mMeshRenderer;
		UINT mSourceIndexX;
		UINT mSourceIndexY;
		UINT mSourceIndexZ;

		UINT mIndexX;
		UINT mIndexY;
		UINT mIndexZ;

		eType mType;

	};
}

