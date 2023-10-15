#pragma once
#include "yaPlayer.h"
#include "yaScene.h"
#include "yaTile.h"

namespace ya
{
#define LEFT_TOP_Y 0.f
#define LEFT_TOP_X 0.f

#define RIGHT_BOTTOM_Y 900.f
#define RIGHT_BOTTOM_X 1600.f

	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void Load();

	private:
		std::vector<Tile*> mTiles;
		Player* mPlayer;
	};
}
