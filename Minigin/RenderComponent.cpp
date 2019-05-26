#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "ContentManager.h"


dae::RenderComponent::RenderComponent(int width, int height)
	:m_Width(width)
	,m_Height(height)
{
}
void dae::RenderComponent::SetTexture(const std::string& filename)
{
	mTexture = ContentManager::GetInstance().Load<Texture2D>(filename);
	if(m_Width == 0 || m_Height == 0)
	{
		SDL_QueryTexture(mTexture->GetSDLTexture(), nullptr, nullptr, &m_Width, &m_Height);
	}
}

void dae::RenderComponent::Render() const
{
	if (mTexture != nullptr)
	{
		const auto pos = GetGameObject()->GetTransform().lock()->GetPosition();
		Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y, (float)m_Width, (float)m_Height);
	}
}
