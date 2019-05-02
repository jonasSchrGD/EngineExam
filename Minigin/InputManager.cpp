#include "MiniginPCH.h"
#include "InputManager.h"

#include <SDL.h>
#pragma comment(lib, "Xinput.lib")

dae::InputManager::InputManager()
	:m_CurrentKeyBoardState(new std::vector<SDL_Keycode>())
	,m_OldKeyBoardState(new std::vector<SDL_Keycode>())
{
	
}

dae::InputManager::~InputManager()
{
	delete m_CurrentKeyBoardState;
	delete m_OldKeyBoardState;
}

bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_Controllers[0].currentState, sizeof(XINPUT_STATE));

	for (int i = 0; i < 4; i++)
	{
		m_Controllers[i].update();
		auto result = XInputGetState(0, &m_Controllers[i].currentState);
		m_Controllers[i].isConnected = (result != ERROR_NOT_CONNECTED);
	}
	
	auto KeyboardState = m_CurrentKeyBoardState;
	m_CurrentKeyBoardState = m_OldKeyBoardState;
	m_OldKeyBoardState = KeyboardState;
	m_CurrentKeyBoardState->clear();

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			m_CurrentKeyBoardState->push_back(e.key.keysym.sym);
		}
		m_Mouse.mousePos.x = (float)e.button.x;
		m_Mouse.mousePos.y = (float)e.button.y;
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			m_Mouse.isPressed = true;
		}
	}

	return true;
}

bool dae::InputManager::IsDown(input button, int controller) const
{
	if (button.second > 0 && controller > 0 && m_Controllers[controller].isConnected)
		return (m_Controllers[controller].currentState.Gamepad.wButtons & (unsigned short)button.second) == (unsigned short)button.second;
	
	return std::find(m_CurrentKeyBoardState->begin(), m_CurrentKeyBoardState->end(), button.first) != m_CurrentKeyBoardState->end();
}

bool dae::InputManager::IsReleased(input button, int controller) const
{
	if (button.second > 0 && controller > 0 && m_Controllers[controller].isConnected)
		return
		(m_Controllers[controller].previousState.Gamepad.wButtons & (unsigned short)button.second) == (unsigned short)button.second
		&& (m_Controllers[controller].currentState.Gamepad.wButtons & (unsigned short)button.second) != (unsigned short)button.second;

	return
		(std::find(m_CurrentKeyBoardState->begin(), m_CurrentKeyBoardState->end(), button.first) == m_CurrentKeyBoardState->end()
			&& std::find(m_OldKeyBoardState->begin(), m_OldKeyBoardState->end(), button.first) != m_OldKeyBoardState->end());
}

bool dae::InputManager::IsPressed(input button, int controller) const
{
	if (button.second > 0 && controller > 0 && m_Controllers[controller].isConnected)
		return
		(m_Controllers[controller].currentState.Gamepad.wButtons & (unsigned short)button.second) == (unsigned short)button.second
		&& (m_Controllers[controller].previousState.Gamepad.wButtons & (unsigned short)button.second) != (unsigned short)button.second;

	return
		(std::find(m_CurrentKeyBoardState->begin(), m_CurrentKeyBoardState->end(), button.first) != m_CurrentKeyBoardState->end()
			&& std::find(m_OldKeyBoardState->begin(), m_OldKeyBoardState->end(), button.first) == m_OldKeyBoardState->end());
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

