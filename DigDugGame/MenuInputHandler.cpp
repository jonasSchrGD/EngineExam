#include "pch.h"
#include "MenuInputHandler.h"
#include "SceneManager.h"
#include "TextRenderComponent.h"


MenuInputHandler::MenuInputHandler(std::vector<std::shared_ptr<dae::GameObject>> buttons, std::vector<std::shared_ptr<dae::BaseCommand>> commands, const SDL_Color& unselectedColor, const SDL_Color& selectedColor)
	:m_Buttons(buttons)
	,m_Commands(commands)
	,m_SelectedButton(0)
	,m_ColorUnselected(unselectedColor)
	,m_ColorSelected(selectedColor)
{
	for (auto button : buttons)
	{
		button->GetComponent<dae::TextRenderComponent>()->SetColor(unselectedColor);
	}
	m_Buttons[m_SelectedButton]->GetComponent<dae::TextRenderComponent>()->SetColor(selectedColor);
}


MenuInputHandler::~MenuInputHandler()
{
}

void MenuInputHandler::Update()
{
	auto& inputmanager = dae::InputManager::GetInstance();

	if (inputmanager.IsDown(m_Select, 0))
	{
		m_Commands[m_SelectedButton]->Execute(nullptr);//std::shared_ptr<dae::GameObject>()
	}

	if((inputmanager.IsDown(m_Up) || inputmanager.GetAxis(dae::ControllerAxis::JoystickLY, 0) > 0.75f) && m_SelectedButton > 0)
	{
		if (m_NoInput)
		{
			m_Buttons[m_SelectedButton]->GetComponent<dae::TextRenderComponent>()->SetColor(m_ColorUnselected);
			m_SelectedButton--;
			m_Buttons[m_SelectedButton]->GetComponent<dae::TextRenderComponent>()->SetColor(m_ColorSelected);
		}
		m_NoInput = false;
	}
	else if((inputmanager.IsDown(m_Down) || inputmanager.GetAxis(dae::ControllerAxis::JoystickLY, 0) < -0.75f) && m_SelectedButton < (int)m_Buttons.size() - 1)
	{
		if (m_NoInput)
		{
			m_Buttons[m_SelectedButton]->GetComponent<dae::TextRenderComponent>()->SetColor(m_ColorUnselected);
			m_SelectedButton++;
			m_Buttons[m_SelectedButton]->GetComponent<dae::TextRenderComponent>()->SetColor(m_ColorSelected);
		}
		m_NoInput = false;
	}
	else if(!m_NoInput)
	{
		m_NoInput = true;
	}
}
