#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


void dae::SceneManager::Initialize()
{
	m_Scenes[0]->LoadScene();
}

void dae::SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	m_Scenes.push_back(scene);
	scene->SetupScene();
	scene->Initialize();
}

void dae::SceneManager::SetActiveScene(int sceneId)
{
	if (sceneId >= 0 && sceneId < (int)m_Scenes.size())
	{
		m_Scenes[m_ActiveScene]->UnloadScene();
		m_ActiveScene = sceneId;
		m_Scenes[m_ActiveScene]->LoadScene();
	}
}

void dae::SceneManager::Update()
{
	//only check needed here because setactivescene() makes sure m_activeScene is in range
	if (m_Scenes.size() > 0)
		m_Scenes[m_ActiveScene]->Update();
}

void dae::SceneManager::Render()
{
	//only check needed here because setactivescene() makes sure m_activeScene is in range
	if (m_Scenes.size() > 0)
		m_Scenes[m_ActiveScene]->Render();
}

void dae::SceneManager::Clear()
{
	m_Scenes.clear();
}
