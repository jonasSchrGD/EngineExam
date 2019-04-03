#include "MiniginPCH.h"
#include "BaseRenderComponent.h"
#include "Renderer.h"

dae::BaseRenderComponent::BaseRenderComponent()
	:m_AddedToRenderer(false)
{

}

dae::BaseRenderComponent::~BaseRenderComponent()
{
	Renderer::GetInstance().RemoveRenderComponent(weak_from_this());
}

void dae::BaseRenderComponent::AddToRenderer()
{
	if (!m_AddedToRenderer)
	{
		Renderer::GetInstance().AddRenderComponent(shared_from_this());
		m_AddedToRenderer = true;
	}
}
