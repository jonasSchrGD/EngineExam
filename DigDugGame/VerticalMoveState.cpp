#include "pch.h"
#include "VerticalMoveState.h"
#include "IdleState.h"
#include "MoveUpCommand.h"
#include "MoveDownCommand.h"


VerticalMoveState::VerticalMoveState(std::shared_ptr<Level> level)
	:m_Level(level)
{
}

std::shared_ptr<dae::BaseState> VerticalMoveState::Update(std::shared_ptr<dae::GameObject> gameObject, dae::BaseCommand*& commandOutput)
{
	std::shared_ptr<BaseState> returnState;

	if (dae::InputManager::GetInstance().IsDown(m_Up) || dae::InputManager::GetInstance().GetAxis(dae::ControllerAxis::JoystickLY, 0) > 0.75f)
	{
		commandOutput = new MoveUpCommand(50);
	}
	else if (dae::InputManager::GetInstance().IsDown(m_Down) || dae::InputManager::GetInstance().GetAxis(dae::ControllerAxis::JoystickLY, 0) < -0.75f)
	{
		commandOutput = new MoveDownCommand(50);
	}
	else
	{
		return std::make_shared<IdleState>(m_Level);
	}


	return returnState;
}
