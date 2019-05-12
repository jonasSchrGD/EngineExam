#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include "CollisionHandler.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "Time.h"
#include "ContentManager.h"

void dae::Minigin::Run()
{
	// tell the resource manager where he can find the game data
	ContentManager::GetInstance().Initialize("../Data/");

	InitializeCustomLoaders();

	Initialize();

	LoadGame();

	{
		auto OldT = std::chrono::high_resolution_clock::now();
		float deltaTime{};
		float& elapsed = Time::GetInstance().m_FrameTime;
		float msPerFrame = Time::GetInstance().m_MsPerFrame;;//value only needs to be changed in time class

		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& collision = CollisionHandler::GetInstance();

		sceneManager.Initialize();

		bool doContinue = true;
		while (doContinue)
		{
			auto currentT = std::chrono::high_resolution_clock::now();
			elapsed = (float)std::chrono::duration_cast<std::chrono::microseconds>(currentT - OldT).count() / 1000000;
			OldT = currentT;
			deltaTime += elapsed;

			doContinue = input.ProcessInput();

			//update
			while (deltaTime >= msPerFrame)
			{
				sceneManager.Update();
				collision.Update();
				deltaTime -= msPerFrame;
			}

			renderer.Render();
		}

		ContentManager::GetInstance().Destroy();
		sceneManager.Clear();
	}

	Cleanup();
}

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

		window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		560,
		720,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}
