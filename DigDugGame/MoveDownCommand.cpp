#include "pch.h"
#include "MoveDownCommand.h"
#include "Animations.h"
#include "SpriteRenderer.h"
#include "Time.h"
#include "DigDugColllision.h"


MoveDownCommand::MoveDownCommand(float movementSpeed, std::shared_ptr<Level> level)
	: m_MovementSpeed(movementSpeed)
	, m_Level(level)
	, m_TunnelTime(0.1f)
{
}

void MoveDownCommand::Execute(std::shared_ptr<dae::GameObject> gameObject)
{
	auto transform = gameObject->GetTransform().lock();
	if (m_Level->IsInGrid(float2({ transform->GetPosition().x, transform->GetPosition().y + m_MovementSpeed * dae::Time::GetInstance().DeltaTime() })))
		gameObject->GetTransform().lock()->Translate(0, m_MovementSpeed * dae::Time::GetInstance().DeltaTime(), 0);

	auto spriterenderer = gameObject->GetComponent<dae::SpriteRenderer>();

	auto digdug = gameObject->GetComponent<DigDugColllision>();

	if (digdug)
		if (digdug->GetDigging())
		{
			m_TunnelTime = 0;
			spriterenderer->SetAnimation((int)DigDugAnimation::digDown);
		}
		else
		{
			if (m_TunnelTime >= 0.1f)
				spriterenderer->SetAnimation((int)DigDugAnimation::down);
			else
			{
				spriterenderer->SetAnimation((int)DigDugAnimation::digDown);
				m_TunnelTime += dae::Time::GetInstance().DeltaTime();
			}
		}
}
