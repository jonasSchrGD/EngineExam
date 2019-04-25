#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include "CollisionHandler.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"

void dae::Minigin::Run()
{
	// tell the resource manager where he can find the game data
	dae::ResourceManager::GetInstance().Init("../Data/");

	Initialize();

	LoadGame();

	{
		auto OldT = std::chrono::high_resolution_clock::now();
		float deltaTime{};
		float& elapsed = Time::GetInstance().m_FrameTime;
		float msPerFrame = dae::Time::GetInstance().m_MsPerFrame;;//nu hoeft de waarde alleen in de time class aangepast te worden

		auto& renderer = dae::Renderer::GetInstance();
		auto& sceneManager = dae::SceneManager::GetInstance();
		auto& input = dae::InputManager::GetInstance();
		auto& collision = CollisionHandler::GetInstance();

		bool doContinue = true;
		while (doContinue)
		{
			auto currentT = std::chrono::high_resolution_clock::now();
			elapsed = (float)std::chrono::duration_cast<std::chrono::milliseconds>(currentT - OldT).count() / 1000.f;
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
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	dae::Renderer::GetInstance().Init(window);
}

void dae::Minigin::Cleanup()
{
	dae::Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}
