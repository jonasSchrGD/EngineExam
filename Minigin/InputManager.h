#pragma once
#include <XInput.h>
#include "Singleton.h"

namespace dae
{
	enum class ControllerButton
	{
		A = XINPUT_GAMEPAD_A,
		B = XINPUT_GAMEPAD_B,
		X = XINPUT_GAMEPAD_X,
		Y = XINPUT_GAMEPAD_Y,
		DpadL = XINPUT_GAMEPAD_DPAD_LEFT,
		DpadR = XINPUT_GAMEPAD_DPAD_RIGHT,
		DpadU = XINPUT_GAMEPAD_DPAD_UP,
		DpadD = XINPUT_GAMEPAD_DPAD_DOWN,
		Start = XINPUT_GAMEPAD_START,
		Back = XINPUT_GAMEPAD_BACK,
		ThumbL = XINPUT_GAMEPAD_LEFT_THUMB,
		ThumbR = XINPUT_GAMEPAD_RIGHT_THUMB,
		BumberR = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		BumberL = XINPUT_GAMEPAD_LEFT_SHOULDER
	};
	enum class ControllerAxis
	{
		TriggerL,
		TriggerR,
		JoystickLX,
		JoystickLY,
		JoystickRX,
		JoystickRY
	};

	class InputManager final : public Singleton<InputManager>
	{
	private:
		struct ControllerInfo
		{
			XINPUT_STATE currentState;
			XINPUT_STATE previousState;
			bool isConnected;

			void update()
			{
				previousState = currentState;
			}
		};

	public:
		bool ProcessInput();
		bool IsDown(ControllerButton button, int controller)const;
		bool IsReleased(ControllerButton button, int controller)const;
		bool IsPressed(ControllerButton button, int controller) const;
		float GetAxis(ControllerAxis axis, int controller) const;

	private:
		ControllerInfo m_Controllers[4] = {};
	};//geen commands gebruikt omdat het veel vrijheid wegneemt naar mijn mening

}
