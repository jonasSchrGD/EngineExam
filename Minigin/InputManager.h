#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <SDL.h>
#include "structs.h"
#include <map>

namespace dae
{
	class ExitCommand;

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

	using input = std::pair<SDL_Keycode, int>;

	class InputManager final : public Singleton<InputManager>
	{
		friend ExitCommand;
	private:
		struct ControllerInfo
		{
			XINPUT_STATE currentState;
			XINPUT_STATE previousState;
			bool isConnected;

			void update()
			{
				previousState = currentState;
				currentState = XINPUT_STATE();
			}
		};
		struct MouseState
		{
			float2 mousePos;
			bool isPressed, isPressedOld;

			void Update()
			{
				isPressedOld = isPressed;
				isPressed = false;
			}
		};

		enum class KeyState
		{
			pressed,
			down,
			released
		};

	public:
		InputManager();
		~InputManager();

		bool ProcessInput();
		bool IsDown(input button, int controller = -1);
		bool IsReleased(input button, int controller = -1);
		bool IsPressed(input button, int controller = -1);
		float GetAxis(ControllerAxis axis, int controller) const;
		const float2& GetMousePos() const { return m_Mouse.mousePos; }

	private:
		void UpdateKeys();

		ControllerInfo m_Controllers[4] = {};
		std::map<SDL_Keycode, KeyState> m_Keys;
		MouseState m_Mouse;
		bool m_Exit = false;
	};//geen commands gebruikt omdat het veel vrijheid wegneemt naar mijn mening

}
