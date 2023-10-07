#include "yaApplication.h"

#include "yaCamera.h"
#include "yaGraphicsDevice_DX11.h"

#include "yaInput.h"
#include "yaTime.h"
#include "yaRenderer.h"
#include "yaSceneManager.h"
#include "yaCollisionManager.h"

using namespace ya::graphics;

namespace ya
{
	Application::~Application()
	{
		renderer::Release();
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Initialize()
	{
		Camera::Initialize();
		Time::Initialize();
		Input::Initialize();

		renderer::Initialize();
		CollisionManager::Initialize();
		SceneManager::Initialize();
	}

	void Application::Update()
	{
		Time::Update();
		Camera::Update();
		Input::Update();
		CollisionManager::Update();
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{

	}

	void Application::Render()
	{
		graphicsDevice->Clear();
		graphicsDevice->AdjustViewport();

		Time::Render();
		CollisionManager::Render();
		SceneManager::Render();

		//graphicsDevice->Render();
		graphicsDevice->Present();
	}

	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicsDevice == nullptr)
		{
			mHwnd = hwnd;
			mWidth = width;
			mHegith = height;

			graphicsDevice = std::make_unique<GraphicsDevice_DX11>();
			ya::graphics::GetDevice() = graphicsDevice.get();
			//ya::device = graphicsDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}
}
