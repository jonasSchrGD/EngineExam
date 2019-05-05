#pragma once
#include <BaseComponent.h>
#include "GameObject.h"
#include "InputManager.h"
#include "BaseCommand.h"

class MenuInputHandler final : public dae::BaseComponent
{
public:
	MenuInputHandler(std::vector<std::shared_ptr<dae::GameObject>> buttons, std::vector<std::shared_ptr<dae::BaseCommand>> commands, const SDL_Color& unselectedColor, const SDL_Color& selectedColor);
	~MenuInputHandler();

protected:
	void Update() override;

private:
	std::vector<std::shared_ptr<dae::GameObject>> m_Buttons;
	std::vector<std::shared_ptr<dae::BaseCommand>> m_Commands;

	dae::input m_Select{ SDLK_RETURN, (int)dae::ControllerButton::A };
	dae::input m_Up{ SDLK_UP, 0 };
	dae::input m_Down{ SDLK_DOWN, 0 };

	SDL_Color m_ColorUnselected, m_ColorSelected;

	int m_SelectedButton;

	bool m_NoInput = true;
};

