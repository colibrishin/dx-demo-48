#pragma once
#include "yaEntity.h"
#include "yaComponent.h"
#include "yaScript.h"


namespace ya
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		template <typename T>
		T* AddComponent()
		{
			T* component = new T();
			Component* comp = dynamic_cast<Component*>(component);
			if (comp)
			{
				int myOrder = comp->GetUpdateOrder();
				mComponents[myOrder] = comp;
				mComponents[myOrder]->mOwner = this;
			}

			Script* script = dynamic_cast<Script*>(component);
			if (script != nullptr)
			{
				mScripts.push_back(script);
				script->SetOwner(this);
			}

			return component;
		}

		template <typename T>
		T* GetComponent()
		{
			T* component;
			for (auto c : mComponents)
			{
				component = dynamic_cast<T*>(c);

				if (component != nullptr)
					return component;
			}

			return nullptr;
		}
		std::vector<Component*>& GetComponents() { return mComponents; }
		std::vector<Script*>& GetScripts() { return mScripts; }

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		eState mState;
		std::vector<Component*> mComponents;
		std::vector<Script*> mScripts;
	};
}
