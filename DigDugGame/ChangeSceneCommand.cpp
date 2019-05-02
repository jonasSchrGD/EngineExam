#include "pch.h"
#include "ChangeSceneCommand.h"
#include "SceneManager.h"


ChangeSceneCommand::ChangeSceneCommand(int newScene)
	:m_newScene(newScene)
{
}


ChangeSceneCommand::~ChangeSceneCommand()
{
}

void ChangeSceneCommand::Execute(std::shared_ptr<dae::GameObject> gameObject)
{
	dae::SceneManager::GetInstance().SetActiveScene(m_newScene);
}
