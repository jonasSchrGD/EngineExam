#include "MiniginPCH.h"
#include "InputManager.h"

#include <SDL.h>
#pragma comment(lib, "Xinput.lib")

bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_Controllers[0].currentState, sizeof(XINPUT_STATE));

	for (int i = 0; i < 4; i++)
	{
		m_Controllers[i].update();
		auto result = XInputGetState(0, &m_Controllers[i].currentState);
		m_Controllers[i].isConnected = (result != ERROR_NOT_CONNECTED);
	}
	

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	return true;
}

bool dae::InputManager::IsDown(ControllerButton button, int controller) const
{
	if (m_Controllers[controller].isConnected)
		return (m_Controllers[controller].currentState.Gamepad.wButtons & (unsigned short)button) == (unsigned short)button;
	else
		return false;
}

bool dae::InputManager::IsReleased(ControllerButton button, int controller) const
{
	if (m_Controllers[controller].isConnected)
		return
		(m_Controllers[controller].previousState.Gamepad.wButtons & (unsigned short)button) == (unsigned short)button
		&& (m_Controllers[controller].currentState.Gamepad.wButtons & (unsigned short)button) != (unsigned short)button;
	else
		return false;
}

bool dae::InputManager::IsPressed(ControllerButton button, int controller) const
{
	if (m_Controllers[controller].isConnected)
		return
		(m_Controllers[controller].currentState.Gamepad.wButtons & (unsigned short)button) == (unsigned short)button
		&& (m_Controllers[controller].previousState.Gamepad.wButtons & (unsigned short)button) != (unsigned short)button;
	else
		return false;
}

float dae::InputManager::GetAxis(ControllerAxis axis, int controller) const
{
	if (m_Controllers[controller].isConnected)
	{
		switch (axis)
		{
		case ControllerAxis::TriggerL:
			return m_Controllers[controller].currentState.Gamepad.bLeftTrigger;
		case ControllerAxis::TriggerR:
			return m_Controllers[controller].currentState.Gamepad.bRightTrigger;
		case ControllerAxis::JoystickLX:
			return m_Controllers[controller].currentState.Gamepad.sThumbLX;
		case ControllerAxis::JoystickLY:
			return m_Controllers[controller].currentState.Gamepad.sThumbLY;
		case ControllerAxis::JoystickRX:
			return m_Controllers[controller].currentState.Gamepad.sThumbRX;
		case ControllerAxis::JoystickRY:
			return m_Controllers[controller].currentState.Gamepad.sThumbRY;
		}
	}
	return 0;
}

