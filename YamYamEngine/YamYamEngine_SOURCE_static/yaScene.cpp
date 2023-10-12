#include "yaScene.h"

#include "yaCollisionManager.h"


namespace ya
{
    Scene::Scene()
    {
        for (int i = 0; i < LAYER_MAX; ++i)
        {
	        mLayers[i].SetLayerType(static_cast<LAYER>(i));
        }
    }

    Scene::~Scene()
    {
    }

    void Scene::Initialize()
    {
        for (Layer& layer : mLayers)
        {
            layer.Initialize();
        }
    }

    void Scene::Update()
    {
        for (Layer& layer : mLayers)
        {
            layer.Update();
        }
    }

    void Scene::LateUpdate()
    {
        for (Layer& layer : mLayers)
        {
            layer.LateUpdate();
        }
    }

    void Scene::Render()
    {
        for (Layer& layer : mLayers)
        {
            layer.Render();
        }
    }

    void Scene::AddGameObject(GameObject* gameObject, UINT layerIndex)
    {
        mLayers[layerIndex].AddGameObject(gameObject);
        gameObject->SetLayer(static_cast<LAYER>(layerIndex));
    }
}