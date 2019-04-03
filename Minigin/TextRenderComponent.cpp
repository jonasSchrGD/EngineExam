#include "MiniginPCH.h"
#include "TextRenderComponent.h"
#include "Renderer.h"
#include "GameObject.h"

dae::TextRenderComponent::TextRenderComponent(const std::string& text, std::shared_ptr<Font> font, SDL_Color color)
	: mNeedsUpdate(true)
	, mText(text)
	, mFont(font)
	, mTexture(nullptr)
	, m_Color(color)
{
}

void dae::TextRenderComponent::SetText(const std::string& text)
{
	mText = text;
	mNeedsUpdate = true;
}

void dae::TextRenderComponent::Update()
{
	AddToRenderer();

	if (mNeedsUpdate)
	{
		//const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(mFont->GetFont(), mText.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		mTexture = std::make_shared<Texture2D>(texture);
	}
}

void dae::TextRenderComponent::Render() const
{
	if (mTexture != nullptr)
	{
		const auto pos = GetGameObject()->GetTransform().lock()->GetPosition();
		Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
	}
}
