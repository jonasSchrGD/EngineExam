#include "pch.h"
#include "IdleState.h"
#include "HorizontalMoveState.h"
#include "VerticalMoveState.h"


IdleState::IdleState(std::shared_ptr<Level> level)
	:m_Level(level)
{
}

std::shared_ptr<dae::BaseState> IdleState::Update(std::shared_ptr<dae::GameObject> gameObject, dae::BaseCommand*& commandOutput)
{
	UNREFERENCED_PARAMETER(commandOutput);

	std::shared_ptr<BaseState> returnState{};

	if (dae::InputManager::GetInstance().IsDown(m_Right) || dae::InputManager::GetInstance().GetAxis(dae::ControllerAxis::JoystickLX, 0) > 0.75f)
	{
		if (m_Level->Center(gameObject, false))
		{
			returnState = std::make_shared<HorizontalMoveState>(m_Level);
		}
	}
	else if (dae::InputManager::GetInstance().IsDown(m_Left) || dae::InputManager::GetInstance().GetAxis(dae::ControllerAxis::JoystickLX, 0) < -0.75f)
	{
		if (m_Level->Center(gameObject, false))
		{
			returnState = std::make_shared<HorizontalMoveState>(m_Level);
		}
	}
	else if (dae::InputManager::GetInstance().IsDown(m_Up) || dae::InputManager::GetInstance().GetAxis(dae::ControllerAxis::JoystickLY, 0) > 0.75f)
	{
		if (m_Level->Center(gameObject, true))
		{
			returnState = std::make_shared<VerticalMoveState>(m_Level);
		}
	}
	else if (dae::InputManager::GetInstance().IsDown(m_Down) || dae::InputManager::GetInstance().GetAxis(dae::ControllerAxis::JoystickLY, 0) < -0.75f)
	{
		if (m_Level->Center(gameObject, true))
		{
			returnState = std::make_shared<VerticalMoveState>(m_Level);
		}
	}

	return returnState;
}


