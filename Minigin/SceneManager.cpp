#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


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
