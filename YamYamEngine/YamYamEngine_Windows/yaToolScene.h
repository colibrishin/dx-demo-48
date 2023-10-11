#pragma once
#include "yaScene.h"
#include "yaTile.h"

namespace ya
{
#define LEFT_TOP_Y 0.f
#define LEFT_TOP_X 0.f

#define RIGHT_BOTTOM_Y 900.f
#define RIGHT_BOTTOM_X 1600.f


	class ToolScene : public Scene
	{
	public:

		ToolScene();
		virtual ~ToolScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render( ) override;

		void PushTile(Tile* tile) { mTiles.push_back(tile); }

		void Save();
		void Load();

		virtual void Enter();
		virtual void Exit();


	private:
		std::vector<Tile*> mTiles;

	};
}
