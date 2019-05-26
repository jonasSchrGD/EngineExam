#include "pch.h"
#include "MenuInputHandler.h"
#include "SceneManager.h"
#include "TextRenderComponent.h"
#include "SelectedLevel.h"
#include "ContentManager.h"


MenuInputHandler::MenuInputHandler(std::vector<std::shared_ptr<dae::GameObject>> buttons, std::vector<std::shared_ptr<dae::BaseCommand>> commands, const SDL_Color& unselectedColor, const SDL_Color& selectedColor, int nrOfLevels)
	:m_Buttons(buttons)
	,m_Commands(commands)
	,m_SelectedButton(0)
	,m_SelectedLevel(1)
	,m_ColorUnselected(unselectedColor)
	,m_ColorSelected(selectedColor)
	,m_NrOflevels(nrOfLevels)
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
	else if(inputmanager.GetAxis(dae::ControllerAxis::JoystickRY, 0) > 0.75f)
	{
		if (m_NoInput)
		{
			m_SelectedLevel = (m_SelectedLevel + 1) % m_NrOflevels;
			SelectedLevel::GetInstance().selectedLevel = m_SelectedLevel + 1;
			m_LevelSelection->SetText("selected level: " + std::to_string(m_SelectedLevel + 1));
		}
		m_NoInput = false;
	}
	else if (inputmanager.GetAxis(dae::ControllerAxis::JoystickRY, 0) < -0.75f)
	{
		if (m_NoInput)
		{
			m_SelectedLevel--;
			if (m_SelectedLevel == -1)
				m_SelectedLevel += m_NrOflevels;
			SelectedLevel::GetInstance().selectedLevel = m_SelectedLevel + 1;
			m_LevelSelection->SetText("selected level: " + std::to_string(m_SelectedLevel + 1));
		}
		m_NoInput = false;
	}
	else if(!m_NoInput)
	{
		m_NoInput = true;
	}
}

void MenuInputHandler::Initialize()
{
	auto font = dae::ContentManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto object = std::make_shared<dae::GameObject>();
	object->SetPosition(300, 10);
	m_LevelSelection = std::make_shared<dae::TextRenderComponent>("selected level: " + std::to_string(m_SelectedLevel), font);
	object->AddComponent(m_LevelSelection);
	GetGameObject()->GetScene()->Add(object);
}
