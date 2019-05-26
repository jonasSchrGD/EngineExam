#include "pch.h"
#include "HorizontalMoveState.h"
#include "InputManager.h"
#include "MoveRightCommand.h"
#include "MoveLeftCommand.h"
#include "IdleState.h"


HorizontalMoveState::HorizontalMoveState(std::shared_ptr<Level> level)
	:m_Level(level)
{
}

std::shared_ptr<dae::BaseState> HorizontalMoveState::Update(std::shared_ptr<dae::GameObject> gameObject, dae::BaseCommand*& commandOutput, int controller)
{
	std::shared_ptr<BaseState> returnState;

	if (controller == 0 && dae::InputManager::GetInstance().IsDown(m_Right) || dae::InputManager::GetInstance().GetAxis(dae::ControllerAxis::JoystickLX, controller) > 0.75f)
		commandOutput = new MoveRightCommand(50, m_Level);

	else if (controller == 0 && dae::InputManager::GetInstance().IsDown(m_Left) || dae::InputManager::GetInstance().GetAxis(dae::ControllerAxis::JoystickLX, controller) < -0.75f)
		commandOutput = new MoveLeftCommand(50, m_Level);
	else
	{
		returnState = std::make_shared<IdleState>(m_Level);
	}

	return returnState;
}
