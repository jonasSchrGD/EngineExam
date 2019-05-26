#include "pch.h"
#include "VerticalMoveState.h"
#include "IdleState.h"
#include "MoveUpCommand.h"
#include "MoveDownCommand.h"


VerticalMoveState::VerticalMoveState(std::shared_ptr<Level> level)
	:m_Level(level)
{
}

std::shared_ptr<dae::BaseState> VerticalMoveState::Update(std::shared_ptr<dae::GameObject> gameObject, dae::BaseCommand*& commandOutput, int controller)
{
	std::shared_ptr<BaseState> returnState;

	if (controller == 0 && dae::InputManager::GetInstance().IsDown(m_Up) || dae::InputManager::GetInstance().GetAxis(dae::ControllerAxis::JoystickLY, controller) > 0.75f)
	{
		commandOutput = new MoveUpCommand(50, m_Level);
	}
	else if (controller == 0 && dae::InputManager::GetInstance().IsDown(m_Down) || dae::InputManager::GetInstance().GetAxis(dae::ControllerAxis::JoystickLY, controller) < -0.75f)
	{
		commandOutput = new MoveDownCommand(50, m_Level);
	}
	else
	{
		return std::make_shared<IdleState>(m_Level);
	}


	return returnState;
}
