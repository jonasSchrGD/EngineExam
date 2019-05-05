#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "FPSComponent.h"
#include "SpriteRenderer.h"
#include "RenderComponent.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) 
	: mName(name)
{
}

void dae::Scene::AddFpsComponent()
{
	auto go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<FPSComponent>());
	go->SetPosition(5, 5);
	Add(go);
}

void dae::Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	mObjects.push_back(object);
}

void dae::Scene::Update()
{
	m_RenderComponents.clear();
	for(auto gameObject : mObjects)
	{
		gameObject->Update();

		//todo: find better solution?
		std::shared_ptr<BaseRenderComponent> renderComp = std::dynamic_pointer_cast<GameObject>(gameObject)->GetComponent<BaseRenderComponent>(); // TextRenderComponent
		if (renderComp)
			m_RenderComponents.push_back(renderComp);
	}
}

void dae::Scene::Render() const
{
	for (auto renderComponent : m_RenderComponents)
	{
		renderComponent->Render();
	}
}

