#include "yaLayer.h"


namespace ya
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
		for (GameObject* gameObject : mGameObjects)
		{
			delete gameObject;
			gameObject = nullptr;
		}
	}

	void Layer::Initialize()
	{
		for(int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Initialize();
		}
	}

	void Layer::Update()
	{
		for(int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Update();
		}
	}

	void Layer::LateUpdate()
	{
		for(int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->LateUpdate();
		}
	}

	void Layer::Render()
	{
		for(int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Render();
		}
		
		// GameObject를 돌면서 GameObject의 상태가 Dead이면 Delete
		for (std::vector<GameObject*>::iterator iter = mGameObjects.begin();
			iter != mGameObjects.end();)
		{
			if ((*iter)->GetGameObjectState() == GameObject::eState::Dead)
			{
				GameObject* deadObj = *iter;
				delete deadObj;
				deadObj = nullptr;

				iter = mGameObjects.erase(iter);
			}
			else
				iter++;
		}
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		mGameObjects.push_back(gameObject);
	}
}