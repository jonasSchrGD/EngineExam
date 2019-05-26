#include "pch.h"
#include "MoveLeftCommand.h"
#include "Time.h"
#include "SpriteRenderer.h"
#include "Animations.h"
#include "DigDugColllision.h"

MoveLeftCommand::MoveLeftCommand(float movementSpeed, std::shared_ptr<Level> level)
	: m_MovementSpeed(movementSpeed)
	, m_Level(level)
	, m_TunnelTime(0.1f)
{
}

void MoveLeftCommand::Execute(std::shared_ptr<dae::GameObject> gameObject)
{
	auto transform = gameObject->GetTransform().lock();
	if (m_Level->IsInGrid(float2({ transform->GetPosition().x - m_MovementSpeed * dae::Time::GetInstance().DeltaTime(), transform->GetPosition().y })))
		transform->Translate(-m_MovementSpeed * dae::Time::GetInstance().DeltaTime(), 0, 0);

	auto spriterenderer = gameObject->GetComponent<dae::SpriteRenderer>();

	auto digdug = gameObject->GetComponent<DigDugColllision>();

	if (digdug)
		if (digdug->GetDigging())
		{
			m_TunnelTime = 0;
			spriterenderer->SetAnimation((int)DigDugAnimation::digLeft);
		}
		else
		{
			if (m_TunnelTime >= 0.1f)
				spriterenderer->SetAnimation((int)DigDugAnimation::left);
			else
			{
				spriterenderer->SetAnimation((int)DigDugAnimation::digLeft);
				m_TunnelTime += dae::Time::GetInstance().DeltaTime();
			}
		}
	else
		spriterenderer->SetAnimation((int)PookaAnimation::left);
}
