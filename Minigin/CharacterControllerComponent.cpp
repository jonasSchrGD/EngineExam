#include "MiniginPCH.h"
#include "CharacterControllerComponent.h"


dae::CharacterControllerComponent::CharacterControllerComponent(std::shared_ptr<BaseState> startState)
	:m_CurrentState(startState)
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
		command->Execute(gameobject);
		delete command;
	}
}

