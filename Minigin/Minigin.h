#pragma once

//http://gameprogrammingpatterns.com/
//this book is the reference for patterns

struct SDL_Window;
namespace dae
{
	class Minigin
	{
	public:
		virtual ~Minigin() = default;
		virtual void Run();

	protected:
		virtual void Initialize();
		virtual void LoadGame() const = 0;
		virtual void Cleanup();
		virtual void InitializeCustomLoaders() { }

	private:
		SDL_Window* window{};
	};
}
