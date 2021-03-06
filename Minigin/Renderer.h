#pragma once
#include "Singleton.h"
#include "TextRenderComponent.h"

#include <vector>

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

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect) const;

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
	};
}

