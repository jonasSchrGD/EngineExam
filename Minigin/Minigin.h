#pragma once
#include "FPSComponent.h"

struct SDL_Window;
namespace dae
{
	class TextRenderComponent;
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();

	private:
		SDL_Window* window{};
		std::shared_ptr<FPSComponent> m_Fps;
	};
}