#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "FPSComponent.h"
#include "BaseRenderComponent.h"
#include "RenderCompObserver.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name)
	: mName(name)
	, m_IsInitialized(false)
	, m_RenderComponents()
	, m_Observer(std::make_shared<RenderCompObserver>(m_RenderComponents))
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
	object->SetScene(shared_from_this());

	auto go = std::dynamic_pointer_cast<GameObject>(object);
	if (object)
		go->AddObServer(m_Observer);

	if (m_IsInitialized)
		object->Initialize();
}

void dae::Scene::Update()
{
	for(auto gameObject : mObjects)
	{
		gameObject->Update();
	}
}

void dae::Scene::Render() const
{
	for (auto renderComponent : m_RenderComponents)
	{
		renderComponent->Render();
	}
}

void dae::Scene::Initialize()
{
	AddFpsComponent();
	for (auto gameObject : mObjects)
	{
		gameObject->Initialize();

		//gameobject already notified if a rendercomponent has been added
		std::shared_ptr<BaseRenderComponent> renderComp = std::dynamic_pointer_cast<GameObject>(gameObject)->GetComponent<BaseRenderComponent>();
		if (renderComp)
			m_RenderComponents.push_back(renderComp);
	}
}

void dae::Scene::LoadScene()
{
	for (auto object : mObjects)
	{
		object->Load();
	}
}

void dae::Scene::UnloadScene()
{
	for (auto object : mObjects)
	{
		object->Unload();
	}
}