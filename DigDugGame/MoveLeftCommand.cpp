#include "pch.h"
#include "MoveLeftCommand.h"
#include "Time.h"
#include "SpriteRenderer.h"
#include "Animations.h"

MoveLeftCommand::MoveLeftCommand(float movementSpeed)
	: m_MovementSpeed(movementSpeed)
{
}

void MoveLeftCommand::Execute(std::shared_ptr<dae::GameObject> gameObject)
{
	gameObject->GetTransform().lock()->Translate(-m_MovementSpeed * dae::Time::GetInstance().DeltaTime(), 0, 0);
	gameObject->GetComponent<dae::SpriteRenderer>()->SetAnimation((int)DigDugAnimation::left);
}
