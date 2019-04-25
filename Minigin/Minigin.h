#pragma once
#include "Time.h"

struct SDL_Window;
namespace dae
{
	class TextRenderComponent;
	class Minigin
	{
	public:
		virtual ~Minigin() = default;
		virtual void Run();

	protected:
		virtual void Initialize();
		virtual void LoadGame() const = 0;
		virtual void Cleanup();

	private:
		SDL_Window* window{};
	};
}
