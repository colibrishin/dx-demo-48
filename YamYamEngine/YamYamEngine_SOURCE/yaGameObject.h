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

		friend static __forceinline void Destroy(GameObject* gameObject);

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

		// Component 삭제해주는 함수
		template <typename T>
		void DeleteComponent()
		{
			T* comp = nullptr;

			for (std::vector<Component*>::iterator iter = mComponents.begin();
				iter != mComponents.end(); iter++)
			{
				comp = dynamic_cast<T*>(*iter);

				if (comp != nullptr)
				{
					delete comp;
					comp = nullptr;
					iter = mComponents.erase(iter);
					return;
				}
			}
		}

		std::vector<Component*>& GetComponents() { return mComponents; }
		std::vector<Script*>& GetScripts() { return mScripts; }
		eState GetGameObjectState() { return mState; }

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetLayer(LAYER LayerType) { mLayer = LayerType; }
		LAYER GetLayer() { return mLayer; }


	private:
		eState mState;
		std::vector<Component*> mComponents;
		std::vector<Script*> mScripts;
		LAYER mLayer;
		void death() { mState = eState::Dead; }
		
	};

	// 죽은 게임 오브젝트의 메모리룰 제거해주는 함수
	static __forceinline void Destroy(GameObject* gameObject)
	{
		gameObject->death();
	}
}
