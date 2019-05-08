#include "MiniginPCH.h"
#include "ChangeSceneCommand.h"
#include "SceneManager.h"


dae::ChangeSceneCommand::ChangeSceneCommand(int newScene)
	:m_newScene(newScene)
{
}


dae::ChangeSceneCommand::~ChangeSceneCommand()
{
}

void dae::ChangeSceneCommand::Execute(std::shared_ptr<dae::GameObject> gameObject)
{
	dae::SceneManager::GetInstance().SetActiveScene(m_newScene);
}
