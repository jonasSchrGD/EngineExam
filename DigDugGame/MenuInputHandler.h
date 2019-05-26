#pragma once
#include <BaseComponent.h>
#include "GameObject.h"
#include "InputManager.h"
#include "BaseCommand.h"
#include "TextRenderComponent.h"

class MenuInputHandler final : public dae::BaseComponent
{
public:
	MenuInputHandler(std::vector<std::shared_ptr<dae::GameObject>> buttons, std::vector<std::shared_ptr<dae::BaseCommand>> commands, const SDL_Color& unselectedColor, const SDL_Color& selectedColor, int nrOfLevels);
	~MenuInputHandler();

protected:
	void Update() override;

	void Initialize() override;
private:
	std::vector<std::shared_ptr<dae::GameObject>> m_Buttons;
	std::vector<std::shared_ptr<dae::BaseCommand>> m_Commands;
	std::shared_ptr<dae::TextRenderComponent> m_LevelSelection;

	dae::input m_Select{ SDLK_SPACE, (int)dae::ControllerButton::A };
	dae::input m_Up{ SDLK_w, 0 };
	dae::input m_Down{ SDLK_s, 0 };

	SDL_Color m_ColorUnselected, m_ColorSelected;

	int m_SelectedButton, m_SelectedLevel;
	const int m_NrOflevels;

	bool m_NoInput = true;
};

