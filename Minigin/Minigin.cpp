#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "TextRenderComponent.h"
#include "RenderComponent.h"
#include "Time.h"


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

	Renderer::GetInstance().Init(window);

	m_Fps = std::make_shared<FPSComponent>();
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	auto rendercomp = std::make_shared<RenderComponent>();
	rendercomp->SetTexture("background.jpg");
	go->AddComponent(rendercomp);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	rendercomp = std::make_shared<RenderComponent>();
	rendercomp->SetTexture("logo.png");
	go->AddComponent(rendercomp);
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComp = std::make_shared<GameObject>();
	auto to = std::make_shared<TextRenderComponent>("Programming 4 Assignment", font);
	textComp->SetPosition(80, 20);
	textComp->AddComponent(to);
	scene.Add(textComp);

	go = std::make_shared<GameObject>();
	go->AddComponent(m_Fps);
	go->SetPosition(5, 5);
	scene.Add(go);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	Initialize();

	LoadGame();

	{
		auto OldT = std::chrono::high_resolution_clock::now();
		float deltaTime{};
		float& elapsed = Time::GetInstance().m_FrameTime;
		const float& msPerFrame = Time::GetInstance().m_MsPerFrame;

		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		
		bool doContinue = true;
		while (doContinue)
		{
			auto currentT = std::chrono::high_resolution_clock::now();
			elapsed = (float)std::chrono::duration_cast<std::chrono::milliseconds>(currentT - OldT).count() / 1000.f;
			OldT = currentT;
			deltaTime += elapsed;

			doContinue = input.ProcessInput();

			//update
			while(deltaTime >= msPerFrame)
			{
				sceneManager.Update();
				deltaTime -= msPerFrame;
			}

			renderer.Render();
		}
	}

	Cleanup();
}
