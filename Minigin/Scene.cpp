#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "FPSComponent.h"
#include "BaseRenderComponent.h"
#include "RenderCompObserver.h"
#include <algorithm>

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
	object->SetScene(shared_from_this());

	auto go = std::dynamic_pointer_cast<GameObject>(object);
	if (object)
		go->AddObServer(m_Observer);

	if (m_IsInitialized)
	{
		m_ObjectsToAdd.push_back(object);
		object->Initialize();
		object->Load();
	}
	else
		mObjects.push_back(object);
}

void dae::Scene::Remove(const std::shared_ptr<SceneObject>& object)
{
	m_ObjectsToRemove.push_back(object);
}

void dae::Scene::Update()
{
	for (auto gameObject : m_ObjectsToAdd)
	{
		mObjects.push_back(gameObject);
	}
	m_ObjectsToAdd.clear();

	for(auto gameObject : mObjects)
	{
		gameObject->Update();
	}

	DoRemove();
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
	if (!m_IsInitialized)
	{
		AddFpsComponent();
		m_IsInitialized = true;

		for (auto gameObject : mObjects)
		{
			gameObject->Initialize();
		}
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

void dae::Scene::DoRemove()
{
	for (auto gameObject : m_ObjectsToRemove)
	{
		auto rendercomp = std::static_pointer_cast<GameObject>(gameObject)->GetComponent<BaseRenderComponent>();

		auto obj = std::remove(mObjects.begin(), mObjects.end(), gameObject);
		if (obj != mObjects.end())
			mObjects.erase(obj);

		auto rend = std::remove(m_RenderComponents.begin(), m_RenderComponents.end(), rendercomp);
		if (rend != m_RenderComponents.end())
			m_RenderComponents.erase(rend);
	}
	m_ObjectsToRemove.clear();
}
