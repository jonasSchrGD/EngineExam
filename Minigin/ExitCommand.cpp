#include "MiniginPCH.h"
#include "ExitCommand.h"
#include "InputManager.h"

void dae::ExitCommand::Execute(std::shared_ptr<GameObject> gameObject)
{
	InputManager::GetInstance().m_Exit = true;
};