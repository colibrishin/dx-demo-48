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
			LayerItemCheck(mGameObjects[i]);
			mGameObjects[i]->Initialize();
		}
	}

	void Layer::Update()
	{
		for(int i = 0; i < mGameObjects.size(); i++)
		{
			LayerItemCheck(mGameObjects[i]);
			mGameObjects[i]->Update();
		}
	}

	void Layer::LateUpdate()
	{
		for(int i = 0; i < mGameObjects.size(); i++)
		{
			LayerItemCheck(mGameObjects[i]);
			mGameObjects[i]->LateUpdate();
		}
	}

	void Layer::Render()
	{
		for(int i = 0; i < mGameObjects.size(); i++)
		{
			LayerItemCheck(mGameObjects[i]);
			mGameObjects[i]->Render();
		}
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		mGameObjects.push_back(gameObject);
	}
}
