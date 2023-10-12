#pragma once
#include "yaEntity.h"
#include "yaGameObject.h"

namespace ya
{
	class Layer : public Entity
	{
	public:
		Layer();
		~Layer() override;

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void AddGameObject(GameObject* gameObject);

		std::vector<GameObject*>& GetGameObjects() { return mGameObjects; }

	private:
		friend class Scene;
		void SetLayerType(LAYER type) { mType = type; }
		void LayerItemCheck(GameObject* obj);

		LAYER mType;
		std::vector<GameObject*> mGameObjects;
	};
}
