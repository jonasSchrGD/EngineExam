#include "MiniginPCH.h"
#include "InputManager.h"

#include <SDL.h>
#pragma comment(lib, "Xinput.lib")

dae::InputManager::InputManager()
	: m_Mouse()
{
}

dae::InputManager::~InputManager()
{
}

bool dae::InputManager::ProcessInput()
{
	for (int i = 0; i < 4; i++)
	{
		m_Controllers[i].update();
		auto result = XInputGetState(i, &m_Controllers[i].currentState);
		m_Controllers[i].isConnected = (result != ERROR_NOT_CONNECTED);
	}

	UpdateKeys();

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT ) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			if (m_Keys.find(e.key.keysym.sym) == m_Keys.end())
				m_Keys.insert(std::pair<SDL_Keycode, KeyState>(e.key.keysym.sym, KeyState::pressed));
		}
		m_Mouse.mousePos.x = (float)e.button.x;
		m_Mouse.mousePos.y = (float)e.button.y;
		if(e.type == SDL_KEYUP)
		{
			m_Keys[e.key.keysym.sym] = KeyState::released;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			m_Mouse.isPressed = true;
		}
	}

	return !m_Exit;
}

bool dae::InputManager::IsDown(input button, int controller)
{
	if (controller > -1 && m_Controllers[controller].isConnected)
		if ((m_Controllers[controller].currentState.Gamepad.wButtons & (unsigned short)button.second) != 0)
			return true;
	
	if (m_Keys.find(button.first) != m_Keys.end())
	{
		auto key = m_Keys[button.first];
		return key == KeyState::down;
	}
	return false;
}

bool dae::InputManager::IsReleased(input button, int controller)
{
	if (controller > -1 && m_Controllers[controller].isConnected)
		if(
		(m_Controllers[controller].previousState.Gamepad.wButtons & (unsigned short)button.second) != 0
		&& (m_Controllers[controller].currentState.Gamepad.wButtons & (unsigned short)button.second) == 0)
			return true;

	if (m_Keys.find(button.first) != m_Keys.end())
	{
		return m_Keys[button.first] == KeyState::released;
	}
	return false;
}

bool dae::InputManager::IsPressed(input button, int controller)
{
	if (controller > -1 && m_Controllers[controller].isConnected)
		if (
			(m_Controllers[controller].currentState.Gamepad.wButtons & (unsigned short)button.second) != 0
			&& (m_Controllers[controller].previousState.Gamepad.wButtons & (unsigned short)button.second) == 0)
			return true;

	if (m_Keys.find(button.first) != m_Keys.end())
	{
		return m_Keys[button.first] == KeyState::pressed;
	}
	return false;
}

float dae::InputManager::GetAxis(ControllerAxis axis, int controller) const
{
	if (m_Controllers[controller].isConnected)
	{
		switch (axis)
		{
		case ControllerAxis::TriggerL:
			return (m_Controllers[controller].currentState.Gamepad.bLeftTrigger - 128) / 128.f;
		case ControllerAxis::TriggerR:
			return (m_Controllers[controller].currentState.Gamepad.bRightTrigger - 128) / 128.f;
		case ControllerAxis::JoystickLX:
			return m_Controllers[controller].currentState.Gamepad.sThumbLX / 32768.f;
		case ControllerAxis::JoystickLY:
			return m_Controllers[controller].currentState.Gamepad.sThumbLY / 32768.f;
		case ControllerAxis::JoystickRX:
			return m_Controllers[controller].currentState.Gamepad.sThumbRX / 32768.f;
		case ControllerAxis::JoystickRY:
			return m_Controllers[controller].currentState.Gamepad.sThumbRY / 32768.f;
		}
	}
	return 0;
}

void dae::InputManager::UpdateKeys()
{
	std::vector<SDL_Keycode> keysToRemove{};
	for (auto& key : m_Keys)
	{
		if (key.second == KeyState::released)
			keysToRemove.push_back(key.first);

		if (key.second == KeyState::pressed)
			key.second = KeyState::down;
	}

	for (auto keyToRemove : keysToRemove)
	{
		m_Keys.erase(keyToRemove);
	}
}

