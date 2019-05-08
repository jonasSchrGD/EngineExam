#include "MiniginPCH.h"
#include "RenderCompObserver.h"
#include "BaseRenderComponent.h"
#include "GameObject.h"

dae::RenderCompObserver::RenderCompObserver(std::vector<std::shared_ptr<BaseRenderComponent>>& renderComponents):
	m_RenderComponents(renderComponents)
{
}

void dae::RenderCompObserver::Notify(std::shared_ptr<GameObject> go)
{
	m_RenderComponents.push_back(go->GetComponent<BaseRenderComponent>());
}

