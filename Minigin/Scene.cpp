#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "FPSComponent.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) 
	: mName(name)
{
}

dae::Scene::~Scene()
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
	for(auto gameObject : mObjects)
	{
		gameObject->Update();
	}
}

void dae::Scene::Render() const
{
}

