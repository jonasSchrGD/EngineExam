#include "pch.h"
#include "MoveUpCommand.h"
#include "Time.h"
#include "SpriteRenderer.h"
#include "Animations.h"


MoveUpCommand::MoveUpCommand(float movementSpeed)
	: m_MovementSpeed(movementSpeed)
{
}

void MoveUpCommand::Execute(std::shared_ptr<dae::GameObject> gameObject)
{
	gameObject->GetTransform().lock()->Translate(0, -m_MovementSpeed * dae::Time::GetInstance().DeltaTime(), 0);
	gameObject->GetComponent<dae::SpriteRenderer>()->SetAnimation((int)DigDugAnimation::up);
}

