#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "Texture2D.h"
#include "BaseRenderComponent.h"
#include <algorithm>

void dae::Renderer::Init(SDL_Window * window)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void dae::Renderer::Render()
{
	SDL_RenderClear(mRenderer);

	for (auto renderComponent : m_RenderComponents)
	{
		renderComponent.lock()->Render();
	}

	SDL_RenderPresent(mRenderer);
}

void dae::Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
}

void dae::Renderer::AddRenderComponent(std::shared_ptr<BaseRenderComponent> component)
{
	m_RenderComponents.push_back(component);
}

void dae::Renderer::RemoveRenderComponent(std::weak_ptr<BaseRenderComponent> component)
{
	m_RenderComponents.erase(std::remove_if(m_RenderComponents.begin(), m_RenderComponents.end(), [component](std::weak_ptr<BaseRenderComponent> it) {return  it.lock() == component.lock(); }));
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect) const
{
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dstRect);
}
