#pragma once
#include "yaSceneManager.h"
#include "yaPlayScene.h"


//#ifdef  _DEBUG
//#pragma comment(lib, "..\\x64\\Debug\\YamYamEngine_Windows.lib")
//#else
//#pragma comment(lib, "..\\x64\\Release\\YamYamEngine_Windows.lib")
//#endif //  _DEBUG

namespace ya
{
	void InitializeScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");

		SceneManager::LoadScene(L"PlayScene");
	}
}