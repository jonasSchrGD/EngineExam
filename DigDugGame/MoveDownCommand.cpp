#include "pch.h"
#include "MoveDownCommand.h"
#include "Animations.h"
#include "SpriteRenderer.h"
#include "Time.h"


MoveDownCommand::MoveDownCommand(float movementSpeed)
	: m_MovementSpeed(movementSpeed)
{
}

void MoveDownCommand::Execute(std::shared_ptr<dae::GameObject> gameObject)
{
	gameObject->GetTransform().lock()->Translate(0, m_MovementSpeed * dae::Time::GetInstance().DeltaTime(), 0);
	gameObject->GetComponent<dae::SpriteRenderer>()->SetAnimation((int)DigDugAnimation::down);
}
