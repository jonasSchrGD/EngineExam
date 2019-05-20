#include "pch.h"
#include "MoveUpCommand.h"
#include "Time.h"
#include "SpriteRenderer.h"
#include "Animations.h"
#include "DigDugColllision.h"


MoveUpCommand::MoveUpCommand(float movementSpeed, std::shared_ptr<Level> level)
	: m_MovementSpeed(movementSpeed)
	, m_Level(level)
	, m_TunnelTime(0.1f)
{
}

void MoveUpCommand::Execute(std::shared_ptr<dae::GameObject> gameObject)
{
	auto transform = gameObject->GetTransform().lock();
	if (m_Level->IsInGrid(float2({ transform->GetPosition().x, transform->GetPosition().y  - m_MovementSpeed * dae::Time::GetInstance().DeltaTime()})))
		gameObject->GetTransform().lock()->Translate(0, -m_MovementSpeed * dae::Time::GetInstance().DeltaTime(), 0);

	auto spriterenderer = gameObject->GetComponent<dae::SpriteRenderer>();

	auto digdug = gameObject->GetComponent<DigDugColllision>();
	
	if (digdug)
		if (digdug->GetDigging())
		{
			m_TunnelTime = 0;
			spriterenderer->SetAnimation((int)DigDugAnimation::digUp);
		}
		else
		{
			if (m_TunnelTime >= 0.1f)
				spriterenderer->SetAnimation((int)DigDugAnimation::up);
			else
			{
				spriterenderer->SetAnimation((int)DigDugAnimation::digUp);
				m_TunnelTime += dae::Time::GetInstance().DeltaTime();
			}
		}
}

