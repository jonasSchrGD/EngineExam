#include "pch.h"
#include "Projectile.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Time.h"
#include "CollisionComponent.h"
#include "TunnelUpdate.h"
#include "EnemyCollisionHandler.h"

Projectile::Projectile(int2 direction)
	: m_MaxDistance(80)
	, m_velocity(160)
	, m_Direction(direction)
	, m_Distance()
{
}


Projectile::~Projectile()
{
}

void Projectile::Initialize()
{
	if (m_Direction.x > 0)
		GetGameObject()->GetComponent<dae::SpriteRenderer>()->SetAnimation(1, false);
	else if(m_Direction.x < 0)
		GetGameObject()->GetComponent<dae::SpriteRenderer>()->SetAnimation(0, false);
	else if (m_Direction.y < 0)
		GetGameObject()->GetComponent<dae::SpriteRenderer>()->SetAnimation(2, false);
	else if (m_Direction.y > 0)
		GetGameObject()->GetComponent<dae::SpriteRenderer>()->SetAnimation(3, false);
}

void Projectile::OnTriggerEnter(std::shared_ptr<dae::CollisionComponent> other)
{
	if(other)
	{
		if (other->GetGameObject()->GetComponent<TunnelUpdate>() || other->GetGameObject()->GetComponent<EnemyCollisionHandler>())
		{
			if (other->GetGameObject()->GetComponent<dae::SpriteRenderer>()->GetAnimation() == int(TunnelSprite::none) || other->GetGameObject()->GetComponent<EnemyCollisionHandler>())
				m_Hit = true;
		}
	}
}

void Projectile::Update()
{
	if (!m_Hit)
	{
		float distance = dae::Time::GetInstance().DeltaTime() * m_velocity;
		float2 translate{ m_Direction.x * distance, m_Direction.y * distance };
		GetGameObject()->GetTransform().lock()->Translate(translate.x, translate.y, 0);

		m_Distance += distance;
		if (m_Distance >= m_MaxDistance)
			GetGameObject()->GetScene()->Remove(GetGameObject());
	}
	else
	{
		if (!dae::InputManager::GetInstance().IsDown(m_Select, m_PlayerNr))
			GetGameObject()->GetScene()->Remove(GetGameObject());
	}
}