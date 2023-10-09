#pragma once
#include "yaScene.h"
#include "yaTile.h"
#include <d3d11.h>

namespace ya
{
#define LEFT_TOP_Y 40.f
#define LEFT_TOP_X 20.f

#define RIGHT_BOTTOM_Y 560.f
#define RIGHT_BOTTOM_X 620.f


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

		void ID3D11DeviceContext::SetViewport(const D3D11_VIEWPORT* pViewport);

	private:
		std::vector<Tile*> mTiles;

	};
}
