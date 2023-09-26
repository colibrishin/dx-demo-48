#pragma once
#include "yaScene.h"

namespace ya
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();

		template <typename T>
		static bool CreateScene(const std::wstring name)
		{
			std::map<std::wstring, Scene*>::iterator iter
				= mScenes.find(name);

			if (iter != mScenes.end())
				return false;

			T* scene = new T();
			mScenes.insert(std::make_pair(name, scene));
			scene->Initialize();
			
			return true;
		}
		static Scene* LoadScene(const std::wstring name);

	private:
		static Scene* mActiveScene;
		static std::map<std::wstring, Scene*> mScenes;
	};
}
