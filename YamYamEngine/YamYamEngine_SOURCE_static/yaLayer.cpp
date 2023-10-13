#include "yaLayer.h"

#include "yaSceneManager.h"


namespace ya
{
	Layer::Layer() : mType(NONE)
	{
	}

	Layer::~Layer()
	{
		for (const GameObject* gameObject : mGameObjects)
		{
			delete gameObject;
			gameObject = nullptr;
		}
	}

	void Layer::LayerItemCheck(GameObject* obj)
	{
		if (obj->GetLayer() != mType)
		{
			SceneManager::GetActiveScene()->AddGameObject(obj, obj->GetLayer());
			std::erase_if(mGameObjects, [&](const auto* cmp)
			{
				return cmp == obj;
			});
		}
	}

	void Layer::Initialize()
	{
		for(int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Initialize();
			LayerItemCheck(mGameObjects[i]);
		}
	}

	void Layer::Update()
	{
		for(int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Update();
			LayerItemCheck(mGameObjects[i]);
		}
	}

	void Layer::LateUpdate()
	{
		for(int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->LateUpdate();
			LayerItemCheck(mGameObjects[i]);
		}
	}

	void Layer::Render()
	{
		for(int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Render();
			LayerItemCheck(mGameObjects[i]);
		}
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		mGameObjects.push_back(gameObject);
	}
}
