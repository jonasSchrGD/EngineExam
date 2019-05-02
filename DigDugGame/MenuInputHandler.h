#pragma once
#include <BaseComponent.h>
#include "GameObject.h"
#include "InputManager.h"
#include "Command.h"

class MenuInputHandler final : public dae::BaseComponent
{
public:
	MenuInputHandler(std::vector<std::shared_ptr<dae::GameObject>> buttons, std::vector<std::shared_ptr<dae::Command>> commands);
	~MenuInputHandler();

protected:
	void Update() override;

private:
	std::vector<std::shared_ptr<dae::GameObject>> m_Buttons;
	std::vector<std::shared_ptr<dae::Command>> m_Commands;

	dae::input m_Select{ SDLK_KP_ENTER, (int)dae::ControllerButton::A };
	dae::input m_Up{ SDLK_UP, 0 };
	dae::input m_Down{ SDLK_DOWN, 0 };

	int m_SelectedButton;
};

