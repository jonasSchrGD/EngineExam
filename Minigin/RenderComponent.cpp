#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"


dae::RenderComponent::RenderComponent(int width, int height)
	:m_AddedToRenderer(false)
	,m_Width(width)
	,m_Height(height)
{
}
void dae::RenderComponent::SetTexture(const std::string& filename)
{
	mTexture = ResourceManager::GetInstance().LoadTexture(filename);
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
