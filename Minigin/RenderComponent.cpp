#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"


dae::RenderComponent::RenderComponent()
	:m_AddedToRenderer(false)
{
}
void dae::RenderComponent::SetTexture(const std::string& filename)
{
	mTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::Render() const
{
	if (mTexture != nullptr)
	{
		const auto pos = GetGameObject()->GetTransform().lock()->GetPosition();
		Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
	}
}
