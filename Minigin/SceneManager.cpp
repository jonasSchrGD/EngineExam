#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


void dae::SceneManager::Initialize()
{
	if (!m_IsInitialized)
	{
		for (int i = 0; i < m_Scenes.size(); ++i)
		{
			m_Scenes[i]->Initialize();
		}

		m_Scenes[0]->LoadScene();
		m_IsInitialized = true;
	}
}

void dae::SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	m_Scenes.push_back(scene);
	scene->SetupScene();

	if (m_IsInitialized)
		scene->Initialize();
}

void dae::SceneManager::SetActiveScene(int sceneId)
{
	if (sceneId >= 0 && sceneId < (int)m_Scenes.size())
	{
		m_newScene = sceneId;
	}
}

void dae::SceneManager::Update()
{
	if(m_newScene != m_ActiveScene)
	{
		m_Scenes[m_ActiveScene]->UnloadScene();
		m_Scenes[m_ActiveScene]->DoRemove();
		m_ActiveScene = m_newScene;
		m_Scenes[m_ActiveScene]->LoadScene();
	}

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
