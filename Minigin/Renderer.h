#pragma once
#include "Singleton.h"
#include "TextRenderComponent.h"

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	class BaseRenderComponent;

	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* mRenderer = nullptr;

		//creation of rendercomponents should not happen verry often during game itself
		std::vector<std::weak_ptr<BaseRenderComponent>> m_RenderComponents;

	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void AddRenderComponent(std::shared_ptr<BaseRenderComponent> component);

		void RemoveRenderComponent(std::weak_ptr<BaseRenderComponent> component);

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
	};
}

