#include "yaGameObject.h"


namespace ya
{
	GameObject::GameObject()
		: mState(eState::Active),
		mLayer(LAYER::NONE)
	{
		mComponents.resize(COMPONENTTYPE::END);
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			delete comp;
			comp = nullptr;
		}

		for (Script* script : mScripts)
		{
			delete script;
			script = nullptr;
		}
	}

	void GameObject::Initialize()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Initialize();
		}

		for (Script* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->Initialize();
		}
	}
	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Update();
		}

		for (Script* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->Update();
		}
	}
	void GameObject::LateUpdate()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->LateUpdate();
		}

		for (Script* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->LateUpdate();
		}
	}

	void GameObject::Render()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->Render();
		}

		for (Script* script : mScripts)
		{
			if (script == nullptr)
				continue;

			script->Render();
		}
	}

	void GameObject::OnCollisionEnter(Collider* other)
	{
	}
	void GameObject::OnCollisionStay(Collider* other)
	{
	}
	void GameObject::OnCollisionExit(Collider* other)
	{
	}
}
