#include "pch.h"
#include "DigDugAnimationHandler.h"
#include "InputManager.h"
#include "GameObject.h"
#include <Box2D/Common/b2Math.h>
#include "Time.h"


DigDugAnimationHandler::DigDugAnimationHandler()
	:m_MovementSpeed(50)
{
}


DigDugAnimationHandler::~DigDugAnimationHandler()
{
}

void DigDugAnimationHandler::Initialize()
{
	m_pSpriteRenderer = GetGameObject()->GetComponent<dae::SpriteRenderer>();
}

void DigDugAnimationHandler::Update()
{
	b2Vec2 movement{ 0,0 };
	if (dae::InputManager::GetInstance().IsDown(m_Right) || dae::InputManager::GetInstance().GetAxis(dae::ControllerAxis::JoystickLX,0) > 0.75f)
	{
		movement.x += 1;
		m_pSpriteRenderer->SetAnimation(1);
	}
	if (dae::InputManager::GetInstance().IsDown(m_Left) || dae::InputManager::GetInstance().GetAxis(dae::ControllerAxis::JoystickLX, 0) < -0.75f)
	{
		movement.x -= 1;
		m_pSpriteRenderer->SetAnimation(0);
	}
	if (dae::InputManager::GetInstance().IsDown(m_Up) || dae::InputManager::GetInstance().GetAxis(dae::ControllerAxis::JoystickLY, 0) > 0.75f)
	{
		movement.y -= 1;
		m_pSpriteRenderer->SetAnimation(3);
	}
	if (dae::InputManager::GetInstance().IsDown(m_Down) || dae::InputManager::GetInstance().GetAxis(dae::ControllerAxis::JoystickLY, 0) < -0.75f)
	{
		movement.y += 1;
		m_pSpriteRenderer->SetAnimation(2);
	}
	movement.Normalize();

	GetGameObject()->GetTransform().lock()->Translate(movement.x * m_MovementSpeed * dae::Time::GetInstance().DeltaTime(), movement.y * m_MovementSpeed * dae::Time::GetInstance().DeltaTime(), 0);
}

