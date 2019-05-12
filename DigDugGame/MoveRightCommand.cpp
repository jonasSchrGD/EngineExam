#include "pch.h"
#include "MoveRightCommand.h"
#include "Animations.h"
#include "SpriteRenderer.h"
#include "Time.h"


MoveRightCommand::MoveRightCommand(float movementSpeed)
	: m_MovementSpeed(movementSpeed)
{
}

void MoveRightCommand::Execute(std::shared_ptr<dae::GameObject> gameObject)
{
	gameObject->GetTransform().lock()->Translate(m_MovementSpeed * dae::Time::GetInstance().DeltaTime(), 0, 0);
	gameObject->GetComponent<dae::SpriteRenderer>()->SetAnimation((int)DigDugAnimation::right);
}
