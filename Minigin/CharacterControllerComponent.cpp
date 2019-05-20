#include "MiniginPCH.h"
#include "CharacterControllerComponent.h"


dae::CharacterControllerComponent::CharacterControllerComponent(std::shared_ptr<BaseState> startState, int playerNr)
	:m_CurrentState(startState)
	,m_PlayerNr(playerNr)
	,m_pCurrentCommand()
{
}

void dae::CharacterControllerComponent::Update()
{
	auto gameobject = GetGameObject();
	BaseCommand* command{};

	auto newstate = m_CurrentState->Update(gameobject, command);
	if (newstate)
		m_CurrentState = newstate;

	if(command != nullptr)
	{
		if (m_pCurrentCommand != nullptr)
		{
			if(typeid(*m_pCurrentCommand) != typeid(*command))
			{
				delete m_pCurrentCommand;
				m_pCurrentCommand = command;
			}
			else
				delete command;
		}
		else
		{
			m_pCurrentCommand = command;
		}
	}

	if(m_pCurrentCommand != nullptr)
		m_pCurrentCommand->Execute(gameobject);
}

