#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"


dae::RenderComponent::RenderComponent()
{
}

dae::RenderComponent::~RenderComponent()
{
}

void dae::RenderComponent::Update()
{
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	mTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::Render() const
{
	if (mTexture)
	{
		const auto pos = GetGameObject()->GetPosition();
		Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
	}
}
