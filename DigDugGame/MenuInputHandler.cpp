#include "pch.h"
#include "MenuInputHandler.h"
#include "SceneManager.h"


MenuInputHandler::MenuInputHandler(std::vector<std::shared_ptr<dae::GameObject>> buttons, std::vector<std::shared_ptr<dae::Command>> commands)
	:m_Buttons(buttons)
	,m_Commands(commands)
	,m_SelectedButton(0)
{
}


MenuInputHandler::~MenuInputHandler()
{
}

void MenuInputHandler::Update()
{
	auto& inputmanager = dae::InputManager::GetInstance();
	if (inputmanager.IsDown(m_Select), 0)
	{
		m_Commands[m_SelectedButton]->Execute(nullptr);//std::shared_ptr<dae::GameObject>()
	}
	if(inputmanager.IsDown(m_Up) && m_SelectedButton > 0)
	{
		m_SelectedButton--;
	}
	if(inputmanager.IsDown(m_Down) && m_SelectedButton < (int)m_Buttons.size() - 1)
	{
		m_SelectedButton++;
	}
}
