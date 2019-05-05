#include "MiniginPCH.h"
#include "BaseRenderComponent.h"
#include "Renderer.h"

dae::BaseRenderComponent::BaseRenderComponent()
	:m_AddedToRenderer(false)
{
}

dae::BaseRenderComponent::~BaseRenderComponent()
{
}

void dae::BaseRenderComponent::AddToRenderer()
{
	if (!m_AddedToRenderer)
	{
		m_AddedToRenderer = true;
	}
}
